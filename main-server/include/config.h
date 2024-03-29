#ifndef H_MAIN_SERVER_CONFIG_FILE
#define H_MAIN_SERVER_CONFIG_FILE

#define MS_DEFAULT_PORT 8888 //socket binds
#define MS_RECEIVE_BUFFER 1024 //received data by server hold on a array with this size
#define MS_DATABASE_FILE "fluffy.db"
#define MS_VERSION "0.0.1"


#define GAME_SERVER_APPLICATION_PATH "../game-server/"
#define GAME_SERVER_APPLICATION_NAME "gs.run"

#define MS_DATA_ENCRYPT_DECRYPT_SHIFT 5
#define MS_GET_LOBBY_LIST_COUNT_OF_RESULTS 10

#define MS_CLIENT_MINIMUM_IDENTITY_LENGTH 59
#define MS_CLIENT_MAXIMUM_IDENTITY_LENGTH 60

#define MS_CLIENT_MINIMUM_USERNAME_LENGTH 5
#define MS_CLIENT_MAXIMUM_USERNAME_LENGTH 32

#define MS_CLIENT_MINIMUM_PASSWORD_LENGTH 5
#define MS_CLIENT_MAXIMUM_PASSWORD_LENGTH 32

#define MS_CLIENT_MINIMUM_HARDWAREID_LENGTH 32
#define MS_CLIENT_MAXIMUM_HARDWAREID_LENGTH 32

#define MS_CLIENT_MINIMUM_EMAIL_LENGTH 10
#define MS_CLIENT_MAXIMUM_EMAIL_LENGTH 32

#define MS_LOBBY_IP_PORT_MINIMUM_LENGTH 11
#define MS_GET_LOBBY_BY_ID_MINIMUM_LENGTH 44

#define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_YEARS 0
#define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_MONTHS 1
#define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_DAYS 0
#define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_HOURS 0
#define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_MINUTES 6
#define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_SECONDS 0

/*
  data received from client or wants to send position of that string is set by here
  maybe later needs to re-position data code indexes change these three numbers.
*/
#define MS_DATA_CODE_INDEX_A 0
#define MS_DATA_CODE_INDEX_B 1
#define MS_DATA_CODE_INDEX_C 2

#define MS_DATA_START_AT_INDEX 3
#define MS_DATA_DELIMITER ",&"
#define MS_REQUEST_CLOSER "~"
#define MS_RECEIVED_DATA_MINIMUM_LENGTH 1
#define MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH 3
#define MS_INVALID_LOBBY_ID_IS 0


#define MS_CREATE_LOBBY_DEFAULT_SERVER_IP "127.0.0.1"
#define MS_CREATE_LOBBY_DEFAULT_SERVER_PORT "9088"

#define MS_CHARECTERS_ALLOWED_FOR_IDENTITY_GENERATOR "abcdefghijklmnopqrstuvwxyzABCDEFGHIKLMNOPQRSTUVWXYZ0123456789"

#endif
