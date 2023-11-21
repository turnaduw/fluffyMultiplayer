#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateLogout::StateLogout()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state logout");
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
    return this;
  }
}
