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
    delete db;
    delete errMsg;
  }

  void FluffyDatabase::initTables()
  {
    int rc;
    // Create a table for client
    const char* createTableClient = "CREATE TABLE IF NOT EXISTS fm_client("
                                 "id INTEGER AUTOINCREMENT,"
                                 "email PRIMARY KEY TEXT NOT NULL,"
                                 "username PRIMARY KEY TEXT NOT NULL,"
                                 "password TEXT NOT NULL,"
                                 "hardwareId TEXT NOT NULL,"
                                 "isBanned BOOLEAN DEFAULT 0,"
                                 "isLobbyCreationLimited BOOLEAN DEFAULT 0,"
                                 "isAdmin BOOLEAN DEFAULT 0,"
                                 "registerDate DATETIME DEFAULT CURRENT_TIMESTAMP);";
    rc = sqlite3_exec(db, createTableClient, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error while init table fm_client: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Create table for lobby
    const char* createTableLobby = "CREATE TABLE IF NOT EXISTS fm_lobby("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "server_ip TEXT NOT NULL,"
                             "server_port TEXT NOT NULL,"
                             "password TEXT," //not null or e default password
                             "gameMode INTEGER DEFAULT 1,"
                             "maxPlayers INTEGER DEFAULT 4,"
                             "owner INTEGER PRIMARY KEY NOT NULL,"
                             "voiceChatForbidden BOOLEAN DEFAULT 0,"
                             "textChatForbidden BOOLEAN DEFAULT 0,"
                             "specterForbidden BOOLEAN DEFAULT 0,"
                             "creationDate DATETIME DEFAULT CURRENT_TIMESTAMP,"
                             "FOREIGN KEY(owner) REFERENCES fm_client(id));";
    rc = sqlite3_exec(db, createTableLobby, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error while init table fm_lobby: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Create table for client_login
    const char* createClientLogin = "CREATE TABLE IF NOT EXISTS fm_client_login("
                             "clientId INTEGER PRIMARY KEY,"
                             "identity TEXT PRIMARY KEY,"
                             "loginDate DATETIME DEFAULT CURRENT_TIMESTAMP,"
                             "FOREIGN KEY(clientId) REFERENCES fm_client(id));";
    rc = sqlite3_exec(db, createClientLogin, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error while init table fm_client_login: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Create table for client_in_lobby
    const char* createClientInLobby = "CREATE TABLE IF NOT EXISTS fm_client_in_lobby("
                             "clientId INTEGER PRIMARY KEY,"
                             "lobbyId INTEGER PRIMARY KEY,"
                             "FOREIGN KEY(clientId) REFERENCES fm_client(id),"
                             "FOREIGN KEY(lobbyId) REFERENCES fm_lobby(id));";
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
        std::string basic_query = "SELECT id FROM fm_client WHERE identity='";
        basic_query += identity + "';";
        std::string clientId = isExists_in_db(basic_query);

        //convert received data into int
        const char* cxx = clientId.c_str();
        int cid = std::atoi(cxx);
        if(cid>=1)
          return true;
        return false;
  }

  int FluffyDatabase::getClientIdByIdentity(const std::string& identity)
  {
    std::string basic_query = "SELECT id FROM fm_client WHERE identity='";
    basic_query += identity + "';";
    std::string clientId = isExists_in_db(basic_query);

    //convert received data into int
    const char* cxx = clientId.c_str();
    int cid = std::atoi(cxx);
    if(cid>=1)
      return cid;
    return -1; //not found
  }

  int FluffyDatabase::loginClient(const FluffyMultiplayer::LoginClientData& client, std::string& outputIdentity)
  {
     //generateIdentity then checkForUniq then return that id //write code..
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
          basic_query += lobbyInfo.gameMode + "', '" +
           lobbyInfo.maxPlayers + "', '" +
           lobbyInfo.password  + "', '" +
           ownerId + "', '" +
           lobbyInfo.textChatForbidden + "', '" +
           lobbyInfo.voiceChatForbidden + "', '" +
           lobbyInfo.specterForbidden + "');";
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

  int FluffyDatabase::registerClient(const FluffyMultiplayer::RegisterClientData& client, std::string& outputIdentity)
  {
     //write..
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
        if (rc != SQLITE_OK)
        {
            std::cout << "(query_to_db) SQL error: " << errMsg << "\tquery=" << _q << std::endl;
            sqlite3_free(errMsg);
        }
        else
          result = true;
        delete[] final_query;
        return result;
  }


}
