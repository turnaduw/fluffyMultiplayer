#include "../../include/states.h"

namespace FluffyMultiplayer
{
  void StateLoginForm::init()
  {
    inputFocus = &usernameInput;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "LOGIN FORM");
    setSimpleTextPosition(150.0, 5.0);
    usernameInput.init("","","username:","enter username..", 100.0, 100.0);
    passwordInput.init("","","password:","enter password..", 100.0, 200.0);
    saveLoginCheckBox.init("save login", 100.0, 300.0, sf::Color::Black, sf::Color::White, 22);
    buttonGoToRegisterForm.init("Sign up", 100.0,400.0, sf::Color::Black,sf::Color::White, 60,30, 22);
    buttonSubmit.init("submit", 300.0,400.0, sf::Color::Black,sf::Color::Green, 60,30, 22);
  }

  FluffyMultiplayer::AppState* StateLoginForm::formFinishedResult(bool isSubmit)
  {
    if(isSubmit)
    {
      form_data._inputs[0] = usernameInput.getEnteredText();
      form_data._inputs[1] = passwordInput.getEnteredText();
      form_data._saveLoginStatus = saveLoginCheckBox.getStatus();

      FluffyMultiplayer::AppState* res = nullptr;
      if(form_data._saveLoginStatus)
        res = new FluffyMultiplayer::StateWriteIdentityToLocal;
      else
         res = new FluffyMultiplayer::StateMainPage;

      //go login..
      return new FluffyMultiplayer::StateWaitForResponse
      (
        "waiting for response from server\nto login into account.\nplease wait..",
        this,
        form_data,
        std::vector<FluffyMultiplayer::AppState*> {new FluffyMultiplayer::StateFailed("account is banned.\n",this,nullptr)},
        res,
        std::vector<int> {MS_ERROR_FAILED_TO_LOGIN_BANNED},
        MS_RESPONSE_SUCCESS_LOGIN
      );
    }


    //else
    return new FluffyMultiplayer::StateRegisterForm;
  }

  StateLoginForm::StateLoginForm()
  {
    init();
  }

  StateLoginForm::StateLoginForm(FluffyMultiplayer::LoginFormData _data)
  {
    init();
    form_data = _data;
    
    //apply passed data into form element
    usernameInput.setText(form_data._inputs[0]);
    usernameInput.setError(form_data._errors[0]);
    passwordInput.setText(form_data._inputs[1]);
    passwordInput.setError(form_data._errors[1]);
    saveLoginCheckBox.setStatus(form_data._saveLoginStatus);
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
    saveLoginCheckBox.render(window);
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

    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        if(buttonSubmit.getButtonBound().contains(mousePosition))
        {
          std::cout<<"mouse is clicked on button submit"<< std::endl;
          if(!usernameInput.getEnteredText().empty()
              && !passwordInput.getEnteredText().empty())
          {
            return formFinishedResult(true);
          }
        }
        else if(saveLoginCheckBox.getBound().contains(mousePosition))
        {
          std::cout << "mouse is lciked on checkbox" << std::endl;
          saveLoginCheckBox.clickedOnCheckBox();
        }
        else if(buttonGoToRegisterForm.getButtonBound().contains(mousePosition))
        {
          std::cout << "mouse is clicked on buttn go to register form" << std::endl;
          return formFinishedResult(false);
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
                  && !passwordInput.getEnteredText().empty())
          {
            return formFinishedResult(true);
          }
          else
            std::cout << "one or more of the inputs are empty, can not submit\n";
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
