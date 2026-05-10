port module Main exposing (main)

import Bootstrap.Alert as Alert
import Bootstrap.Button as Button
import Bootstrap.CDN as CDN
import Bootstrap.Carousel exposing (Msg)
import Bootstrap.Form as Form
import Bootstrap.Grid as Grid
import Browser
import Canvas exposing (rect, shapes)
import Canvas.Settings exposing (Setting, fill)
import Canvas.Settings.Advanced exposing (GlobalCompositeOperationMode(..))
import File exposing (File)
import Html exposing (..)
import Html.Attributes exposing (for, id, style, type_)
import Html.Events exposing (on)
import Http
import Json.Decode as D


port renderPpm : String -> Cmd msg


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
    , imageReady : Bool
    }


type Msg
    = SendForm
    | UpdateObj File
    | UpdateSceneFile File
    | RecieveResponse (Result Http.Error String)
    | AlertMsg Alert.Visibility


init : () -> ( Model, Cmd Msg )
init _ =
    ( Model Nothing Nothing "" Alert.closed False, Cmd.none )


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
                    ( { model | alertText = "Scene rendered successfully!", alertVisibility = Alert.shown, imageReady = True }
                    , renderPpm s
                    )

                Err _ ->
                    ( { model | alertText = "Error", alertVisibility = Alert.shown }, Cmd.none )

        AlertMsg visibility ->
            ( { model | alertVisibility = visibility }, Cmd.none )


view : Model -> Html Msg
view model =
    Grid.container []
        [ CDN.stylesheet
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
        , if model.imageReady then
            div [ style "text-align" "center", style "margin-top" "20px" ]
                [ h3 [] [ text "Result" ]
                , node "canvas" [ id "render-canvas", style "border" "1px solid black" ] []
                ]

          else
            text ""
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
