#ifndef H_APP_CLASS
#define H_APP_CLASS

#include <SFML/Graphics.hpp>
#include <queue>
#include <array>
#include "config.h"
#include "dataType.h"
using boost::asio::ip::udp;

#include "appState.h"

namespace FluffyMultiplayer
{
  class AppState;
  class App
  {
    private:
      FluffyMultiplayer::AnAddress serverAddress;
      unsigned short appPort;
      FluffyMultiplayer::AppState* currentState;
      std::queue<FluffyMultiplayer::AnAddress> serverList;
      bool sendDataStatus;
      bool receiveDataStatus;

    public:
      sf::RenderWindow appWindow;
      App(): appWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
      {
        appPort=MC_DEFAULT_PORT; //default port
        currentState=nullptr;
      }

      ~App();
      void init();
      void run(std::queue<std::string>&, std::queue<std::string>&);
      FluffyMultiplayer::AnAddress getServerAddress();
      void setServer(FluffyMultiplayer::AnAddress);
      void addServer(FluffyMultiplayer::AnAddress);
      int getServerListCount();
      void setAppPort(unsigned short);
      unsigned short getAppPort();
      bool getReceiveDataStatus();
      bool getSendDataStatus();
      void setReceiveDataStatus(bool);
      void setSendDataStatus(bool);
  };
}

#endif
