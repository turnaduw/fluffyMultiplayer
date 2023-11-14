#ifndef H_STATE_CREATE_LOBBY_FORM
#define H_STATE_CREATE_LOBBY_FORM

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateCreateLobbyForm : public AppState
  {
  public:
    StateCreateLobbyForm();
    ~StateCreateLobbyForm();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
