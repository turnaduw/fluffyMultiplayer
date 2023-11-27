#include "../../include/states.h"

namespace FluffyMultiplayer
{

  StateLoginForm::StateLoginForm()
  {
    inputFocus = &usernameInput;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "LOGIN FORM");
    usernameInput.init("","","username:","enter username..");
  }

  StateLoginForm::StateLoginForm(FluffyMultiplayer::LoginFormData _data)
  {
    inputFocus = &usernameInput;
    form_data = _data;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "LOGIN FORM");
    usernameInput.init(form_data._inputs[0],form_data._errors[0],"username:","enter username..");
  }

  StateLoginForm::~StateLoginForm()
  {

  }

  void StateLoginForm::render(sf::RenderWindow& window)
  {
    window.draw(theText);
    if(inputFocus!=nullptr)
      inputFocus->render(window);
  }


  FluffyMultiplayer::AppState* StateLoginForm::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
      return this;
  }


  FluffyMultiplayer::AppState* StateLoginForm::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
      {
        if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
        {
          if(inputFocus!=nullptr)
          {
            form_data._inputs[0] = inputFocus->getEnteredText();
          }
          //go login..
          return new FluffyMultiplayer::StateWaitForResponse //will break loop
          (
            "waiting for response from server\nto login into account.\nplease wait..",
            this,
            form_data,
            new FluffyMultiplayer::StateFailed("account is banned.\n",this,nullptr),
            new FluffyMultiplayer::StateWriteIdentityToLocal,
            MS_ERROR_FAILED_TO_LOGIN_BANNED,
            MS_RESPONSE_SUCCESS_LOGIN
          );
        }
        if(event.key.code == sf::Keyboard::Space)
        {
          return new FluffyMultiplayer::StateRegisterForm;
        }
        if(event.key.code == sf::Keyboard::Backspace)
        {
          if(inputFocus!=nullptr)
            inputFocus->removeFromText();
        }
      }break;

      case sf::Event::TextEntered:
      {
        if (event.text.unicode < 128)
        {
          if(inputFocus!=nullptr)
            inputFocus->update(static_cast<char>(event.text.unicode));
        }
      }break;

    }
    return this;
  }

}
