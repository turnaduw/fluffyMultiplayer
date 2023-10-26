#ifndef H_DATABASE_CLASS
#define H_DATABASE_CLASS

#include <sqlite3.h>
#include <string>
#include <cstring>

//convert string to int
#include <cstdlib>


namespace FluffyMultiplayer
{
  class FluffyDatabase
  {
      sqlite3* db;
      char* errMsg = nullptr;
    public:
      FluffyDatabase(bool);
      ~FluffyDatabase();

      std::string getLobbyInfo(const int&); //write code..
      std::string getLobbyList(int); //not refrenced because arguman is from config.h      //write code..
      bool isIdentityExists(const std::string&); //write code..
      int loginClient(const FluffyMultiplayer::LoginClientData&, std::string&); //generateIdentity then checkForUniq then return that id //write code..
      int createLobby(const FluffyMultiplayer::CreateLobbyData&, std::string&); //write code..
      int registerClient(const FluffyMultiplayer::RegisterClientData&, std::string&);//write..
      void initTables();
  };
}


#endif
