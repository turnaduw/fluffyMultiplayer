#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateEnd::StateEnd()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Are you sure to quit?");
    setSimpleTextPosition(395.0, 300.0);
    buttonConfirm.init("Quit",340.0,370.0, sf::Color::White, sf::Color::White, 60,30, 22);
    buttonCancel.init("Back",540.0,370.0, sf::Color::White, sf::Color::White, 60,30, 22);
  }

  StateEnd::~StateEnd()
  {

  }

  void StateEnd::render(sf::RenderWindow& window)
  {
    window.draw(theText);
    buttonConfirm.render(window);
    buttonCancel.render(window);
  }


  FluffyMultiplayer::AppState* StateEnd::update(FluffyMultiplayer::App& app)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateEnd::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        if(buttonConfirm.getButtonBound().contains(mousePosition))
        {
          app.close();
        }
        else if(buttonCancel.getButtonBound().contains(mousePosition))
        {
          return new FluffyMultiplayer::StateMainPage(app);
        }
    }
    return this;
  }
}
