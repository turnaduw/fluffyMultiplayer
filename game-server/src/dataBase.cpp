#include "../include/dataBase.h"


namespace FluffyMultiplayer
{

    void init(std::string filename)
    {
      log.init(DATABASE_LOG_FILENAME,DATABASE_PRINT_LOGS_LEVEL);
      int rc = sqlite3_open(DATABASE_FILENAME, &db);
      if(rc)
        log.print("can not open database: "+sqlite3_errmsg(db)+"\n", FluffyMultiplayer::LogType::Error);
      else
        log.print("Database opened/created fine.\n", FluffyMultiplayer::LogType::Success);
    }


    void close()
    {
      int rc = sqlite3_close(db);
      if(rc)
        log.print("error while close database: "+sqlite3_errmsg(db)+"\n", FluffyMultiplayer::LogType::Error);
      else
        log.print("database closed fine.\n", FluffyMultiplayer::LogType::Success);

      log.close();
      db=nullptr;
      errMsg=nullptr;
      // delete db;
      delete errMsg;
    }

    //database----------
    int DataBase::search_in_db_callback_nofield(void* data, int argc, char** argv, char** azColName)
    {
        std::string* _result = static_cast<std::string*>(data);
        for (int i = 0; i < argc; i++)
        {
            // std::cout << "db search noField i=" << i  << "\t"<< azColName[i] << '=' << (argv[i] ? argv[i] : "NULL") << std::endl;
            // log.print("(search_in_db_callback_nofield): (..convert data to print here..) ", FluffyMultiplayer::LogType::Information);
            *_result +=  (argv[i] ? argv[i] : "NULL");
        }
        // std::cout << std::endl;
        log.print("(search_in_db_callback_nofield): _result="+(*_result)+"\n", FluffyMultiplayer::LogType::Information);

        return 0;
    }

    int DataBase::search_in_db_callback(void* data, int argc, char** argv, char** azColName)
    {
        std::string* _result = static_cast<std::string*>(data);
        for (int i = 0; i < argc; i++)
        {
            // std::cout << "db search i=" << i  << "\t"<< azColName[i] << '=' << (argv[i] ? argv[i] : "NULL") << std::endl;
            // log.print("(search_in_db_callback): (..convert data to print here..) ", FluffyMultiplayer::LogType::Information);
            *_result += azColName[i];
            *_result += '=';
            *_result +=  (argv[i] ? argv[i] : "NULL");
            *_result += "\n";
        }
        // std::cout << std::endl;
        log.print("(search_in_db_callback): _result="+(*_result), FluffyMultiplayer::LogType::Information);

        return 0;
    }

    std::string DataBase::search_in_db(const std::string& _q, bool withoutFieldName=false)
    {
        char* errMsg;
        char* final_query = new char[_q.length() + 1];
        std::strcpy(final_query, _q.c_str());

        std::string result;
        int rc;

        if(withoutFieldName)
          rc = sqlite3_exec(db, final_query, &DataBase::search_in_db_callback_nofield, &result, &errMsg);
        else
          rc = sqlite3_exec(db, final_query, &DataBase::search_in_db_callback, &result, &errMsg);

        delete[] final_query;

        if (rc != SQLITE_OK)
        {
            // std::cout << "(search_in_db) SQL search error: " << errMsg << "\tquery=" << _q << std::endl;
            log.print("(search_in_db): SQL search error: "+errMsg+"\tquery="+_q , FluffyMultiplayer::LogType::Error);
            sqlite3_free(errMsg);
        }
        return result;
    }


    //--------------------
    bool DataBase::query_to_db()
    {
      return query_to_db(queryStr);
    }
    bool DataBase::query_to_db(const std::string& _q)
    {
          bool result=false;
          char* final_query = new char[_q.length()+1];
          std::strcpy(final_query, _q.c_str());

          int rc = sqlite3_exec(db, final_query, nullptr, 0, &errMsg);

          final_query = nullptr;
          delete[] final_query;



          if (rc != SQLITE_OK)
          {
              // std::cout << "(query_to_db) SQL error: " << errMsg << "\tquery=" << _q << std::endl;
              log.print("(query_to_db): SQL error: "+errMsg+"\tquery="+_q , FluffyMultiplayer::LogType::Error);
              sqlite3_free(errMsg);
          }
          else
            result = true;
          return result;
    }

}
