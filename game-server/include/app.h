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




namespace FluffyMultiplayer
{
  class App
  {
    private:
      FluffyMultiplayer::DataBase db;

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
      boost::thread threadSend;
      boost::thread threadReceive;
      boost::asio::io_context io_context_text;
      boost::asio::io_context io_context_voice;
      std::queue<FluffyMultiplayer::SocketReceiveData> receivedTextDataList;
      std::queue<FluffyMultiplayer::SocketReceiveData> receivedVoiceDataList;
      std::queue<FluffyMultiplayer::SocketSendData> sendVoiceDataList;
      std::queue<FluffyMultiplayer::SocketSendData> sendTextDataList;


    public:
      App(): socketText(io_context_text, DEFAULT_PORT_TEXT),
             socketVoice(io_context_voice, DEFAULT_PORT_VOICE)
      {

      }

      ~App()
      {

      }

      void init(int lobbyId);
      void run();
      FluffyMultiplayer::GameMode* process();

      bool checkConnection(FluffyMultiplayer::AnAddress);


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
