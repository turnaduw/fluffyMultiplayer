#ifndef H_LOG_CLASS
#define H_LOG_CLASS


#include "dataType.h"

#include <string>
#include <iostream>


//work with file
#include <fstream>

//current time
#include <ctime>


namespace FluffyMultiplayer
{
  class Log
  {
    private:
      std::string filename;
      FluffyMultiplayer::LogType levelPrintOnConsole;
      std::string getTime();

      std::ofstream file;

    public:
      void print(std::string, FluffyMultiplayer::LogType);

      void init(std::string, FluffyMultiplayer::LogType);
      void close();
      Log();
      ~Log();
  };
}

#endif
