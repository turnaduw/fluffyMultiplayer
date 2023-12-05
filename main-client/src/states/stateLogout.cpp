#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateLogout::StateLogout()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state logout\nare you sure to logout?\npress enter to confirm others to cancel.");
    buttonConfirm.init("ok, Confirm", 200.0,200.0, sf::Color::Black,sf::Color::White, 60,30, 22);
    buttonCancel.init("Cancel", 400.0,200.0, sf::Color::Black,sf::Color::White, 60,30, 22);
  }

  StateLogout::~StateLogout()
  {

  }

  void StateLogout::render(sf::RenderWindow& window)
  {
    window.draw(theText);
    buttonConfirm.render(window);
    buttonCancel.render(window);
  }


  FluffyMultiplayer::AppState* StateLogout::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateLogout::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        if(buttonConfirm.getButtonBound().contains(mousePosition))
        {
          std::cout<<"mouse is clicked on button confirm logout"<< std::endl;
          app.clearIdentity();
          return new FluffyMultiplayer::StateLoginForm;
        }
        else if(buttonCancel.getButtonBound().contains(mousePosition))
        {
          std::cout<<"mouse is clicked on button cancel"<< std::endl;
          return new FluffyMultiplayer::StateMainPage;
        }
    }

    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
          {
            app.clearIdentity();
            return new FluffyMultiplayer::StateLoginForm;
          }
          else
          {
            return new FluffyMultiplayer::StateMainPage;
          }
        }
        break;
    }
    return this;
  }
}
