#include "./include/app.h"

int main(int argc, char** argv)
{

  FluffyMultiplayer::LobbyData lobby
  {
      argv[1], //id
      argv[2], //maxplayers
      argv[3], //gameMode
      argv[4], //currentPlayers
      argv[5], //voice
      argv[6], //ttext
      argv[7], //specter
      argv[8], //ingame
      argv[9], //password
      argv[10], //textport
      argv[11], //voiceport
      argv[12] //ownerid
  };

  FluffyMultiplayer::App app;
  app.init(lobby);
  app.run();
  return 0;
}
