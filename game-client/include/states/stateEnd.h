#ifndef H_STATE_END
#define H_STATE_END

#include "../appState.h"
#include "../uiComponents/button.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateEnd : public AppState
  {
  private:
    FluffyMultiplayer::Button buttonConfirm;
    FluffyMultiplayer::Button buttonCancel;

    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;

  public:
    StateEnd();
    ~StateEnd();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
