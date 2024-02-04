#include <iostream>
#include <string>
#include "include/app.h"
#include "include/dataType.h"

//convert string to int
#include <cstdlib>

int stringToInt(const std::string& str)
{
  const char* c = str.c_str();
  return std::atoi(c);
}


int main(int argc, char** argv)
{
  std::string sIp = std::string(argv[1]); // ip
  unsigned short sPort = static_cast<unsigned short>(stringToInt(std::string(argv[2]))); //port
  std::string sIdentity = std::string(argv[3]);//"WjkT2REaPMwnuiQ4Q0V0iwXB4XzdQsu0uDInzi1enMKgEplczWWHDpvN8OH5";

  //init address
  FluffyMultiplayer::AnAddress serverAddress = {sIp,sPort};
  try
  {
    FluffyMultiplayer::App app;
    app.init(serverAddress,sIdentity);
    app.run(); //main loop is here
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
