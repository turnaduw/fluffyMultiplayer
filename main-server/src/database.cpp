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
                             "isTextChatAllowed BOOLEAN DEFAULT 1,"
                             "isVoiceChatAllowed BOOLEAN DEFAULT 1,"
                             "isSpecterAllowed BOOLEAN DEFAULT 0,"
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










}
