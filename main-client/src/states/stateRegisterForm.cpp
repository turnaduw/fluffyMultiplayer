#include "../../include/states.h"

namespace FluffyMultiplayer
{
  void StateRegisterForm::initForm()
  {
    label_text[0] = "username:";
    label_text[1] = ""; //username error
    label_text[2] = "email:";
    label_text[3] = ""; //email error
    label_text[4] = "password";
    label_text[5] = ""; //password error

    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "REGISTER FORM");
  }

  StateRegisterForm::StateRegisterForm()
  {
    initForm();
  }

  StateRegisterForm::StateRegisterForm(FluffyMultiplayer::RegisterFormData data)
  {
    form_data=data;
    initForm();
  }

  StateRegisterForm::~StateRegisterForm()
  {

  }

  void StateRegisterForm::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateRegisterForm::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateRegisterForm::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
      {
        if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
        {
          //go register..
          return new FluffyMultiplayer::StateWaitForResponse //will break loop
          (
            "waiting for response from server\nto register an account.\nplease wait..",
            this,
            form_data,
            new FluffyMultiplayer::StateWriteIdentityToLocal(form_data.identity),
            MS_RESPONSE_SUCCESS_REGISTER
          );
        }
        if(event.key.code == sf::Keyboard::Space)
        {
          return new FluffyMultiplayer::StateLoginForm;
        }
      }
      break;
    }
    return this;
  }
}
