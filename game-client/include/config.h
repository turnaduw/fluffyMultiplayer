#ifndef H_CONFIG
#define H_CONFIG

#define WINDOW_WIDTH 1024
#deinfe WINDOW_HEIGHT 1024
#deifne WINDOW_TITLE "Game Client"
#define WINDOW_STYLE sf::Style::Fullscreen


#define PATH_TO_ASSESTS "./assets/"
#define PATH_TO_UI_COMPONENTS_ASSETS PATH_TO_ASSESTS "uiComponents/"
#define DEFAULT_FONT PATH_TO_ASSESTS "arial.ttf"
#define DEFAULT_FONT_SIZE 13
#define ASSETS_NOT_FOUND PATH_TO_ASSESTS "failedToLoad.png"

#define DATA_ENCRYPT_DECRYPT_SHIFT 5

#define DELIMITER ",&"
#define CLOSER "~"
#define GAME_MODES_DELIMITER ",*"

#define VOICE_CHAT_SAMPLE_RATE 44100
#define VOICE_CHAT_FRAMES_PER_BUFFER 1024

#endif
