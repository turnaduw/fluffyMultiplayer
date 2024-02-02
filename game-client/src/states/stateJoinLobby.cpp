#include "../../include/states.h"

namespace FluffyMultiplayer
{
  void StateJoinLobby::init()
  {
    inputFocus = &passwordInput;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "LOBBY PASSWORD");
    setSimpleTextPosition(150.0, 5.0);
    passwordInput.init("","","password:","enter password..", 100.0, 200.0);
    buttonCancel.init("cancel", 100.0,400.0, sf::Color::Black,sf::Color::White, 60,30, 22);
    buttonSubmit.init("join", 300.0,400.0, sf::Color::Black,sf::Color::Green, 60,30, 22);
  }

  StateJoinLobby::StateJoinLobby()
  {
    init();
  }

  StateJoinLobby::~StateJoinLobby()
  {

  }

  void StateJoinLobby::render(sf::RenderWindow& window)
  {
    window.draw(theText);
    passwordInput.render(window);
    buttonSubmit.render(window);
    buttonCancel.render(window);
  }


  FluffyMultiplayer::AppState* StateJoinLobby::update(FluffyMultiplayer::App& app)
  {
      return this;
  }

  FluffyMultiplayer::AppState* StateJoinLobby::formFinishedResult(FluffyMultiplayer::App& app)
  {
    entered_password = passwordInput.getEnteredText();
    std::string _data = app.getIdentity() + std::string(MS_DATA_DELIMITER) + entered_password;
    app.addSendText(REQUEST_JOIN_TO_LOBBY,_data);


    return new FluffyMultiplayer::StateWaitForResponse
    (
      "waiting for response from server\nto join into lobby.\nplease wait..",
      this,
      std::vector<FluffyMultiplayer::AppState*>
          {
            new FluffyMultiplayer::StateMainPage(app),
            new FluffyMultiplayer::StateFailed("incorrect password.\n",this,nullptr),
            new FluffyMultiplayer::StateFailed("invalid identity.\n",this,nullptr)
          },
      std::vector<int>
        {
          RESPONSE_YOU_ARE_JOINT_INTO_LOBBY, //success
          RESPONSE_ERROR_JOIN_LOBBY_PASSWORD_INCORRECT,
          RESPONSE_ERROR_JOIN_LOBBY_INVALID_IDENTITY
        }
    );

  }

  FluffyMultiplayer::AppState* StateJoinLobby::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {

    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        if(buttonSubmit.getButtonBound().contains(mousePosition))
        {
          if(!passwordInput.getEnteredText().empty())
          {
            return formFinishedResult(app);
          }
        }
        else if(buttonCancel.getButtonBound().contains(mousePosition))
        {
          return formFinishedResult(app);
        }
        else if(passwordInput.getInputBoxBound().contains(mousePosition))
        {
          inputFocus = &passwordInput;
        }
    }


    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
      {
        if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
        {
          if(!passwordInput.getEnteredText().empty())
          {
            return formFinishedResult(app);
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
