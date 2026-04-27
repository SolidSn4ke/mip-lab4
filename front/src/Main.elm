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
    , sceneFile : Maybe File
    , alertText : String
    , alertVisibility : Alert.Visibility
    }


type Msg
    = SendForm
    | UpdateObj File
    | UpdateSceneFile File
    | RecieveResponse (Result Http.Error String)
    | AlertMsg Alert.Visibility


init : () -> ( Model, Cmd Msg )
init _ =
    ( Model Nothing Nothing "" Alert.closed, Cmd.none )


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        SendForm ->
            ( model
            , ( model.objFile, model.sceneFile )
                |> (\( f1, f2 ) ->
                        case ( f1, f2 ) of
                            ( Just obj, Just scene ) ->
                                sendForm obj scene

                            ( _, _ ) ->
                                Cmd.none
                   )
            )

        UpdateObj f ->
            ( { model | objFile = Just f }, Cmd.none )

        UpdateSceneFile f ->
            ( { model | sceneFile = Just f }, Cmd.none )

        RecieveResponse res ->
            case res of
                Ok s ->
                    ( { model | alertText = s, alertVisibility = Alert.shown }, Cmd.none )

                Err _ ->
                    ( { model | alertText = "Ошибка", alertVisibility = Alert.shown }, Cmd.none )

        AlertMsg visibility ->
            ( { model | alertVisibility = visibility }, Cmd.none )


view : Model -> Html Msg
view model =
    Grid.container []
        [ CDN.stylesheet
        , alertElemnt model
        , Form.form []
            [ Form.group []
                [ Form.label [ for "obj-input" ] [ text "OBJ Файл" ]
                , input [ id "obj-input", type_ "file", on "change" (D.map UpdateObj fileDecoder) ] []
                ]
            , Form.group []
                [ Form.label [ for "scene-input" ] [ text "Параметры сцены" ]
                , input [ id "scene-input", type_ "file", on "change" (D.map UpdateSceneFile fileDecoder) ] []
                ]
            , Button.button [ Button.primary, Button.onClick SendForm ] [ text "Отправить" ]
            ]
        ]


alertElemnt : Model -> Html Msg
alertElemnt model =
    Alert.config
        |> Alert.info
        |> Alert.dismissable AlertMsg
        |> Alert.children [ text model.alertText ]
        |> Alert.view model.alertVisibility


fileDecoder : D.Decoder File
fileDecoder =
    D.at [ "target", "files", "0" ] File.decoder


sendForm : File -> File -> Cmd Msg
sendForm objFile sceneFile =
    Http.post
        { url = "http://localhost:8080/scene"
        , body =
            Http.multipartBody
                [ Http.filePart "obj" objFile, Http.filePart "scene" sceneFile ]
        , expect = Http.expectString RecieveResponse
        }
