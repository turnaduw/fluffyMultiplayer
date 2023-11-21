#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateMainPage::StateMainPage(std::string identity)
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state mainPage");
  }

  StateMainPage::~StateMainPage()
  {

  }

  void StateMainPage::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateMainPage::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateMainPage::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
