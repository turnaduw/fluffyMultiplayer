#include "../../include/states.h"

namespace FluffyMultiplayer
{
  void StateRegisterForm::initForm()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "REGISTER FORM");
    setSimpleTextPosition(150.0, 5.0);
    emailInput.init("","","email:","enter email..", 100.0, 100.0);
    usernameInput.init("","","username:","enter username..", 100.0, 200.0);
    passwordInput.init("","","password:","enter password..", 100.0, 300.0);
    buttonGoToLoginForm.init("Sign In", 100.0,400.0, sf::Color::Black,sf::Color::White, 60,30, 22);
    buttonSubmit.init("submit", 300.0,400.0, sf::Color::Black,sf::Color::Green, 60,30, 22);
    inputFocus = &emailInput;
  }

  FluffyMultiplayer::AppState* StateRegisterForm::formFinishedResult(bool isSubmit)
  {
    if(isSubmit)
    {
      form_data._inputs[0] = usernameInput.getEnteredText();
      form_data._inputs[1] = passwordInput.getEnteredText();
      form_data._inputs[2] = emailInput.getEnteredText();
      //go register..
      return new FluffyMultiplayer::StateWaitForResponse //will break loop
      (
        "waiting for response from server\nto register an account.\nplease wait..",
        this,
        form_data,
        new FluffyMultiplayer::StateWriteIdentityToLocal,
        MS_RESPONSE_SUCCESS_REGISTER
      );
    }

    //else
    return new FluffyMultiplayer::StateLoginForm;
  }
  StateRegisterForm::StateRegisterForm()
  {
    initForm();
  }

  StateRegisterForm::StateRegisterForm(FluffyMultiplayer::RegisterFormData data)
  {
    form_data=data;
    initForm();
    emailInput.setText(form_data._inputs[0]);
    emailInput.setError(form_data._errors[0]);
    usernameInput.setText(form_data._inputs[1]);
    usernameInput.setError(form_data._errors[1]);
    passwordInput.setText(form_data._inputs[2]);
    passwordInput.setError(form_data._errors[2]);
  }

  StateRegisterForm::~StateRegisterForm()
  {

  }

  void StateRegisterForm::render(sf::RenderWindow& window)
  {
    window.draw(theText);
    emailInput.render(window);
    usernameInput.render(window);
    passwordInput.render(window);
    buttonSubmit.render(window);
    buttonGoToLoginForm.render(window);
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
    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        if(buttonSubmit.getButtonBound().contains(mousePosition))
        {
          std::cout<<"mouse is clicked on button submit"<< std::endl;
          if(!usernameInput.getEnteredText().empty()
              && !passwordInput.getEnteredText().empty()
              && !emailInput.getEnteredText().empty())
          {
            return formFinishedResult(true);
          }
        }
        else if(buttonGoToLoginForm.getButtonBound().contains(mousePosition))
        {
          std::cout << "mouse is clicked on buttn go to login form" << std::endl;
          return formFinishedResult(false);
        }
        else if(emailInput.getInputBoxBound().contains(mousePosition))
        {
          std::cout << "mouse is clicked on email input" << std::endl;
          inputFocus = &emailInput;
        }
        else if(usernameInput.getInputBoxBound().contains(mousePosition))
        {
          std::cout << "mouse is clicked on username input" << std::endl;
          inputFocus = &usernameInput;
        }
        else if(passwordInput.getInputBoxBound().contains(mousePosition))
        {
          std::cout << "mouse is clicked on password input" << std::endl;
          inputFocus = &passwordInput;
        }
        else
          std::cout << "mouse clicked on nowhere. posx:"  << mousePosition.x
                  <<  "\tposy:" << mousePosition.y << std::endl;
    }


    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
      {
        if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
        {
          if(!usernameInput.getEnteredText().empty()
              && !passwordInput.getEnteredText().empty()
              && !emailInput.getEnteredText().empty())
                  return formFinishedResult(true);
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
          if(inputFocus != nullptr)
            inputFocus->update(static_cast<char>(event.text.unicode));
        }
      }break;
    }
    return this;
  }
}
