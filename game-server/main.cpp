#include "./include/app.h"

int main(int argc, char** argv)
{

  // FluffyMultiplayer::LobbyData lobby
  // {
  //     FluffyMultiplayer::App::stringToInt(std::string(argv[1])), //id
  //     FluffyMultiplayer::App::stringToInt(std::string(argv[2])), //maxplayers
  //     FluffyMultiplayer::App::stringToInt(std::string(argv[3])), //gameMode
  //     FluffyMultiplayer::App::stringToInt(std::string(argv[4])), //currentPlayers
  //     FluffyMultiplayer::App::stringToBool(std::string(argv[5])), //voice
  //     FluffyMultiplayer::App::stringToBool(std::string(argv[6])), //ttext
  //     FluffyMultiplayer::App::stringToBool(std::string(argv[7])), //specter
  //     FluffyMultiplayer::App::stringToBool(std::string(argv[8])), //ingame
  //     std::string(argv[9]), //password
  //     static_cast<unsigned short>(FluffyMultiplayer::App::stringToInt(std::string(argv[10]))), //textport
  //     static_cast<unsigned short>(FluffyMultiplayer::App::stringToInt(std::string(argv[11]))), //voiceport
  //     FluffyMultiplayer::App::stringToInt(std::string(argv[12])), //ownerid
  // };

  FluffyMultiplayer::LobbyData lobby
  {
    1,10,0,2,0,0,0,0,"password",DEFAULT_PORT_TEXT,DEFAULT_PORT_VOICE,0
  };

  FluffyMultiplayer::App app;
  app.init(lobby);
  app.run();
  return 0;
}
