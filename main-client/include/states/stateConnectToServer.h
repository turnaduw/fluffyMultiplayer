#ifndef H_STATE_CONNECT_TO_SERVER
#define H_STATE_CONNECT_TO_SERVER

#include "../appState.h"

#include <ctime>

#include <boost/asio.hpp>
using boost::asio::ip::udp;


namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateConnectToServer : public AppState
  {
  private:
    int findIndexOfChar(const std::string&, const char&);
  public:
    StateConnectToServer();
    ~StateConnectToServer();
    int generateRandomNumber(int,int);
    bool isPortBusy(int);
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
