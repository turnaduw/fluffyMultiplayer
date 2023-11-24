#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateLogout::StateLogout()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state logout\nare you sure to logout?\npress enter to confirm others to cancel.");
  }

  StateLogout::~StateLogout()
  {

  }

  void StateLogout::render(sf::RenderWindow& window)
  {
    window.draw(theText);
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
