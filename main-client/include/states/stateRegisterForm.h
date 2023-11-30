#ifndef H_STATE_REGISTER_FORM
#define H_STATE_REGISTER_FORM

#include "../appState.h"
#include "../uiComponents/textInput.h"
#include "../uiComponents/button.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateRegisterForm : public AppState
  {
  private:
    FluffyMultiplayer::RegisterFormData form_data;
    void initForm();

    //focus input
    FluffyMultiplayer::TextInput* inputFocus;

    //text inputs
    FluffyMultiplayer::TextInput emailInput;
    FluffyMultiplayer::TextInput usernameInput;
    FluffyMultiplayer::TextInput passwordInput;


    //buttons
    FluffyMultiplayer::Button buttonSubmit;
    FluffyMultiplayer::Button buttonGoToLoginForm;

    //to avoid duplicate return code while calling them from event mouse, keyboard
    FluffyMultiplayer::AppState* formFinishedResult(bool isSubmit);

    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;

  public:
    StateRegisterForm();
    StateRegisterForm(FluffyMultiplayer::RegisterFormData);
    ~StateRegisterForm();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
