#ifndef H_DATABASE_CLASS
#define H_DATABASE_CLASS

#include <sqlite3.h>
#include <string>
#include <cstring>

//convert string to int
#include <cstdlib>

#include "server-request-response-list.h"

#include "config.h"

#include "dataSecurity.h"
#include "dataTypes.h"


//time for relogin
#include <ctime>


#include <string>

namespace FluffyMultiplayer
{
  class FluffyDatabase
  {
      sqlite3* db;
      char* errMsg = nullptr;
      FluffyMultiplayer::FluffyDataSecurity dataSecurity;
      FluffyMultiplayer::TimeAndDate convertDatabaseTimeStamp(std::string);
      FluffyMultiplayer::TimeAndDate getCurrentTime();
      void printTime(std::string, const FluffyMultiplayer::TimeAndDate&);


    public:
      FluffyDatabase(bool);
      ~FluffyDatabase();


      //------------------------- authication

      int loginClient(const FluffyMultiplayer::LoginClientData&, std::string&);
      int reloginClient(const FluffyMultiplayer::LoginClientData&);

      int registerClient(const FluffyMultiplayer::RegisterClientData&, std::string&);

      int getClientIdByIdentity(const std::string&);
      bool isIdentityExists(const std::string&);

      bool createSessionForClient(const int&,std::string&);


      //------------------------- lobby
      /*
        about function getLobbyList():
        not refrenced because arguman is from config.h
        there is a problem, the query is sending exact password saved
        on database to requester have to remove password and just tell client
        a flag like is that lobby locked or not
      */
      std::string getLobbyList(int);

      int createLobby(const FluffyMultiplayer::CreateLobbyData&, std::string&);

      std::string getLobbyInfoByOwnerId(const int&);

      std::string getLobbyInfo(const int&);

      bool isLobbyCreationLimited(const int&);

      bool isOwnLobby(const int&);


      //------------------------- database
      void initTables();

      static int search_in_db_callback(void* data, int argc, char** argv, char** azColName);
      std::string search_in_db(std::string&);

      static int isExists_in_db_callback(void* data, int argc, char** argv, char** azColName);
      bool isExists_in_db(std::string& _q);

      bool query_to_db(const std::string&);
  };
}


#endif
