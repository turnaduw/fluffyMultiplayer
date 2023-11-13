#ifndef H_STATE_FAILED_TO_BIND_PICK_PORT
#define H_STATE_FAILED_TO_BIND_PICK_PORT

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateFailedToBindPickPort : public AppState
  {
  public:
    StateFailedToBindPickPort();
    ~StateFailedToBindPickPort();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
