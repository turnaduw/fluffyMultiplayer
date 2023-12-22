#ifndef H_APP_CLASS
#define H_APP_CLASS

#include <iostream>
#include <string>
#include <queue>

#include "gameMode.h"
#include "dataType.h"
#include "udpSocket.h"
#include "dataSecurity.h"
#include "config.h"
#include "dataBase.h"
#include "log.h"

#include "gameModes.h"


#include "lobby-request-response-list.h"

namespace FluffyMultiplayer
{
  class App
  {
    private:
      FluffyMultiplayer::DataBase db;
      FluffyMultiplayer::Log log;
      FluffyMultiplayer::DataSecurity ds;

      std::queue<FluffyMultiplayer::Player> connectedPlayers;
      std::queue<FluffyMultiplayer::BanList> bannedPlayers;
      std::queue<FluffyMultiplayer::AnAddress> blockedAddresses; //for spam

      std::queue<FluffyMultiplayer::Player> inGamePlayers;
      std::queue<FluffyMultiplayer::Player> lobbySpecters;
      FluffyMultiplayer::LobbyData lobbyData;
      FluffyMultiplayer::GameMode* currentGameMode;

      //receive and send data.
      FluffyMultiplayer::UdpSocket socketText;
      FluffyMultiplayer::UdpSocket socketVoice;
      boost::asio::io_context io_context_text;
      boost::asio::io_context io_context_voice;
      std::queue<FluffyMultiplayer::SocketReceiveData> receivedTextDataList;
      std::queue<FluffyMultiplayer::SocketReceiveData> receivedVoiceDataList;
      std::queue<FluffyMultiplayer::SocketSendData> sendVoiceDataList;
      std::queue<FluffyMultiplayer::SocketSendData> sendTextDataList;


      void sendData();
      void receiveData();

    public:
      boost::thread threadSend;
      boost::thread threadReceive;

      App(FluffyMultiplayer::lobbyData _lobby): socketText(io_context_text, _lobby.textPort),
             socketVoice(io_context_voice, _lobby.voicePort)
      {
          currentGameMode=nullptr;
          lobbyData = _lobby;
          threadSend = boost::thread(&FluffyMultiplayer::App::sendData, this);
          threadReceive = boost::thread(&FluffyMultiplayer::App::receiveData, this);
      }

      ~App()
      {

      }

      void init(FluffyMultiplayer::LobbyData);
      void run();
      FluffyMultiplayer::GameMode* process();

      bool checkConnection(const FluffyMultiplayer::AnAddress&);

      //convert
      FluffyMultiplayer::TimeAndDate stringToTime(const std::string&);
      FluffyMultiplayer::Player stringToPlayer(const std::string&);
      FluffyMultiplayer::LobbyData stringToLobbyData(const std::string&);
      FluffyMultiplayer::AnAddress stringToAnAddress(const std::string&);
      int stringToInt(const std::string&);
      bool stringToBool(const std::string&);


      //player
      bool connectPlayer(FluffyMultiplayer::Player&);
      bool disconnectPlayer(FluffyMultiplayer::Player&);
      bool reconnectPlayer(FluffyMultiplayer::Player&);
      bool checkEnteredPassword(const std::string&);
      bool textChat(const std::string&);
      bool voiceChat(const std::string&);
      bool kickPlayer(FluffyMultiplayer::Player&, const std::string& reason);
      bool banPlayer(FluffyMultiplayer::Player&, const std::string& reason, FluffyMultiplayer::TimeAndDate duration);
      bool playerAsSpecter(FluffyMultiplayer::Player&);
      bool addPlayerToVoiceChat(); //enalbe his voiceChat
      bool removePlayerFromVoiceChat(); //disable his voiceChat


      //lobby
      bool transferLobbyOwnerShip(FluffyMultiplayer::Player& newOwner);
      std::string getLobbySettings();
      bool updateLobby(FluffyMultiplayer::LobbyData);
      std::string lobbyInfo(); //will report lobby players and details for first time to connected player
      bool startGame();
      bool stopGame();
      bool deleteLobby();
  };
}

#endif
