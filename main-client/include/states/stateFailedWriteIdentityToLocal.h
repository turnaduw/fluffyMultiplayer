#ifndef H_STATE_FAILED_WRITE_IDENTITY_TO_LOCAL
#define H_STATE_FAILED_WRITE_IDENTITY_TO_LOCAL

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateFailedWriteIdentityToLocal : public AppState
  {
  public:
    StateFailedWriteIdentityToLocal();
    ~StateFailedWriteIdentityToLocal();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
