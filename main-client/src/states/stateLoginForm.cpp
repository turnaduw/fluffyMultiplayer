#include "../../include/states.h"

namespace FluffyMultiplayer
{
  void StateLoginForm::init()
  {
    inputFocus = &usernameInput;
    buttonFocus = nullptr;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "LOGIN FORM");
    setSimpleTextPosition(150.0, 5.0);
    buttonGoToRegisterForm.init("register\naccount", 100.0,300.0, sf::Color::Black,sf::Color::White, 60,30, 22);
    buttonSubmit.init("submit", 300.0,300.0, sf::Color::Black,sf::Color::Green, 60,30, 22);
  }

  StateLoginForm::StateLoginForm()
  {
    init();
    usernameInput.init("","","username:","enter username..", 100.0, 100.0);
    passwordInput.init("","","password:","enter password..", 100.0, 200.0);
  }

  StateLoginForm::StateLoginForm(FluffyMultiplayer::LoginFormData _data)
  {
    init();
    form_data = _data;
    usernameInput.init(form_data._inputs[0],form_data._errors[0],"username:","enter username..", 100.0, 100.0);
    passwordInput.init(form_data._inputs[1],form_data._errors[1],"password:","enter password..", 100.0, 200.0);
  }

  StateLoginForm::~StateLoginForm()
  {

  }

  void StateLoginForm::render(sf::RenderWindow& window)
  {
    window.draw(theText);
    usernameInput.render(window);
    passwordInput.render(window);
    buttonSubmit.render(window);
    buttonGoToRegisterForm.render(window);
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
          if(inputFocus==nullptr && buttonFocus == &buttonSubmit
                  && !usernameInput.getEnteredText().empty()
                  && !passwordInput.getEnteredText().empty())
          {
            form_data._inputs[0] = usernameInput.getEnteredText();
            form_data._inputs[1] = passwordInput.getEnteredText();
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
          else if(inputFocus==nullptr && buttonFocus == &buttonGoToRegisterForm)
          {
            return new FluffyMultiplayer::StateRegisterForm;
          }
          else
            std::cout << "button no focused\n";
        }
        if(event.key.code == sf::Keyboard::Backspace)
        {
          if(inputFocus!=nullptr)
            inputFocus->removeFromText();
        }
        if(event.key.code == sf::Keyboard::Tab)
        {
          if((usernameInput.getEnteredText()).empty())
          {
            buttonFocus=nullptr;
            inputFocus = &usernameInput;
          }
          else if((passwordInput.getEnteredText()).empty())
          {
            buttonFocus=nullptr;
            inputFocus = &passwordInput;
          }
          else if(buttonFocus == nullptr)
          {
            inputFocus=nullptr;
            buttonFocus=&buttonGoToRegisterForm;
          }
          else if(buttonFocus == &buttonGoToRegisterForm)
          {
            inputFocus=nullptr;
            buttonFocus = &buttonSubmit;
          }
          else if(buttonFocus == &buttonSubmit)
          {
            inputFocus=nullptr;
            buttonFocus = &buttonGoToRegisterForm;
          }
          else
            std::cout << "form nowhere to focus\n";
        }
      }break;

      case sf::Event::TextEntered:
      {
        if (event.text.unicode < 128)
        {
          if(inputFocus != nullptr)
            inputFocus->update(static_cast<char>(event.text.unicode));
        }
      }break;

    }
    return this;
  }

}
