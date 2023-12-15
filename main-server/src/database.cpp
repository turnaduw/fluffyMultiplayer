#include "../include/database.h"


namespace FluffyMultiplayer
{

  void FluffyDatabase::insertTestData()
  {
    //lets create some test accounts(client) and create lobby for them

    std::cout << "test data insertation started." << std::endl;



    auto insertClient = [this] (int i, std::string email, std::string username,
              std::string password, std::string hardwareid, std::string banned,
            std::string lobbycreation, std::string admin)
    {
      std::string test_query = "INSERT INTO fm_client (email,username,password,hardwareId,isBanned,isLobbyCreationLimited,isAdmin) VALUES('";
      test_query += email + "', '";
      test_query += username + "', '";
      test_query += password + "', '";
      test_query += hardwareid + "', '";
      test_query += banned + "', '";
      test_query += lobbycreation + "', '";
      test_query += admin + "');";
      if(query_to_db(test_query))
        std::cout << "[SUCCESS] client " << i << " (email:" << email << ", user:"
                << username << ", pass:" << password <<") added successfully.\n";
      else
        std::cout << "[FAILED] client " << i << " (email:" << email << ", user:"
                << username << ", pass:" << password <<") to add.\n";
    };

    insertClient(1,"peter@gmail.com","peter","peter123","1234567","0","0","0");
    insertClient(2,"alex@gmail.com","alex","alex123","4659753","0","0","0");
    insertClient(3,"mohammad@gmail.com","mohammad","mohammad123","9788652","0","0","0");
    insertClient(4,"json@gmail.com","json","json123","1326498","0","0","0");
    insertClient(5,"alireza@gmail.com","alireza","alireza123","4444444","0","0","1");
    insertClient(6,"albin@gmail.com","albin","albin123","9956200","0","0","1");
    insertClient(7,"devil@gmail.com","devil","devil123","2346897","0","1","0");
    insertClient(8,"samsung@gmail.com","samsung","samsung123","4652379","0","1","0");
    insertClient(9,"keeperofLight@gmail.com","keeperofLight","keeperofLight123","7878946","1","0","0");

    //clear accounts (without lobby and loimitation)
    insertClient(10,"capsLOCK@gmail.com","capsLOCK","capsLOCK123","2020203","0","0","0");
    insertClient(11,"madmax@gmail.com","madmax","madmax123","3333333","0","0","0");
    insertClient(12,"asusAsus@gmail.com","asusAsus","asusAsus123","4567893","0","0","0");




    auto insertLobby = [this] (int i, std::string gm, std::string players, std::string pass,
             std::string ownerid,  std::string textchat,  std::string voicechat,  std::string specter,
             std::string ipadd,  std::string portadd, std::string showOnlist, std::string lobbyStatus)
    {
      std::string test_query = "INSERT INTO fm_lobby (gameMode,maxPlayers,password,owner,textChatForbidden,voiceChatForbidden,specterForbidden,server_ip,server_port,showLobbyOnList,lobbyStatus) VALUES('";
      test_query += gm + "', '";
      test_query += players + "', '";
      test_query += pass + "', '";
      test_query += ownerid + "', '";
      test_query += textchat + "', '";
      test_query += voicechat + "', '";
      test_query += specter + "', '";
      test_query += ipadd + "', '";
      test_query += portadd + "', '";
      test_query += showOnlist + "', '";
      test_query += lobbyStatus + "');";
      if(query_to_db(test_query))
      {
        test_query = "INSERT INTO fm_client_in_lobby ( clientId, lobbyId ) VALUES('";
        test_query += ownerid + "', (SELECT  id FROM fm_lobby WHERE owner='";
        test_query += ownerid + "'));";
        if(query_to_db(test_query))
        {
          std::cout << "[SUCCESS] lobby " << i << " (owner:" << ownerid << ", password:" << pass <<") added successfully and owner insesrted into lobby.\n";
        }
        else
        std::cout << "[HALF-SUCCESS] lobby " << i << " (owner:" << ownerid << ", password:" << pass <<") added successfully but could not insert owner into lobby.\n";
      }
      else
        std::cout << "[FAILED] lobby " << i << " (owner:" << ownerid << ", password:" << pass <<") to add.\n";
      };

      insertLobby(1, "0", "10", "lobby1", "1", "0", "0" , "0", "127.0.0.1", "8888", "1", "0");
      insertLobby(2, "1", "2", "lobby2", "2", "0", "1" , "0", "127.0.0.2", "8888", "1", "1");
      insertLobby(3, "2", "6", "lobby3", "3", "0", "0" , "1", "127.0.0.3", "8888", "0", "0");
      insertLobby(4, "1", "2", "lobby4", "4", "1", "1" , "0", "127.0.0.4", "8888", "1", "1");
      insertLobby(5, "0", "3", "lobby5", "5", "0", "0" , "0", "127.0.0.5", "8888", "0", "1");
      insertLobby(6, "0", "5", "", "6", "1", "1" , "1", "127.0.0.6", "8888", "1", "0");
      insertLobby(7, "0", "10", "lobby7", "7", "1", "0" , "1", "127.0.0.7", "8888", "1", "0");
      insertLobby(8, "1", "8", "lobby8", "8", "0", "1" , "0", "127.0.0.8", "8888", "1", "1");
      insertLobby(9, "2", "10", "lobby9", "9", "0", "0" , "1", "127.0.0.9", "8888", "1", "0");
      insertLobby(10, "2", "1", "lobby10", "10", "1", "0" , "0", "127.0.0.10", "8888", "1", "0");

    std::cout << "test data insertation finished." << std::endl;
  }

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
      {
        initTables();
        insertTestData();
      }
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
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT," //
                                 "email TEXT NOT NULL,"
                                 "username TEXT NOT NULL,"
                                 "password TEXT NOT NULL,"
                                 "hardwareId TEXT NOT NULL,"
                                 "isBanned BOOLEAN DEFAULT 0,"
                                 "isLobbyCreationLimited BOOLEAN DEFAULT 0,"
                                 "isAdmin BOOLEAN DEFAULT 0,"
                                 "registerDate DATETIME DEFAULT (datetime('now','localtime')));";
                                 // "PRIMARY KEY (email,username) );";
    rc = sqlite3_exec(db, createTableClient, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error while init table fm_client: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Create table for lobby
    const char* createTableLobby = "CREATE TABLE IF NOT EXISTS fm_lobby("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT," //AUTOINCREMENT
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
                             "creationDate DATETIME DEFAULT (datetime('now','localtime')),"
                             "FOREIGN KEY(owner) REFERENCES fm_client(id));";
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
                             "loginDate DATETIME DEFAULT (datetime('now','localtime')),"
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
      std::string all;
      std::string lpassword, lGameMode, lServerAddress, lMaxPlayers, lVoiceChat, lTextChat, lSpecter, lLobbyStatus, lShowLobbyOnList, lCurrentPlayers;
      //get password
      std::string basic_query = "SELECT password FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lpassword = search_in_db(basic_query,true);
      if(lpassword.empty()) //we dont send exact password to client.
        lpassword="0";
      else
        lpassword="1";

      //get gameMode
      basic_query = "SELECT gameMode FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lGameMode = search_in_db(basic_query,true);

      //get serverIp and port
      basic_query = "SELECT server_ip FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lServerAddress = search_in_db(basic_query,true);
      lServerAddress += ":";
      basic_query = "SELECT server_port FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lServerAddress += search_in_db(basic_query,true);


      //get maxPlayers
      basic_query = "SELECT maxPlayers FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lMaxPlayers = search_in_db(basic_query,true);

      //get voiceChatForbidden
      basic_query = "SELECT voiceChatForbidden FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lVoiceChat = search_in_db(basic_query,true);

      //get textChatForbidden
      basic_query = "SELECT textChatForbidden FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lTextChat = search_in_db(basic_query,true);

      //get specterForbidden
      basic_query = "SELECT specterForbidden FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lSpecter = search_in_db(basic_query,true);


      //get lobbyStatus
      basic_query = "SELECT lobbyStatus FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lLobbyStatus = search_in_db(basic_query,true);

      //get showLobbyOnList
      basic_query = "SELECT showLobbyOnList FROM fm_lobby WHERE id='";
      basic_query += std::to_string(lobbyId) + "';";
      lShowLobbyOnList = search_in_db(basic_query,true);


      //get currentPlayers (count of players in lobby)
      basic_query = "SELECT COUNT(*) FROM fm_client_in_lobby WHERE lobbyId='";
      basic_query += std::to_string(lobbyId) + "';";
      lCurrentPlayers = search_in_db(basic_query,true);


      /*
        append searched data into one string as order style LobbyData
       (convert this string will use LobbyData strcut order variables defined)
      */
      all += lpassword + std::string(MS_DATA_DELIMITER);
      all += lVoiceChat + std::string(MS_DATA_DELIMITER);
      all += lTextChat + std::string(MS_DATA_DELIMITER);
      all += lSpecter + std::string(MS_DATA_DELIMITER);
      all += lLobbyStatus + std::string(MS_DATA_DELIMITER);
      all += lShowLobbyOnList + std::string(MS_DATA_DELIMITER);
      all += std::to_string(lobbyId) + std::string(MS_DATA_DELIMITER);
      all += lMaxPlayers + std::string(MS_DATA_DELIMITER);
      all += lCurrentPlayers + std::string(MS_DATA_DELIMITER);
      all += lGameMode + std::string(MS_DATA_DELIMITER);
      all += lServerAddress + std::string(MS_DATA_DELIMITER);
      std::cout << "getlobbyinfo() lobby id="  << lobbyId <<  " data=" << all << std::endl;
      return all;
  }

