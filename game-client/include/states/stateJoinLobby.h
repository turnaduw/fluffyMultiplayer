#ifndef H_STATE_JOIN_LOBBY
#define H_STATE_JOIN_LOBBY

#include "../appState.h"
#include "../uiComponents/textInput.h"
#include "../uiComponents/button.h"
#include "../uiComponents/checkBox.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateJoinLobby : public AppState
  {
  private:
    std::string entered_password;

    //focus
    FluffyMultiplayer::TextInput* inputFocus;

    //text inputs
    FluffyMultiplayer::TextInput passwordInput;

    FluffyMultiplayer::AppState* formFinishedResult(FluffyMultiplayer::App& app);

    //buttons
    FluffyMultiplayer::Button buttonSubmit;
    FluffyMultiplayer::Button buttonCancel;

    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;

    void init();
  public:
    StateJoinLobby();
    ~StateJoinLobby();

    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
