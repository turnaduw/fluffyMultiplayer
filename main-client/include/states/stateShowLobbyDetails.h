#ifndef H_STATE_SHOW_LOBBY_DETAILS
#define H_STATE_SHOW_LOBBY_DETAILS

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateShowLobbyDetials : public AppState
  {
  public:
    StateShowLobbyDetials();
    ~StateShowLobbyDetials();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