  std::string FluffyDatabase::getLobbyInfoByOwnerId(const int& ownerId)
  {
    std::string serverIp, serverPort;
    std::string result;

    std::string basic_query = "SELECT server_ip FROM fm_lobby WHERE owner='";
    basic_query += std::to_string(ownerId) + "';";
    std::string info = search_in_db(basic_query,false);
    serverIp = info.substr(10,info.length()-1);
    std::cout << "getLobbyInfoByOwnerId() serverIp = " << serverIp << std::endl;

    basic_query = "SELECT server_port FROM fm_lobby WHERE owner='";
    basic_query += std::to_string(ownerId) + "';";
    info = search_in_db(basic_query,false);
    serverPort = info.substr(12,info.length()-1);
    std::cout << "getLobbyInfoByOwnerId() serverPort = " << serverPort << std::endl;


    //there is a \n before/after ip/port so have to remove that
    serverIp.erase(std::remove(serverIp.begin(), serverIp.end(), '\n'), serverIp.cend());
    serverPort.erase(std::remove(serverPort.begin(), serverPort.end(), '\n'), serverPort.cend());

    result = serverIp + ":" + serverPort;

    std::cout << "getLobbyInfoByOwnerId() res=" << result << std::endl;
    return result;
  }


  std::string FluffyDatabase::getLobbyList(int howManyResultReturn)
  {
    std::string all;
    std::string lpassword, lGameMode, lServerAddress, lMaxPlayers, lVoiceChat, lTextChat, lSpecter, lLobbyStatus, lShowLobbyOnList, lCurrentPlayers;
    for(int i=1; i<=howManyResultReturn; i++)
    {
      //get password
      std::string basic_query = "SELECT password FROM fm_lobby WHERE id='";
      basic_query += std::to_string(howManyResultReturn) + "';";
      lpassword = search_in_db(basic_query,true);
      if(lpassword.empty()) //we dont send exact password to client.
        lpassword="0";
      else
        lpassword="1";

      //get gameMode
      basic_query = "SELECT gameMode FROM fm_lobby WHERE id='";
      basic_query += std::to_string(i) + "';";
      lGameMode = search_in_db(basic_query,true);

      //get serverIp and port
      basic_query = "SELECT server_ip FROM fm_lobby WHERE id='";
      basic_query += std::to_string(i) + "';";
      lServerAddress = search_in_db(basic_query,true);
      lServerAddress += ":";
      basic_query = "SELECT server_port FROM fm_lobby WHERE id='";
      basic_query += std::to_string(i) + "';";
      lServerAddress += search_in_db(basic_query,true);


      //get maxPlayers
      basic_query = "SELECT maxPlayers FROM fm_lobby WHERE id='";
      basic_query += std::to_string(i) + "';";
      lMaxPlayers = search_in_db(basic_query,true);

      //get voiceChatForbidden
      basic_query = "SELECT voiceChatForbidden FROM fm_lobby WHERE id='";
      basic_query += std::to_string(i) + "';";
      lVoiceChat = search_in_db(basic_query,true);

      //get textChatForbidden
      basic_query = "SELECT textChatForbidden FROM fm_lobby WHERE id='";
      basic_query += std::to_string(i) + "';";
      lTextChat = search_in_db(basic_query,true);

      //get specterForbidden
      basic_query = "SELECT specterForbidden FROM fm_lobby WHERE id='";
      basic_query += std::to_string(i) + "';";
      lSpecter = search_in_db(basic_query,true);


      //get lobbyStatus
      basic_query = "SELECT lobbyStatus FROM fm_lobby WHERE id='";
      basic_query += std::to_string(i) + "';";
      lLobbyStatus = search_in_db(basic_query,true);

      //get showLobbyOnList
      basic_query = "SELECT showLobbyOnList FROM fm_lobby WHERE id='";
      basic_query += std::to_string(i) + "';";
      lShowLobbyOnList = search_in_db(basic_query,true);


      //get currentPlayers (count of players in lobby)
      basic_query = "SELECT COUNT(*) FROM fm_client_in_lobby WHERE lobbyId='";
      basic_query += std::to_string(i) + "';";
      lCurrentPlayers = search_in_db(basic_query,true);


      /*
        append searched data into one string as order style LobbyData
       (convert this string will use LobbyData strcut order variables defined)
      */
      all += lpassword + std::string(MS_DATA_DELIMITER);
      all += lVoiceChat + std::string(MS_DATA_DELIMITER);
      all += lTextChat + std::string(MS_DATA_DELIMITER);
      all += lSpecter + std::string(MS_DATA_DELIMITER);
      all += lLobbyStatus + std::string(MS_DATA_DELIMITER);
      all += lShowLobbyOnList + std::string(MS_DATA_DELIMITER);
      all += std::to_string(i) + std::string(MS_DATA_DELIMITER);
      all += lMaxPlayers + std::string(MS_DATA_DELIMITER);
      all += lCurrentPlayers + std::string(MS_DATA_DELIMITER);
      all += lGameMode + std::string(MS_DATA_DELIMITER);
      all += lServerAddress + std::string(MS_DATA_DELIMITER);
      std::cout << "getLobbyList() lobby i="  << i <<  " data=" << all << std::endl;
    }
    return all;
  }

