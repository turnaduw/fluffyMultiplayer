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

#include "appState.h"

namespace FluffyMultiplayer
{
  class AppState;
  class App
  {
    private:
      std::string identity;
      bool sendDataStatus;
      bool receiveDataStatus;
      unsigned short appPort;
      FluffyMultiplayer::AnAddress serverAddress;
      FluffyMultiplayer::AppState* currentState;
      std::queue<FluffyMultiplayer::AnAddress> serverList;
      std::queue<FluffyMultiplayer::LobbyData>* lobbyList;
      std::queue<std::string> receivedDataQueue;
      std::queue<std::string> sendDataQueue;

      //network and data froms
      boost::asio::io_context io_context;
      FluffyMultiplayer::UdpSocket socket;

      void sendData();
      void receiveData();

    public:
      boost::thread receive_thread;
      boost::thread send_thread;

      sf::RenderWindow appWindow;
      App(): appWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
        , socket(io_context,MC_DEFAULT_PORT)
      {
        //to avoid socket erros due to socket.bind(port) is not completely set.
        //need to set port then active these parts
        setSendDataStatus(false);
        setReceiveDataStatus(false);

        receive_thread = boost::thread(&FluffyMultiplayer::App::receiveData, this);
        send_thread = boost::thread(&FluffyMultiplayer::App::sendData, this);

        appPort=MC_DEFAULT_PORT; //default port
        currentState=nullptr;
        lobbyList=nullptr;
      }

      ~App()
      {
        // delete currentState;
        // delete lobbyList;

        receive_thread.join();
        send_thread.join();
      }

      void init();
      void run();
      void clearIdentity();
      void setIdentity(std::string);
      std::string getIdentity() const;
      FluffyMultiplayer::AnAddress getServerAddress() const;
      void setServer(FluffyMultiplayer::AnAddress);
      void addServer(FluffyMultiplayer::AnAddress);
      FluffyMultiplayer::AnAddress popServerAddress();
      int getServerListCount() const;
      void setAppPort(unsigned short);
      unsigned short getAppPort() const;
      bool getReceiveDataStatus() const;
      bool getSendDataStatus() const;
      void setReceiveDataStatus(bool);
      void setSendDataStatus(bool);
      void openGame(FluffyMultiplayer::AnAddress);
  };
}

#endif
