#ifndef H_STATE_FAILED_CONNECT_TO_ALL_SERVERS
#define H_STATE_FAILED_CONNECT_TO_ALL_SERVERS

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateFailedConnectToAllServers : public AppState
  {
  public:
    StateFailedConnectToAllServers();
    ~StateFailedConnectToAllServers();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