  void FluffyDatabase::printTime(std::string str , const FluffyMultiplayer::TimeAndDate& time)
  {
    std::cout << str << " Year: " << time.year << ", Month: " << time.month << ", Day: " << time.day
          << ", Hour: " << time.hour << ", Minute: " << time.minute << ", Second: " << time.second << std::endl;
  }

  FluffyMultiplayer::TimeAndDate FluffyDatabase::convertDatabaseTimeStamp(std::string time)
  {
    std::tm tm = {};
    strptime(time.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
    return FluffyMultiplayer::TimeAndDate {1900 + tm.tm_year, 1 + tm.tm_mon,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec};
  }

  FluffyMultiplayer::TimeAndDate FluffyDatabase::getCurrentTime()
  {
    // Get current time
    time_t now = time(0);
    tm* ltm = localtime(&now);

    // Extract current time components
    return FluffyMultiplayer::TimeAndDate {1900 + ltm->tm_year, 1 + ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec};
  }

  int FluffyDatabase::reloginClient(const FluffyMultiplayer::LoginClientData& client, std::string& outputIdentity)
  {
    try
    {
      std::cout << "relogin client identity = " << client.oldIdentity << std::endl;

      //search for that oldIdentity from fm_client_login
      std::string basic_query = "SELECT clientId FROM fm_client_login WHERE identity='";
      basic_query += client.oldIdentity + "';";
      std::string result = search_in_db(basic_query,false);

      if(result.length()<MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH)
        return MS_ERROR_FAILED_TO_RELOGIN; //98% chance to login not found because in some case maybe database is not abled to return query's response.


      // set client id,        jump 4 charecter because of field title for example is:  id=123

      int clientId = FluffyMultiplayer::convertStringToInt(result.substr(9,result.length()));
      if(clientId<=0)
        return MS_ERROR_FAILED_TO_RELOGIN; //failed to get client id


      //search for that oldIdentity from fm_client_login
      basic_query = "SELECT loginDate FROM fm_client_login WHERE identity='";
      basic_query += client.oldIdentity + "';";
      result = search_in_db(basic_query,false);


      // set loginDate        jump 4 charecter because of field title for example is:  id=123
      std::string date = result.substr(10,result.length()-1);
      if(date.empty())
        return MS_ERROR_FAILED_TO_RELOGIN; //failed to get loginDate


      //get current time and compare with loginDate + expireDate
      FluffyMultiplayer::TimeAndDate currentDate = getCurrentTime();
      printTime("current time=", currentDate);

      FluffyMultiplayer::TimeAndDate loginDate = convertDatabaseTimeStamp(date);
      printTime("loginDate=",loginDate);

      FluffyMultiplayer::TimeAndDate expireDate
      {
          MS_CLIENT_LOGIN_IDENTITY_EXPIRE_YEARS,
          MS_CLIENT_LOGIN_IDENTITY_EXPIRE_MONTHS,
          MS_CLIENT_LOGIN_IDENTITY_EXPIRE_DAYS,
          MS_CLIENT_LOGIN_IDENTITY_EXPIRE_HOURS,
          MS_CLIENT_LOGIN_IDENTITY_EXPIRE_MINUTES,
          MS_CLIENT_LOGIN_IDENTITY_EXPIRE_SECONDS
      };
      printTime("expireDate=",expireDate);


      if(currentDate.isExpired(loginDate, expireDate))
      {
        std::cout << "identity expired." << std::endl;
        return MS_ERROR_FAILED_TO_RELOGIN_IDENTITY_EXPIRED;
      }


      //relogin success create new identity for that client id
      if(!createSessionForClient(clientId,outputIdentity))
        return MS_ERROR_FAILED_TO_INSERT_CLIENT_IDENTITY;


      return MS_RESPONSE_SUCCESS_LOGIN;
    }
    catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
    }
    return MS_RESPONSE_SUCCESS_LOGIN;
  }

