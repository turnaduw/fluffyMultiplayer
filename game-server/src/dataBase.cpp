#include "../include/dataBase.h"


namespace FluffyMultiplayer
{

    //database----------
    int DataBase::search_in_db_callback_nofield(void* data, int argc, char** argv, char** azColName)
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

    int DataBase::search_in_db_callback(void* data, int argc, char** argv, char** azColName)
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
            std::cout << "(search_in_db) SQL search error: " << errMsg << "\tquery=" << _q << std::endl;
            sqlite3_free(errMsg);
        }
        return result;
    }



    //----------
    int DataBase::isExists_in_db_callback(void* data, int argc, char** argv, char** azColName)
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
    bool DataBase::isExists_in_db(std::string& _q, int lengthField)
    {
      char* final_query = new char[_q.length()+1];
      std::strcpy(final_query, _q.c_str());

      std::string result;
      int rc = sqlite3_exec(db, final_query, &DataBase::isExists_in_db_callback, &result , &errMsg);

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
              std::cout << "(query_to_db) SQL error: " << errMsg << "\tquery=" << _q << std::endl;
              sqlite3_free(errMsg);
          }
          else
            result = true;
          return result;
    }

}
