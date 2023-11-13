#ifndef H_STATE_FAILED_RELOGIN
#define H_STATE_FAILED_RELOGIN

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateFailedRelogin : public AppState
  {
  public:
    StateFailedRelogin();
    ~StateFailedRelogin();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