  int FluffyDatabase::getClientIdByIdentity(const std::string& identity)
  {
    std::string basic_query = "SELECT clientId FROM fm_client_login WHERE identity='";
    basic_query += identity + "';";
    std::string clientId = search_in_db(basic_query,false);

    //convert received data into int
    int cid = FluffyMultiplayer::convertStringToInt(clientId.substr(9,clientId.length()-1));
    if(cid>=1)
      return cid;
    return -1; //not found
  }

  int FluffyDatabase::registerClient(const FluffyMultiplayer::RegisterClientData& client, std::string& outputIdentity)
  {
    try
    {
      std::cout << "client info recieved to register is: \nemail=" << client.email << "\nusername=" << client.username << "\npassword=" << client.password << "\nhardwareid=" << client.hardwareId << std::endl;
        //search for that email address.
        std::string basic_query = "SELECT id FROM fm_client WHERE username='";
        basic_query += client.username + "';";
        if(isExists_in_db(basic_query,2))
          return MS_ERROR_FAILED_TO_REGISTER_USERNAME_EXISTS;

        //search for that username
        basic_query = "SELECT id FROM fm_client WHERE email='";
        basic_query += client.email + "';";
        if(isExists_in_db(basic_query,2))
          return MS_ERROR_FAILED_TO_REGISTER_EMIAL_EXISTS;

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
          basic_query += client.username + "';";
          std::string result =  search_in_db(basic_query,false);
          std::cout << "register res=" << result << "\tlen=" << result.length()  << "\tstrid=" << result.substr(3,result.length()-1) << std::endl;
          int clientId = FluffyMultiplayer::convertStringToInt(result.substr(3,result.length()-1)); //count of charecter id + a '=' is 3 so result is on [3]
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
    catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
    }
    return MS_ERROR_FAILED_TO_REGISTER_CLIENT; //idk whats happend..
  }

