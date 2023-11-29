#ifndef H_MAIN_CLIENT_CONFIG_FILE
#define H_MAIN_CLIENT_CONFIG_FILE

//MC means MainClient

//window
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Fluffy Multiplayer App"

#define FORM_HIDE_CHARECTER '*'
#define STATES_ASSET_PATH "./assets/states/"

#define MC_PATH_TO_FONTS "./assets/fonts/"
#define MC_DEFAULT_FONT "arial.ttf"

#define MC_DEFAULT_PORT 13333

#define MC_RECEIVE_BUFFER 1024
#define CLIENT_LOCAL_SERVER_LIST_FILE "serverlist.txt"
#define CLIENT_LOCAL_APP_CONFIG_FILE "app.txt"

#define MC_IP_PORT_SEPARATOR ":"
#define MC_IP_PORT_ENDLINE ";"

#define MC_APP_CONFIG_IDENTITY_KEY "identity"
#define MC_APP_CONFIG_SEPERATOR "="
#define MC_APP_CONFIG_ENDLINE ";"
#define MC_IDENTITY_MIN_LENGTH 31
#define MC_IDENTITY_MAX_LENGTH 32

#define MC_REQUEST_DELIMITER ",&"
#define MC_REQUEST_CLOSER "~"

#define MC_SERVER_DEFAULT_IP "127.0.0.1"
#define MC_SERVER_DEFAULT_PORT 8888

#define MC_REQUEST_TIMEOUT 1000
#define MC_STATE_BIND_PICK_PORT_TRY_COUNT 10

#define MC_MAIN_PAGE_LOBBY_LIST_REFRESH_TIMER 1000
#define MC_MAIN_PAGE_LOBBY_LIST_REFRESH_TIMEOUT 300

#define MC_MINUMUM_RESPONSE_CODE 100
#define MC_RESPONSE_POSITION_MIN_INDEX 0
#define MC_RESPONSE_POSITION_MAX_INDEX 3




//---------------------------- Form Elements
#define FE_PATH_TO_ASSETS "./assets/uiComponents/"

//TI means Text Input
#define TI_DEFAULT_FONT_PATH MC_PATH_TO_FONTS MC_DEFAULT_FONT
#define TI_DEFAULT_FONT_SIZE 17
#define TI_DEFAULT_COLOR sf::Color::Black
#define TI_DEFAULT_SIZE 100,70
#define TI_DEFAULT_STYLE sf::Text::Bold
#define TI_DEFAULT_POSITION_X 100
#define TI_DEFAULT_POSITION_Y 100

#define TI_TITLE_PADDING_X (0.0,0.0)
#define TI_TITLE_PADDING_Y (0.0,0.0)
#define TI_ERROR_PADDING_X (0.0,0.0)
#define TI_ERROR_PADDING_Y (0.0,0.0)
#define TI_INPUTBOX_PADDING_X (0.0,0.0) //also mainText will this this
#define TI_INPUTBOX_PADDING_Y (0.0,0.0) //also mainText will this this
#define TI_TEXTURE_INPUT_BOX "textInputTexture.png"


//TIP means Text Input Password
#define TIP_BUTTON_VISIBLE_PASSWORD_PADDING_X (0.0,0.0)
#define TIP_BUTTON_VISIBLE_PASSWORD_PADDING_Y (0.0,0.0)
#define TIP_TEXTURE_BUTTON_VISIBLE_PASSWORD_ON "passwordVisibleButtonTexture.png"
#define TIP_TEXTURE_BUTTON_VISIBLE_PASSWORD_OFF "passwordInvisbleButtonTexture.png"


//button component
#define BUTTON_TEXTURE "buttonTexture.png"
#define BUTTON_DEFAULT_BACKGROUND_COLOR sf::Color::White
#define BUTTON_DEFAULT_FORGROUND_COLOR sf::Color::Black
#define BUTTON_DEFAULT_SIZE_WIDTH 20
#define BUTTON_DEFAULT_SIZE_HEIGHT 10
#define BUTTON_DEFAULT_STYLE sf::Text::Bold
#define BUTTON_DEFAULT_FONT_SIZE 17
#define BUTTON_DEFAULT_POS_X 10.0
#DEFINE BUTTON_DEFAULT_POS_Y 10.0
#endif
