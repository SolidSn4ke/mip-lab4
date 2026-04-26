module Main exposing (main)

import Bootstrap.Alert as Alert
import Bootstrap.Button as Button
import Bootstrap.CDN as CDN
import Bootstrap.Carousel exposing (Msg)
import Bootstrap.Form as Form
import Bootstrap.Grid as Grid
import Browser
import File exposing (File)
import Html exposing (..)
import Html.Attributes exposing (for, id, type_)
import Html.Events exposing (on)
import Http
import Json.Decode as D


main : Program () Model Msg
main =
    Browser.element
        { init = init
        , subscriptions = \_ -> Sub.none
        , update = update
        , view = view
        }


type alias Model =
    { objFile : Maybe File
    , alertText : String
    }


type Msg
    = SendForm
    | UpdateObj File
    | RecieveResponse (Result Http.Error String)


init : () -> ( Model, Cmd Msg )
init _ =
    ( Model Nothing "", Cmd.none )


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        SendForm ->
            ( model, sendForm model )

        UpdateObj f ->
            ( { model | objFile = Just f }, Cmd.none )

        RecieveResponse res ->
            case res of
                Ok s ->
                    ( { model | alertText = s }, Cmd.none )

                Err _ ->
                    ( { model | alertText = "Ошибка" }, Cmd.none )


view : Model -> Html Msg
view model =
    Grid.container []
        [ CDN.stylesheet
        , Alert.simplePrimary [] [ text model.alertText ]
        , Form.form []
            [ Form.group []
                [ Form.label [ for "obj-input" ] [ text "OBJ Файл" ]
                , input [ id "obj-input", type_ "file", on "change" (D.map UpdateObj fileDecoder) ] []
                ]
            , Button.button [ Button.primary, Button.onClick SendForm ] [ text "Отправить" ]
            ]
        ]


fileDecoder : D.Decoder File
fileDecoder =
    D.at [ "target", "files", "0" ] File.decoder


sendForm : Model -> Cmd Msg
sendForm model =
    case model.objFile of
        Just objFile ->
            Http.post
                { url = "http://localhost:8080/scene"
                , body = Http.multipartBody [ Http.filePart "scene" objFile ]
                , expect = Http.expectString RecieveResponse
                }

        Nothing ->
            Cmd.none
