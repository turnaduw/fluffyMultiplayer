#include "../include/app.h"

namespace FluffyMultiplayer
{

  void App::init()
  {
    log.init(LOG_FILE,PRINT_LOGS_LEVEL);
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

    //process text requests
    FluffyMultiplayer::SocketReceiveData currentItem;
    FluffyMultiplayer::AnAddress sender;
    std::string receivedData;
    bool elementProcessed;
    std::string basic_query;

    for(int i=0; i<receivedTextDataList.size(); i++)
    {
      currentItem = receivedTextDataList.front();
      elementProcessed=false;
      receivedData = currentItem.data;
      sender = currentItem.sender;
      log.print("sender="+sender.getAsString()+
          "received data="+receiveData, FluffyMultiplayer::LogType::Information);
      udp::endpoint receiverEndpoint(sender.ip,sender.port);

      if(receivedData.length()>MS_RECEIVED_DATA_MINIMUM_LENGTH)
        ds.decryptData(receivedData);

      if(ds.isSQLCodeIncluded(receivedData))
        ds.removeSQLCodeFromData(receivedData);



      log.print("process currentItem.code="
            +std::to_string(currentItem.code)+";~;",
            FluffyMultiplayer::LogType::Information);


      /*
      have to process connect and reconenct dedicated
      because if leave it will check connection and these
      requests (are not exsits or ..) will drop
      */
      if(!checkConnection(sender))
      {
        if(currentItem.code == REQUEST_CONNECT_TO_LOBBY)
        {
          //check for identity and get client id
          //if is not banned then add to connected players
        }
        else if(currentItem.code == REQUEST_RECONNECT_TO_LOBBY)
        {

        }
        else
        {
          //response connection not exsits...
          elementProcessed=true;
          receivedTextDataList.pop();
        }
      }
      else
      {
          //connection is ok and process all requests except connect to lobby
          switch (currentItem.code)
          {
            case REQUEST_DISCONNECT_FROM_LOBBY:
            {

            }break;

            case REQUEST_JOIN_TO_LOBBY:
            {

            }break;

            case REQUEST_GET_LOBBY_SETTINGS:
            {

            }break;

            case REQUEST_UPDATE_LOBBY_SETTINGS:
            {

            }break;

            case REQUEST_START_GAME:
            {

            }break;

            case REQUEST_STOP_GAME:
            {

            }break;

            case REQUEST_DELETE_LOBBY:
            {

            }break;

            case REQUEST_KICK_PLAYER:
            {

            }break;

            case REQUEST_BAN_PLAYER:
            {

            }break;

            case REQUEST_TRANSFER_LOBBY_OWNERSHIP:
            {

            }break;

            case REQUEST_SEND_TEXT_CHAT:
            {

            }break;

            case REQUEST_SEND_VOICE_CHAT:
            {

            }break;

            case REQUEST_ENABLE_VOICE_CHAT:
            {

            }break;

            case REQUEST_DISABLE_VOICE_CHAT:
            {

            }break;

            default:
            {
              if(currentGameMode!=nullptr)
              {
                log.print("unknown request code passing it to gamemode", FluffyMultiplayer::LogType::Information);
                currentGameMode = currentGameMode->process(currentItem);
              }
              else
                log.print("unknown request code and gamemode is nullptr", FluffyMultiplayer::LogType::Warning);
            }

          }

      }
    }

    if(!elementProcessed)
      receivedTextDataList.pop();

    //process voice requests
  }


  bool addPlayerToVoiceChat(); //enalbe his voiceChat
  bool removePlayerFromVoiceChat(); //disable his voiceChat


  void App::run()
  {
    while(true)
    {
      currentGameMode = process();
    }
  }

  bool App::checkConnection(const FluffyMultiplayer::AnAddress& address)
  {
    for(FluffyMultiplayer::AnAddress e : connectedPlayers.address)
    {
      if(e == address)
        return true;
    }
    return false;
  }


  //convert
  FluffyMultiplayer::TimeAndDate App::stringToTime(const std::string& time)
  {
      std::tm tm = {};
      strptime(time.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
      return FluffyMultiplayer::TimeAndDate {1900 + tm.tm_year, 1 + tm.tm_mon,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec};
  }

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
  bool App::checkEnteredPassword(const std::string& password)
  {
    if(lobby.password == password)
      return true;
    return false;
  }

  bool App::textChat(const std::string& text)
  {

  }

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
