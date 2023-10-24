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

      void initTables();
  };
}


#endif
