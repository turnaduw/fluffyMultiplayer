#ifndef H_CONFIG
#define H_CONFIG


#define MC_RECEIVE_BUFFER_TEXT 1024
#define MC_RECEIVE_BUFFER_VOICE 1024
#define MS_DATA_ENCRYPT_DECRYPT_SHIFT 5

#define DEFAULT_PORT_TEXT 7777
#define DEFAULT_PORT_VOICE 9999

#define PRINT_LOGS_LEVEL FluffyMultiplayer::LogType::All
#define LOG_FILE "./gameServer.log"

#define DATABASE_FILENAME "../main-server/fluffy.db" //this path is from ./gameServer.run on runtime
#define DATABASE_LOG_FILENAME "dbFluffy.log"
#define DATABASE_PRINT_LOGS_LEVEL FluffyMultiplayer::LogType::Error

#define SOCKET_LOG_FILENAME "socket.log"
#define SOCKET_PRINT_LOGS_LEVEL FluffyMultiplayer::LogType::All


#define MS_RECEIVED_DATA_MINIMUM_LENGTH 1
#define MS_DATA_DELIMITER ",&"
#define MS_REQUEST_CLOSER "~"
#define MS_DATA_CODE_INDEX_A 0
#define MS_DATA_CODE_INDEX_B 1
#define MS_DATA_CODE_INDEX_C 2


#define DEFAULT_PLAYER_NAME "?player?"
#define DEFAULT_PLAYER_VOICE_ENABLE false

#define LOBBY_MINIMUM_PASSWORD_LENGTH 1

#define SEND_TEXT_CHAT_TO_SPECTERS true
#define SEND_VOICE_CHAT_TO_SPECTERS false

#endif
