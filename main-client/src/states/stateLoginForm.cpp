#include "../../include/states.h"

namespace FluffyMultiplayer
{
  void StateLoginForm::initFormLabels()
  {
    label_text[0] = "username:";
    label_text[1] = ""; //username error
    label_text[2] = "password:";
    label_text[3] = ""; //password error
    label_text[4] = "save login";
  }

  StateLoginForm::StateLoginForm()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "LOGIN FORM");
  }

  StateLoginForm::StateLoginForm(FluffyMultiplayer::LoginFormData _data)
  {
    form_data = _data;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "LOGIN FORM");
  }

  StateLoginForm::~StateLoginForm()
  {

  }

  void StateLoginForm::render(sf::RenderWindow& window)
  {
    window.draw(theText);
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
      }
      break;
    }
    return this;
  }

}
