#ifndef H_STATE_CONNECTING_TO_SERVER
#define H_STATE_CONNECTING_TO_SERVER

#include "../appState.h"

#include <ctime>

#include <boost/asio.hpp>
using boost::asio::ip::udp;


namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateConnectingToServer : public AppState
  {
  private:
    std::string req;
  public:
    StateConnectingToServer();
    ~StateConnectingToServer();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
