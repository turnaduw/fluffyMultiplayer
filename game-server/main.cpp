#include "./include/app.h"

//convert string to int
#include <cstdlib>

int stringToInt(const std::string& str)
{
  const char* c = str.c_str();
  return std::atoi(c);
}

bool stringToBool(const std::string& str)
{
  bool result=false;
  const char* c = str.c_str();
  result = static_cast<bool>(std::atoi(c));
  return result;
}
int main(int argc, char** argv)
{
  if (argc < 13)
  {
    int x;
    std::cerr << "Usage: " << argv[0] << " id maxplayers gameMode currentPlayers voice ttext specter ingame password textport voiceport ownerid\n";
    std::cin>> x;
    return 1;
  }

  FluffyMultiplayer::LobbyData lobby
  {
      stringToInt(std::string(argv[1])), //id
      stringToInt(std::string(argv[2])), //maxplayers
      stringToInt(std::string(argv[3])), //gameMode
      stringToInt(std::string(argv[4])), //currentPlayers
      stringToBool(std::string(argv[5])), //voice
      stringToBool(std::string(argv[6])), //ttext
      stringToBool(std::string(argv[7])), //specter
      stringToBool(std::string(argv[8])), //ingame
      std::string(argv[9]), //password
      static_cast<unsigned short>(stringToInt(std::string(argv[10]))), //textport
      static_cast<unsigned short>(stringToInt(std::string(argv[11]))), //voiceport
      stringToInt(std::string(argv[12])), //ownerid
  };

  // FluffyMultiplayer::LobbyData lobby
  // {
  //   1,10,0,2,0,0,0,0,"password",DEFAULT_PORT_TEXT,DEFAULT_PORT_VOICE,0
  // };

  FluffyMultiplayer::App app;
  app.init(lobby);
  app.run();
  return 0;
}
