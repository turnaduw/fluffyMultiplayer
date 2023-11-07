#include "../include/database.h"


namespace FluffyMultiplayer
{
  FluffyDatabase::FluffyDatabase(bool isDatbaseFileExists=true)
  {
    int rc = sqlite3_open(MS_DATABASE_FILE, &db);
    if(rc)
        std::cout << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    else
    {
      std::cout << "Database opened/created fine.\n";

      //sqlite3.h will create that datbase file but empty lets init tables
      if(!isDatbaseFileExists)
        initTables();
    }
  }

  FluffyDatabase::~FluffyDatabase()
  {
    sqlite3_close(db);
    db=nullptr;
    errMsg=nullptr;
    // delete db;
    delete errMsg;
  }

  void FluffyDatabase::initTables()
  {
    int rc;
    // Create a table for client
    const char* createTableClient = "CREATE TABLE IF NOT EXISTS fm_client("
                                 "id INTEGER," //AUTOINCREMENT
                                 "email TEXT NOT NULL,"
                                 "username TEXT NOT NULL,"
                                 "password TEXT NOT NULL,"
                                 "hardwareId TEXT NOT NULL,"
                                 "isBanned BOOLEAN DEFAULT 0,"
                                 "isLobbyCreationLimited BOOLEAN DEFAULT 0,"
                                 "isAdmin BOOLEAN DEFAULT 0,"
                                 "registerDate DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                 "PRIMARY KEY (id,email,username) );";
    rc = sqlite3_exec(db, createTableClient, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error while init table fm_client: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Create table for lobby
    const char* createTableLobby = "CREATE TABLE IF NOT EXISTS fm_lobby("
                             "id INTEGER," //AUTOINCREMENT
                             "server_ip TEXT NOT NULL,"
                             "server_port TEXT NOT NULL,"
                             "password TEXT," //not null or e default password
                             "gameMode INTEGER DEFAULT 1,"
                             "maxPlayers INTEGER DEFAULT 4,"
                             "owner INTEGER NOT NULL,"
                             "voiceChatForbidden BOOLEAN DEFAULT 0,"
                             "textChatForbidden BOOLEAN DEFAULT 0,"
                             "specterForbidden BOOLEAN DEFAULT 0,"
                             "lobbyStatus BOOLEAN DEFAULT 0,"
                             "showLobbyOnList BOOLEAN DEFAULT 1,"
                             "creationDate DATETIME DEFAULT CURRENT_TIMESTAMP,"
                             "FOREIGN KEY(owner) REFERENCES fm_client(id),"
                             "PRIMARY KEY (id,owner) );";
    rc = sqlite3_exec(db, createTableLobby, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error while init table fm_lobby: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Create table for client_login
    const char* createClientLogin = "CREATE TABLE IF NOT EXISTS fm_client_login("
                             "clientId INTEGER,"
                             "identity TEXT,"
                             "loginDate DATETIME DEFAULT CURRENT_TIMESTAMP,"
                             "FOREIGN KEY(clientId) REFERENCES fm_client(id),"
                             "PRIMARY KEY(clientId, identity) );";
    rc = sqlite3_exec(db, createClientLogin, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error while init table fm_client_login: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Create table for client_in_lobby
    const char* createClientInLobby = "CREATE TABLE IF NOT EXISTS fm_client_in_lobby("
                             "clientId INTEGER,"
                             "lobbyId INTEGER,"
                             "FOREIGN KEY(clientId) REFERENCES fm_client(id),"
                             "FOREIGN KEY(lobbyId) REFERENCES fm_lobby(id),"
                             "PRIMARY KEY(clientId,lobbyId) );";
    rc = sqlite3_exec(db, createClientInLobby, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error while init table fm_client_in_lobby: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
  }



  std::string FluffyDatabase::getLobbyInfo(const int& lobbyId)
  {
      std::string basic_query = "SELECT server_ip,server_port FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      std::string info = search_in_db(basic_query);
      return info;
  }

  std::string FluffyDatabase::getLobbyInfoByOwnerId(const int& ownerId)
  {
    std::string basic_query = "SELECT server_ip,server_port FROM fm_lobby WHERE owner='";
    basic_query += std::to_string(ownerId) + "';";
    std::string info = search_in_db(basic_query);
    return info;
  }


  std::string FluffyDatabase::getLobbyList(int howManyResultReturn)
  {
    std::string lobbies;
    while(howManyResultReturn>0)
    {
      std::string basic_query = "SELECT id,password,gameMode,server_ip,server_port,maxPlayers,voiceChatForbidden,textChatForbidden,specterForbidden FROM fm_lobby;";
      lobbies += MS_DATA_DELIMITER + search_in_db(basic_query);
      howManyResultReturn--;
    }
    return lobbies;
  }

  bool FluffyDatabase::isIdentityExists(const std::string& identity)
  {
        int cid = getClientIdByIdentity(identity);
        if(cid>=1)
          return true;
        return false;
  }

  int FluffyDatabase::getClientIdByIdentity(const std::string& identity)
  {
    std::string basic_query = "SELECT clientId FROM fm_client_login WHERE identity='";
    basic_query += identity + "';";
    std::string clientId = search_in_db(basic_query);

    //convert received data into int
    const char* cxx = clientId.c_str();
    int cid = std::atoi(cxx);
    if(cid>=1)
      return cid;
    return -1; //not found
  }

  int FluffyDatabase::registerClient(const FluffyMultiplayer::RegisterClientData& client, std::string& outputIdentity)
  {
      //search for that email address.
      std::string basic_query = "SELECT id FROM fm_client WHERE username=";
      basic_query += client.username + ";";
      if(isExists_in_db(basic_query))
        return MS_ERROR_FAILED_TO_REGISTER_EMIAL_EXISTS;

      //search for that username
      basic_query = "SELECT id FROM fm_client WHERE email=";
      basic_query += client.email + ";";
      if(isExists_in_db(basic_query))
        return MS_ERROR_FAILED_TO_REGISTER_USERNAME_EXISTS;

      //check for password not easy
      if(dataSecurity.isPasswordEasy(client.password))
        return MS_ERROR_FAILED_TO_REGISTER_EASY_PASSWORD;

      //insert into database
      basic_query = "INSERT INTO fm_client (email,username,password,hardwareId) VALUES('";
      basic_query += client.email + "', '";
      basic_query += client.username + "', '";
      basic_query += client.password  + "', '";
      basic_query += client.hardwareId + "');";
      if(query_to_db(basic_query))
      {
        //search for created client id..
        basic_query = "SELECT id FROM fm_client WHERE username='";
        basic_query += client.username + ";";
        std::string result =  search_in_db(basic_query);
        int clientId = FluffyMultiplayer::convertStringToInt(result.substr(3,result.length())); //count of charecter id + a '=' is 3 so result is on [3]
        if(clientId<=0)
          return MS_ERROR_FAILED_TO_REGISTER_CLIENT; //failed to get client id

        //create session for that client id
        if(!createSessionForClient(clientId,outputIdentity)) //genrate and insert identity for that id
          return MS_ERROR_FAILED_TO_INSERT_CLIENT_IDENTITY;

        if(outputIdentity.length()<MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH)
        {
          outputIdentity = "";
          return MS_ERROR_FAILED_TO_REGISTER_CLIENT;
        }
        else
          return MS_RESPONSE_SUCCESS_REGISTER;

      }
      else
        return MS_ERROR_FAILED_TO_REGISTER_CLIENT; //failed to insert
  }

  int FluffyDatabase::loginClient(const FluffyMultiplayer::LoginClientData& client, std::string& outputIdentity)
  {
    if(client.oldIdentity.length()<=0)
    {
      //insert into database
      std::string basic_query = "SELECT isBanned,id,password FROM fm_client WHERE username='";
      basic_query += client.username + "');";
      std::string result = search_in_db(basic_query);
      if(result.length()<MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH)
        return MS_ERROR_FAILED_TO_LOGIN_NOT_EXISTS; //98% chance to account not found because in some case maybe database is not abled to return query's response.

      int isBanned = FluffyMultiplayer::convertStringToInt(result.substr(9,10)); // isBanned= [9], boolain is just one chartecter 0 or 1
      if(isBanned>0)
        return MS_ERROR_FAILED_TO_LOGIN_BANNED;

      int clientId = FluffyMultiplayer::convertStringToInt(result.substr(12,5)); //count of charecter id + a '=' is 3 so result is on [9+3]
      if(clientId<=0)
        return MS_ERROR_FAILED_TO_LOGIN_CLIENT; //failed to get client id

      std::string password=result.substr(17,result.length());
      if(client.password == password)
      {
          //create session for that client id
          if(!createSessionForClient(clientId,outputIdentity))
            return MS_ERROR_FAILED_TO_INSERT_CLIENT_IDENTITY;

          if(outputIdentity.length()<MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH)
          {
            outputIdentity = "";
            return MS_ERROR_FAILED_TO_LOGIN_CLIENT;
          }
          else
            return MS_RESPONSE_SUCCESS_LOGIN;
      }
      else
        return MS_ERROR_FAILED_TO_LOGIN_INCORRECT; //incrrect password
    }
    else //re-login client
    {
      //search for that oldIdentity from fm_client_login
      std::string basic_query = "SELECT loginDate,clientId FROM fm_client_login WHERE identity='";
      basic_query += client.oldIdentity + "');";
      std::string result = search_in_db(basic_query);
      if(result.length()<MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH)
        return MS_ERROR_FAILED_TO_LOGIN_CLIENT; //98% chance to login not found because in some case maybe database is not abled to return query's response.

      //get current time

      //...
      //compare current time with loginDate then return diffrance number of days,hours,minutes,seconds
      //if those numbers are more than our DEFINES written in config.h return failed login expired
      //else return login sucess return new identity to client.
      // #define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_DAYS 1
      // #define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_HOURS 12
      // #define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_MINUTES 0
      // #define MS_CLIENT_LOGIN_IDENTITY_EXPIRE_SECONDS 0
    }
    return MS_ERROR_FAILED_TO_LOGIN_CLIENT;
  }

  int FluffyDatabase::createLobby(const FluffyMultiplayer::CreateLobbyData& lobbyInfo, std::string& outputServerIpPort)
  {
     int ownerId = getClientIdByIdentity(lobbyInfo.identity);
     if(ownerId != -1)
     {
       if(isOwnLobby(ownerId))
        return MS_ERROR_FAILED_TO_LOBBY_CREATION_CANT_OWN_TWO_LOBBY;
       if(!isLobbyCreationLimited(ownerId))
       {
          std::string basic_query = "INSERT INTO fm_lobby (gameMode,maxPlayers,password,owner,textChatForbidden,voiceChatForbidden,specterForbidden) VALUES('";
          basic_query += std::to_string(lobbyInfo.gameMode) + "', '" +
           std::to_string(lobbyInfo.maxPlayers) + "', '" +
           lobbyInfo.password  + "', '" +
           std::to_string(ownerId) + "', '" +
           std::to_string(lobbyInfo.textChatForbidden) + "', '" +
           std::to_string(lobbyInfo.voiceChatForbidden) + "', '" +
           std::to_string(lobbyInfo.specterForbidden) + "');";
          if(query_to_db(basic_query))
          {
            outputServerIpPort = getLobbyInfoByOwnerId(ownerId);
            if(outputServerIpPort.length()<MS_LOBBY_IP_PORT_MINIMUM_LENGTH)
            {
              outputServerIpPort="";
              return MS_ERROR_FAILED_TO_CREATE_LOBBY; //failed to get lobby ip and port
            }
            else
              return MS_RESPONSE_SUCCESS_LOBBY_CREATED;
          }
          else
            return MS_ERROR_FAILED_TO_CREATE_LOBBY; //failed to insert lobby
       }
       else
        return MS_ERROR_FAILED_TO_LOBBY_CREATION_FORBIDDEN_FOR_YOU;
     }
     else
      return MS_ERROR_FAILED_TO_CREATE_LOBBY; //failed to get client id
  }



  bool FluffyDatabase::isOwnLobby(const int& ownerId)
  {
    std::string basic_query = "SELECT server_port FROM fm_lobby WHERE id=";
    basic_query += std::to_string(ownerId) + ";";
    return isExists_in_db(basic_query);
  }

  bool FluffyDatabase::isLobbyCreationLimited(const int& clientId)
  {
      std::string basic_query = "SELECT isLobbyCreationLimited FROM fm_client WHERE id='";
      basic_query += std::to_string(clientId) + ";";
      std::string result = search_in_db(basic_query);
      result = result.substr(23,result.length()); //count of charecter isLobbyCreationLimited + a '=' is 22 so result is on [23]
      if(result == "true" || result == "TRUE" || result == "True" || result == "1") //idk what database saves for BOOLEAN type
        return true;
      return false;
  }

  bool FluffyDatabase::createSessionForClient(const int& clientId, std::string& outputIdentity)
  {
    outputIdentity = dataSecurity.generateIdentity();

    //insert identity for client
    std::string basic_query = "DELETE FROM fm_client_login WHERE clientId='";
    basic_query += std::to_string(clientId) + "');";
    if(query_to_db(basic_query))
    {
      basic_query = "INSERT INTO fm_client_login (identity,clientId) VALUES('";
      basic_query += outputIdentity + "', '";
      basic_query += std::to_string(clientId) + "');";
      if(query_to_db(basic_query))
        return true;
    }

    outputIdentity = "";
    return false;
  }













  //database----------
  int FluffyDatabase::search_in_db_callback(void* data, int argc, char** argv, char** azColName)
  {
    std::string* _result = static_cast<std::string*>(data);
    for (int i = 0; i < argc; i++)
    {
        std::cout << "db search i=" << i  << "\t"<< azColName[i] << '=' << (argv[i] ? argv[i] : "NULL") << std::endl;
        *_result += azColName[i];
        *_result += '=';
        *_result +=  (argv[i] ? argv[i] : "NULL");
        *_result += "\n";
    }
    std::cout << std::endl;
    return 0;
  }
  std::string FluffyDatabase::search_in_db(std::string& _q)
  {
    char* final_query = new char[_q.length()+1];
    std::strcpy(final_query, _q.c_str());

    std::string result;
    int rc = sqlite3_exec(db, final_query, &FluffyDatabase::search_in_db_callback, &result , &errMsg);


    final_query = nullptr;
    delete[] final_query;


    if (rc != SQLITE_OK)
    {
        std::cout << "(search_in_db)SQL search error: " << errMsg << "\tquery=" << _q << std::endl;
        sqlite3_free(errMsg);
    }
    return result;
  }


  //----------
  int FluffyDatabase::isExists_in_db_callback(void* data, int argc, char** argv, char** azColName)
  {
    std::string* _result = static_cast<std::string*>(data);
    for (int i = 0; i < argc; i++)
    {
        std::cout << "db isExists i=" << i  << "\t"<< azColName[i] << '=' << (argv[i] ? argv[i] : "NULL") << std::endl;
        *_result +=  (argv[i] ? argv[i] : "NULL");
        *_result += "\n";
    }
    std::cout << std::endl;
    return 0;
  }
  bool FluffyDatabase::isExists_in_db(std::string& _q)
  {
    char* final_query = new char[_q.length()+1];
    std::strcpy(final_query, _q.c_str());

    std::string result;
    int rc = sqlite3_exec(db, final_query, &FluffyDatabase::isExists_in_db_callback, &result , &errMsg);

    final_query = nullptr;
    delete[] final_query;

    if (rc != SQLITE_OK)
    {
        std::cout << "(isExists_in_db) SQL search error: " << errMsg << "\tquery=" << _q << std::endl;
        sqlite3_free(errMsg);
    }

    if(result.length()>MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH)
      return true;
    return false;
  }

  //--------------------
  bool FluffyDatabase::query_to_db(const std::string& _q)
  {
        bool result;
        char* final_query = new char[_q.length()+1];
        std::strcpy(final_query, _q.c_str());

        int rc = sqlite3_exec(db, final_query, nullptr, 0, &errMsg);

        final_query = nullptr;
        delete[] final_query;



        if (rc != SQLITE_OK)
        {
            std::cout << "(query_to_db) SQL error: " << errMsg << "\tquery=" << _q << std::endl;
            sqlite3_free(errMsg);
        }
        else
          result = true;
        return result;
  }


}
