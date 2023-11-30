#ifndef H_STATE_LOGIN_FORM
#define H_STATE_LOGIN_FORM

#include "../appState.h"
#include "../uiComponents/textInput.h"
#include "../uiComponents/button.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateLoginForm : public AppState
  {
  private:
    FluffyMultiplayer::LoginFormData form_data;

    //focus
    FluffyMultiplayer::TextInput* inputFocus;
    FluffyMultiplayer::Button* buttonFocus;

    //text inputs
    FluffyMultiplayer::TextInput usernameInput;
    FluffyMultiplayer::TextInput passwordInput;

    //buttons
    FluffyMultiplayer::Button buttonSubmit;
    FluffyMultiplayer::Button buttonGoToRegisterForm;


    void init();
  public:
    StateLoginForm();
    StateLoginForm(FluffyMultiplayer::LoginFormData); //if form failed re-fills form automatically
    ~StateLoginForm();

    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
