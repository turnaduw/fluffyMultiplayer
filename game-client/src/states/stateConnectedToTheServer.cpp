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
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateConnectedToTheServer::update(FluffyMultiplayer::App& app)

  {
    return new FluffyMultiplayer::StateJoinLobby;
  }


  FluffyMultiplayer::AppState* StateConnectedToTheServer::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
