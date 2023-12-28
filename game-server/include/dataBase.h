#ifndef H_DATABASE_CLASS
#define H_DATABASE_CLASS

#include <sqlite3.h>
#include <string>
#include <cstring>

#include "dataType.h"
#include "log.h"


namespace FluffyMultiplayer
{
  class DataBase
  {
      sqlite3* db;
      char* errMsg = nullptr;
      FluffyMultiplayer::Log log;
      FluffyMultiplayer::TimeAndDate convertDatabaseTimeStamp(std::string);
      FluffyMultiplayer::TimeAndDate getCurrentTime();
      void printTime(std::string, const FluffyMultiplayer::TimeAndDate&);

    public:
      std::string queryStr; //to avoid define every time when want call dbQueryStr
      void init(std::string filename);
      void close();

      DataBase()
      {

      }
      ~DataBase()
      {

      }

      static int search_in_db_callback_nofield(void* data, int argc, char** argv, char** azColName);
      static int search_in_db_callback(void* data, int argc, char** argv, char** azColName);
      std::string search_in_db(const std::string&,bool withoutFieldName);

      bool query_to_db(const std::string&);
      bool query_to_db();

  };
}


#endif
