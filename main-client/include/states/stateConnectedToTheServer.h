#ifndef H_STATE_CONNECTED_TO_THE_SERVER
#define H_STATE_CONNECTED_TO_THE_SERVER

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateConnectedToTheServer : public AppState
  {
  public:
    StateConnectedToTheServer();
    ~StateConnectedToTheServer();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
