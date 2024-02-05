#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateConnectedToTheServer::StateConnectedToTheServer()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state connected");
  }

  StateConnectedToTheServer::~StateConnectedToTheServer()
  {

  }

  void StateConnectedToTheServer::render(sf::RenderWindow& window)
  {
    setSimpleTextPosition((window.getSize().x/2)-INITAL_TEXT_ON_SCREEN_PADDING_X,
                          (window.getSize().y/2)-INITAL_TEXT_ON_SCREEN_PADDING_Y);
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateConnectedToTheServer::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return new FluffyMultiplayer::StateRelogin;
  }


  FluffyMultiplayer::AppState* StateConnectedToTheServer::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
