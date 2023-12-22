#include "../include/app.h"

namespace FluffyMultiplayer
{

  void App::init()
  {
    switch (lobbyData.gameMode)
    {
      case 1:
        currentGameMode = new FluffyMultiplayer::GameModeMensch; break;
      default:
        currentGameMode = nullptr; break;
    }
  }

  FluffyMultiplayer::GameMode* App::process()
  {
    FluffyMultiplayer::SocketReceiveData currentItem;
    for()
  }

  void App::run()
  {
    while(true)
    {
      currentGameMode = process();
    }
  }

  bool App::checkConnection(FluffyMultiplayer::AnAddress address)
  {
    for(FluffyMultiplayer::AnAddress e : connectedPlayers.address)
    {
      if(e == address)
        return true;
    }
    return false;
  }


  //convert
  FluffyMultiplayer::TimeAndDate App::stringToTime(const std::string&);
  FluffyMultiplayer::Player App::stringToPlayer(const std::string&);
  FluffyMultiplayer::LobbyData App::stringToLobbyData(const std::string&);
  FluffyMultiplayer::AnAddress App::stringToAnAddress(const std::string&);
  int App::stringToInt(const std::string&);
  bool App::stringToBool(const std::string&);


  //player
  bool App::connectPlayer(FluffyMultiplayer::Player& p)
  {
    connectedPlayers.push(p);
    log.print("id(" + p.id + ") name(" + p.name + ") ip(" + p.address.getAsString() + ") "
      + "connected to the lobby.", FluffyMultiplayer::LogType::Information);
    socketText.broadcast
    (
        FluffyMultiplayer::SocketSendData
        {
          PLAYER_CONNECTED,
          "id(" + p.id + ") name(" + p.name + ") ip(" + p.address.getAsString() + ")",
          &connectedPlayers,
          nullptr
        }
    );
  }
  bool App::disconnectPlayer(FluffyMultiplayer::Player&)
  {

  }

  bool App::reconnectPlayer(FluffyMultiplayer::Player&);
  bool App::checkEnteredPassword(const std::string&);
  bool App::textChat(const std::string&);
  bool App::voiceChat(const std::string&);
  bool App::kickPlayer(FluffyMultiplayer::Player&, const std::string& reason);
  bool App::banPlayer(FluffyMultiplayer::Player&, const std::string& reason, FluffyMultiplayer::TimeAndDate duration);
  bool App::playerAsSpecter(FluffyMultiplayer::Player&);

  //lobby
  bool App::transferLobbyOwnerShip(FluffyMultiplayer::Player& newOwner);
  std::string App::getLobbySettings();
  bool App::updateLobby(FluffyMultiplayer::LobbyData);
  std::string App::lobbyInfo(); //will report lobby players and details for first time to connected player
  bool App::startGame();
  bool App::stopGame();
  bool App::deleteLobby();
}
