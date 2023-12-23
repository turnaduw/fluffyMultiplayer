#include "../include/log.h"

namespace FluffyMultiplayer
{
  void Log::print(std::string text, FluffyMultiplayer::LogType messageType)
  {
    std::string mtype;
    switch (messageType)
    {
      case FluffyMultiplayer::LogType::Information: mtype = "[INFO] "; break;
      case FluffyMultiplayer::LogType::Error: mtype = "[ERROR] "; break;
      case FluffyMultiplayer::LogType::Warning: mtype = "[WARNING] "; break;
      case FluffyMultiplayer::LogType::Success: mtype = "[SUCCESS] ";break;
      default: mtype = "[?]";break;
    }

    try
    {
      text = mtype + getTime() + " " + text + "\n";
      file << text;

      //print on console
      if(levelPrintOnConsole == FluffyMultiplayer::LogType::All
          || messageType == levelPrintOnConsole)
      {
        std::cout << text;
      }
    }
    catch (std::exception& e)
    {
      if(printOnConsole)
        std::cout << "failed to write on log file.\ttext="<< text;
    }
  }

  std::string Log::getTime()
  {
      // Get current time
      time_t now = time(0);
      tm* ltm = localtime(&now);

      std::string time = "[" + std::to_string(1900 + ltm->tm_year) + "/" +
              std::to_string(1 + ltm->tm_mon) + "/" +
              std::to_string(ltm->tm_mday) + " " +
              std::to_string(ltm->tm_hour) + ":" +
              std::to_string(ltm->tm_min) + ":" +
              std::to_string(ltm->tm_sec) + "]";

      return time;
  }

  Log::Log()
  {

  }

  void Log::init(std::string file, FluffyMultiplayer::LogType level)
  {
    levelPrintOnConsole = level;
    filename = file;
    try
    {
      file.open (filename, std::ofstream::out | std::ofstream::app);
    }
    catch (std::exception& e)
    {
      std::cout << "could not open/create log file." << std::endl;
    }
  }

  void Log::close()
  {
    try
    {
      if(file.is_open())
        file.close();
      else
        std::cout << "file log is not open can not close it." << std::endl;
    }
    catch (std::exception& e)
    {
      std::cout << "could not close log file." << std::endl;
    }
  }

  Log::~Log()
  {

  }


}