  int FluffyDatabase::loginClient(const FluffyMultiplayer::LoginClientData& client, std::string& outputIdentity)
  {
    try
    {
      if(client.oldIdentity.empty())
      {
        //get client data if username matches
        std::cout << "loginClient will do query, client info:\nusername=" << client.username << "\npassword=" << client.password << "\nhardwareid=" << client.hardwareId << "\nold_identity=" << client.oldIdentity << std::endl;
        std::string basic_query = "SELECT id FROM fm_client WHERE username='";
        basic_query += client.username + "' AND password='";
        basic_query += client.password + "';";
        std::string result = search_in_db(basic_query,false);

        //check result is not empty that means client exists
        if(result.length()<MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH)
          return MS_ERROR_FAILED_TO_LOGIN_INCORRECT;


        // set client id,        jump 4 charecter because of field title for example is:  id=123
        int clientId = FluffyMultiplayer::convertStringToInt(result.substr(3,result.length()-1));
        if(clientId<=0)
          return MS_ERROR_FAILED_TO_LOGIN_CLIENT; //failed to get client id



        // get banned status by username
        basic_query = "SELECT isBanned FROM fm_client WHERE username='";
        basic_query += client.username + "';";
        result = search_in_db(basic_query,false);

        // set client ban status         jump 9 charecter because of filed title for example is: isBanned=0
        bool isBanned = static_cast<bool>(FluffyMultiplayer::convertStringToInt(result.substr(9,result.length()-1))); // isBanned= [9], boolain is just one chartecter 0 or 1
        if(isBanned)
          return MS_ERROR_FAILED_TO_LOGIN_BANNED;


        //generate Identity for that id
        if(!createSessionForClient(clientId,outputIdentity))
          return MS_ERROR_FAILED_TO_INSERT_CLIENT_IDENTITY;

        //check generated Identity
        if(outputIdentity.length()<MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH)
        {
          outputIdentity = "";
          return MS_ERROR_FAILED_TO_LOGIN_CLIENT;
        }
        else
          return MS_RESPONSE_SUCCESS_LOGIN;
      }
      return MS_ERROR_FAILED_TO_LOGIN_CLIENT;
    }
    catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
    }
    return MS_ERROR_FAILED_TO_LOGIN_CLIENT;
  }

  int FluffyDatabase::createLobby(const FluffyMultiplayer::CreateLobbyData& lobbyInfo, std::string& outputServerIpPort)
  {
      try
      {
        int ownerId = getClientIdByIdentity(lobbyInfo.identity);
        std::cout << "createlobby ownerId (clientId by identity)=" << ownerId << std::endl;
        if(ownerId != -1)
        {
          if(isOwnLobby(ownerId))
           return MS_ERROR_FAILED_TO_LOBBY_CREATION_CANT_OWN_TWO_LOBBY;
          if(!isLobbyCreationLimited(ownerId))
          {

             // ***************
             //those codes to ask a free server ip and port from API or anywhere else.
             //at this time there is no API or etc to select server so lets set default ip port
             std::string selected_server_ip = MS_CREATE_LOBBY_DEFAULT_SERVER_IP;
             std::string selected_server_port = MS_CREATE_LOBBY_DEFAULT_SERVER_PORT;
             // ***************

             std::string basic_query = "INSERT INTO fm_lobby (gameMode,maxPlayers,password,owner,textChatForbidden,voiceChatForbidden,specterForbidden,server_ip,server_port) VALUES('";
             basic_query += std::to_string(lobbyInfo.gameMode) + "', '" +
              std::to_string(lobbyInfo.maxPlayers) + "', '" +
              lobbyInfo.password  + "', '" +
              std::to_string(ownerId) + "', '" +
              std::to_string(lobbyInfo.textChatForbidden) + "', '" +
              std::to_string(lobbyInfo.voiceChatForbidden) + "', '" +
              std::to_string(lobbyInfo.specterForbidden) + "', '" +
              selected_server_ip + "' ,'" +
              selected_server_port + "');";
             if(query_to_db(basic_query))
             {
               //get create lobby id via owner id, add that owner id into lobby
               basic_query = "INSERT INTO fm_client_in_lobby ( clientId, lobbyId ) VALUES('";
               basic_query += std::to_string(ownerId) + "', (SELECT  id FROM fm_lobby WHERE owner='";
               basic_query += std::to_string(ownerId) + "'));";
               if(query_to_db(basic_query))
               {
                 //get lobby address
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
                return MS_ERROR_FAILED_TO_CREATE_LOBBY;//failed to add client into lobby
             }
             else
               return MS_ERROR_FAILED_TO_CREATE_LOBBY; //failed to insert lobby
          }
          else
           return MS_ERROR_FAILED_TO_LOBBY_CREATION_FORBIDDEN_FOR_YOU;
        }
        else
         return MS_ERROR_FAILED_TO_LOBBY_CREATION_INVALID_IDENTITY; // or maybe internal error: failed to get client id
      }
      catch (std::exception& e)
      {
        std::cerr << "Exception: " << e.what() << std::endl;
      }

      return MS_ERROR_FAILED_TO_CREATE_LOBBY; //
  }



  bool FluffyDatabase::isOwnLobby(const int& ownerId)
  {
    std::string basic_query = "SELECT lobbyStatus FROM fm_lobby WHERE owner='";
    basic_query += std::to_string(ownerId) + "';";
    bool own = isExists_in_db(basic_query,11);
    std::cout << "isOwnLobby() own=" << own << std::endl;
    return own;
  }

  bool FluffyDatabase::isLobbyCreationLimited(const int& clientId)
  {
      std::string basic_query = "SELECT isLobbyCreationLimited FROM fm_client WHERE id='";
      basic_query += std::to_string(clientId) + "';";
      std::string result = search_in_db(basic_query,false);
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
    basic_query += std::to_string(clientId) + "';";
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
  int FluffyDatabase::search_in_db_callback_nofield(void* data, int argc, char** argv, char** azColName)
  {
      std::string* _result = static_cast<std::string*>(data);
      for (int i = 0; i < argc; i++)
      {
          std::cout << "db search noField i=" << i  << "\t"<< azColName[i] << '=' << (argv[i] ? argv[i] : "NULL") << std::endl;
          *_result +=  (argv[i] ? argv[i] : "NULL");
      }
      std::cout << std::endl;
      return 0;
  }

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

  std::string FluffyDatabase::search_in_db(const std::string& _q, bool withoutFieldName=false)
  {
      char* errMsg;
      char* final_query = new char[_q.length() + 1];
      std::strcpy(final_query, _q.c_str());

      std::string result;
      int rc;

      if(withoutFieldName)
        rc = sqlite3_exec(db, final_query, &FluffyDatabase::search_in_db_callback_nofield, &result, &errMsg);
      else
        rc = sqlite3_exec(db, final_query, &FluffyDatabase::search_in_db_callback, &result, &errMsg);

      delete[] final_query;

      if (rc != SQLITE_OK)
      {
          std::cout << "(search_in_db) SQL search error: " << errMsg << "\tquery=" << _q << std::endl;
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
        *_result += azColName[i];
        *_result += '=';
        *_result +=  (argv[i] ? argv[i] : "NULL");
        *_result += "\n";
    }
    std::cout << std::endl;
    return 0;
  }
  bool FluffyDatabase::isExists_in_db(std::string& _q, int lengthField)
  {
    char* final_query = new char[_q.length()+1];
    std::strcpy(final_query, _q.c_str());

    std::string result;
    int rc = sqlite3_exec(db, final_query, &FluffyDatabase::isExists_in_db_callback, &result , &errMsg);

    bool isExists=false;
    lengthField++; //because of charecter '='

    std::cout << "isExists_in_db() result.len=" << result.length() << " lengthField=" << lengthField << std::endl;
    std::cout << "isExists_in_db() result= " << result << std::endl;
    if(result.length() > lengthField)
      isExists=true;

    final_query = nullptr;
    delete[] final_query;

    if (rc != SQLITE_OK)
    {
        std::cout << "(isExists_in_db) SQL search error: " << errMsg << "\tquery=" << _q << std::endl;
        sqlite3_free(errMsg);
    }

    return isExists;
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
