#ifndef H_APP_CLASS
#define H_APP_CLASS

#include <SFML/Graphics.hpp>
#include <queue>
#include <array>
#include "include/config.h"
#include "include/dataType.h"
using boost::asio::ip::udp;

#include "include/appState.h"



namespace FluffyMultiplayer
{
  class App
  {
    private:
      sf::RenderWindow appWindow;
      FluffyMultiplayer::AnAddress serverAddress;
      unsigned short appPort;
      FluffyMultiplayer::AppState* currentState;
      std::array<FluffyMultiplayer::AppState*, STATES_COUNT> states;
      std::queue<FluffyMultiplayer::AnAddress> serverList;
      bool sendDataStatus;
      bool receiveDataStatus;

    public:
      App(): appWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
      {

      }

      ~App();
      void init();
      void run(std::queue<std::string>&, std::queue<std::string>&);
      FluffyMultiplayer::AnAddress getServerAddress();
      void setServer(FluffyMultiplayer::AnAddress);
      void addServer(FluffyMultiplayer::AnAddress);
      sf::RenderWindow getWindow();
      unsigned short getAppPort();
      bool getReceiveDataStatus();
      bool getSendDataStatus();
      void setReceiveDataStatus(bool);
      void setSendDataStatus(bool);
  };
}

#endif
