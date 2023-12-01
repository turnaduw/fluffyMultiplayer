#ifndef H_STATE_CREATE_LOBBY_FORM
#define H_STATE_CREATE_LOBBY_FORM

#include "../appState.h"
#include "../uiComponents/textInput.h"
#include "../uiComponents/button.h"
#include "../uiComponents/checkBox.h"
#include "../uiComponents/spinBox.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateCreateLobbyForm : public AppState
  {
  private:
    FluffyMultiplayer::CreateLobbyFormData lobbyData;

    //focus
    FluffyMultiplayer::TextInput* inputFocus;

    //text inputs
    FluffyMultiplayer::TextInput passwordInput;

    //spinboxes
    FluffyMultiplayer::SpinBox gameModeSpinBox;
    FluffyMultiplayer::SpinBox maxPlayersSpinBox;


    //check boxes
    FluffyMultiplayer::CheckBox specterCheckBox;
    FluffyMultiplayer::CheckBox voiceChatCheckBox;
    FluffyMultiplayer::CheckBox textChatCheckBox;

    //buttons
    FluffyMultiplayer::Button buttonSubmit;
    FluffyMultiplayer::Button buttonCancel;

    //to avoid duplicate return code while calling them from event mouse, keyboard
    FluffyMultiplayer::AppState* formFinishedResult(bool isSubmit);


    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;
    std::array<sf::FloatRect,2> gameModeSpinBoxBounds;
    std::array<sf::FloatRect,2> maxPlayersSpinBoxBounds;

    void init();

  public:
    StateCreateLobbyForm();
    StateCreateLobbyForm(FluffyMultiplayer::CreateLobbyFormData);
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
