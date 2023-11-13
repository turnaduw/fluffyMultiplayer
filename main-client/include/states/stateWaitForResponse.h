#ifndef H_STATE_WAIT_FOR_RESPONSE
#define H_STATE_WAIT_FOR_RESPONSE

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateWaitForResponse : public AppState
  {
  public:
    StateWaitForResponse();
    ~StateWaitForResponse();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
