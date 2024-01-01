#ifndef H_APP_CLASS
#define H_APP_CLASS

#include <iostream>

#include <SFML/Graphics.hpp>
#include <queue>
#include <array>

#include <boost/thread.hpp>

#include <boost/asio.hpp>
using boost::asio::ip::udp;

#include "config.h"
#include "dataType.h"
#include "udpSocket.h"
#include "dataSecurity.h"
#include "log.h"
#include "gameMode.h"

#include "appState.h"
#include "states.h"


//clear identity
#include <fstream>
#include <cstdio>

//open application by cmd
#include <cstdlib>


//notification system
#include "./uiComponents/notificationBox.h"

namespace FluffyMultiplayer
{
  class AppState;
  class App
  {
    private:
      bool gameIsRunning; //a flag stop or start game
      bool appIsRunning; //a flag close or continue app

      FluffyMultiplayer::Log log;
      FluffyMultiplayer::DataSecurity ds;

      std::string identity;
      FluffyMultiplayer::LobbyData lobby;
      FluffyMultiplayer::AppState* currentState;
      FluffyMultiplayer::GameMode* currentGameMode;

      //voice chat
      FluffyMultiplayer::VoiceChat voiceChat;

      //data list from or to network
      std::queue<FluffyMultiplayer::SocketReceiveData> receivedTextDataList;
      std::queue<FluffyMultiplayer::SocketReceiveData> receivedVoiceDataList;
      std::queue<FluffyMultiplayer::SocketSendData> sendVoiceDataList;
      std::queue<FluffyMultiplayer::SocketSendData> sendTextDataList;

      //network and data froms
      boost::asio::io_context ioContextVoice;
      FluffyMultiplayer::UdpSocket* socketVoice;

      boost::asio::io_context ioContextText;
      FluffyMultiplayer::UdpSocket* socketText;

      void sendData();
      void receiveData();

    public:
      boost::thread receive_thread;
      boost::thread send_thread;

      //notifications
      std::queue<FluffyMultiplayer::NotificationData> notificationQueue;
      FluffyMultiplayer::NotificationBox notificationBox;
      //mouse event handel variable to delecre once, not per loop delcre
      sf::Vector2f mousePosition;

      sf::RenderWindow appWindow;
      App(): appWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, WINDOW_STYLE)
      {

      }

      ~App()
      {
        // delete currentState;
        receive_thread.join();
        send_thread.join();
      }

      void init(FluffyMultiplayer::AnAddress _server, std::string _identity);
      void run();
      void close();
      void setIdentity(std::string);
      std::string getIdentity() const;
  };
}

#endif
