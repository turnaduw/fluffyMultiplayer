#ifndef H_APP_CLASS
#define H_APP_CLASS

#include <iostream>
#include <string>
#include <queue>
#include <boost/thread.hpp>
#include <vector>

#include "dataType.h"
#include "udpSocket.h"
#include "dataSecurity.h"
#include "config.h"
#include "dataBase.h"
#include "log.h"

//remove from vector
#include<bits/stdc++.h>


#include "lobby-request-response-list.h"

namespace FluffyMultiplayer
{
  class GameModeMensch; // Forward declaration
  class GameMode; // Forward declaration
  class App
  {
    private:
      FluffyMultiplayer::DataBase db;

      FluffyMultiplayer::Log log;
      FluffyMultiplayer::DataSecurity ds;

      std::vector<FluffyMultiplayer::AnAddress> connectedPlayers;
      std::vector<FluffyMultiplayer::BanList> bannedPlayers;
      std::vector<FluffyMultiplayer::AnAddress> blockedAddresses; //for spam

      FluffyMultiplayer::LobbyData lobbyData;
      FluffyMultiplayer::GameMode* currentGameMode;
      bool gameIsRunning; //a flag stop or start game, and know that joint user is player in lobby or specter
      bool appIsRunning; //a flag close or continue app

      //receive and send data.
      FluffyMultiplayer::UdpSocket* socketText;
      FluffyMultiplayer::UdpSocket* socketVoice;
      boost::asio::io_context io_context_text;
      boost::asio::io_context io_context_voice;

      std::queue<FluffyMultiplayer::SocketReceiveData> receivedVoiceDataList;
      std::queue<FluffyMultiplayer::SocketSendData> sendVoiceDataList;

      boost::mutex sendTextDataListMutex;
      boost::mutex sendVoiceDataListMutex;

      /*to avoid create every time an object from type
        e.g: SocketSendData while want push into queue<SocketSendData> create once here*/
      FluffyMultiplayer::SocketSendData sendTemp;
      FluffyMultiplayer::SocketReceiveData receiveTemp;
      FluffyMultiplayer::Player tempPlayer;


      void sendData();
      void receiveData();

      //data splitters
      std::vector<int> dataIndexes(const std::string& data, const std::string& delimiter) const;
      std::vector<std::string> dataSeparator(const std::string& data, std::string delimiter, int startIndex);
      FluffyMultiplayer::SocketReceiveData unpackData(std::string&); //remove request code and last delimiter and closer from received data

    public:
      boost::thread threadReceive;


      //define these in public to be accessable from gameModes
      std::vector<FluffyMultiplayer::Player> inLobbyPlayers;
      std::vector<FluffyMultiplayer::Player> lobbySpecters;
      std::queue<FluffyMultiplayer::SocketReceiveData> receivedTextDataList;
      std::queue<FluffyMultiplayer::SocketSendData> sendTextDataList;


      App();
      ~App();

      void init(FluffyMultiplayer::LobbyData);
      void run();
      void process();
      void processVoice();
      void processText();


      void safePushToList(bool);
      void response(int code,
                    FluffyMultiplayer::AnAddress receiver,
                    bool isVoiceData);

      void response(int code,
                    std::string data, FluffyMultiplayer::AnAddress receiver,
                    bool isVoiceData);


      void response(int code,
                    const std::vector<FluffyMultiplayer::Player>* receivers,
                    const std::vector<FluffyMultiplayer::Player>* except,
                    bool isVoiceData);


      void response(int code, std::string data,
                    const std::vector<FluffyMultiplayer::Player>* receivers,
                    const std::vector<FluffyMultiplayer::Player>* except,
                    bool isVoiceData);


      //connection
      bool isConnectionExists(const FluffyMultiplayer::AnAddress&) const;
      bool isConnectionBlocked(const FluffyMultiplayer::AnAddress&) const;

      //convert
      FluffyMultiplayer::AnAddress stringToAnAddress(const std::string&) const;
      static int stringToInt(const std::string&);
      static bool stringToBool(const std::string&);


      //player
      bool connectPlayer(FluffyMultiplayer::AnAddress&);
      bool disconnectPlayer(FluffyMultiplayer::AnAddress&);
      void updatePlayerVoiceChatStatus(const int&, bool);
      int getIndexPlayerInLobbyByAddress(const FluffyMultiplayer::AnAddress&) const;
      bool isIdBannedFromLobby(const int& id) const;
      std::string getPlayerUsernameById(const int&) const;
      bool isPlayerIdExistsOnLobby(const int&) const;
      bool doesItHavePermission(const FluffyMultiplayer::AnAddress&);
      FluffyMultiplayer::AnAddress getPlayerAddressById(const int&) const;
      int getSenderId(const FluffyMultiplayer::AnAddress&) const;
      void prepareData(FluffyMultiplayer::SocketReceiveData&);
      bool isPlayerOwner(int);
      bool isIdExistsInLobby(int);
      void kickOutPlayerFromLobby(int);
      void destroyLobby();
      void changeOwner(const int&);

      //lobby
      bool startGame();
      bool stopGame();
  };
}

#endif
