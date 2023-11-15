#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateConnectedToTheServer::StateConnectedToTheServer()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "connected to the server.");
  }

  StateConnectedToTheServer::~StateConnectedToTheServer()
  {

  }

  void StateConnectedToTheServer::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateConnectedToTheServer::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateConnectedToTheServer::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
