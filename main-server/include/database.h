#ifndef H_DATABASE_CLASS
#define H_DATABASE_CLASS

#include <sqlite3.h>
#include <string>
#include <cstring>

//convert string to int
#include <cstdlib>

#include "error-list.h"
#include "internal-error-list.h"
#include "response-list.h"

#include "config.h"


namespace FluffyMultiplayer
{
  class FluffyDatabase
  {
      sqlite3* db;
      char* errMsg = nullptr;
    public:
      FluffyDatabase(bool);
      ~FluffyDatabase();


      //------------------------- authication
      bool isIdentityExists(const std::string&);

      int loginClient(const FluffyMultiplayer::LoginClientData&, std::string&); //write code..

      int registerClient(const FluffyMultiplayer::RegisterClientData&, std::string&);//write..

      int getClientIdByIdentity(const std::string&);

      bool isIdentityUnique(const std::string&); //writecode..

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

      int search_in_db_callback(void* data, int argc, char** argv, char** azColName);
      std::string search_in_db(std::string&);

      int isExists_in_db_callback(void* data, int argc, char** argv, char** azColName);
      bool isExists_in_db(std::string& _q);

      bool query_to_db(const std::string&);
  };
}


#endif
