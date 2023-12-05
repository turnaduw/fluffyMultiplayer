#ifndef H_STATE_LOGOUT
#define H_STATE_LOGOUT

#include "../appState.h"
#include "../uiComponents/button.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateLogout : public AppState
  {
  private:
    FluffyMultiplayer::Button buttonConfirm;
    FluffyMultiplayer::Button buttonCancel;
    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;

  public:
    StateLogout();
    ~StateLogout();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
