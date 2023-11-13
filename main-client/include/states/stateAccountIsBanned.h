#ifndef H_STATE_ACCOUNT_IS_BANNED
#define H_STATE_ACCOUNT_IS_BANNED

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateAccountIsBanned : public AppState
  {
  public:
    StateAccountIsBanned();
    ~StateAccountIsBanned();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
