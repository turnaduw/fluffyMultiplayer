#ifndef H_DATABASE_CLASS
#define H_DATABASE_CLASS

#include <sqlite3.h>
#include <string>
#include <cstring>

#include "dataType.h"

namespace FluffyMultiplayer
{
  class DataBase
  {
      sqlite3* db;
      char* errMsg = nullptr;
      FluffyMultiplayer::TimeAndDate convertDatabaseTimeStamp(std::string);
      FluffyMultiplayer::TimeAndDate getCurrentTime();
      void printTime(std::string, const FluffyMultiplayer::TimeAndDate&);

    public:
      DataBase()
      {

      }
      ~DataBase()
      {

      }

      static int search_in_db_callback_nofield(void* data, int argc, char** argv, char** azColName);
      static int search_in_db_callback(void* data, int argc, char** argv, char** azColName);
      std::string search_in_db(const std::string&,bool withoutFieldName);

      static int isExists_in_db_callback(void* data, int argc, char** argv, char** azColName);
      bool isExists_in_db(std::string& _q, int lengthField);

      bool query_to_db(const std::string&);
  };
}


#endif
