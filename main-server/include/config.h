#ifndef H_MAIN_SERVER_CONFIG_FILE
#define H_MAIN_SERVER_CONFIG_FILE

#define MS_DEFAULT_PORT 8888 //socket binds
#define MS_RECEIVE_BUFFER 1024 //received data by server hold on a array with this size
#define MS_DATABASE_FILE "fluffy.db"
#define MS_VERSION "0.0.1"



#define MS_GET_LOBBY_LIST_COUNT_OF_RESULTS 10
#define MS_CLIENT_MINIMUM_IDENTITY_LENGTH 10
#define MS_CLIENT_MAXIMUM_IDENTITY_LENGTH 30

/*
  data received from client or wants to send position of that string is set by here
  maybe later needs to re-position data code indexes change these three numbers.
*/
#define MS_DATA_CODE_INDEX_A 0
#define MS_DATA_CODE_INDEX_B 1
#define MS_DATA_CODE_INDEX_C 2

#define MS_DATA_START_AT_INDEX 3
#define MS_DATA_DELIMITER ";"


#endif
