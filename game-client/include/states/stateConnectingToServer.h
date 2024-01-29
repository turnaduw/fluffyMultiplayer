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
    bool request_sent;
  public:
    StateConnectingToServer();
    ~StateConnectingToServer();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
