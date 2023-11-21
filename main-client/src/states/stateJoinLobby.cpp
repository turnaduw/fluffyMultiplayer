#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateJoinLobby::StateJoinLobby()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state joinLobby");
  }

  StateJoinLobby::~StateJoinLobby()
  {

  }

  void StateJoinLobby::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateJoinLobby::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateJoinLobby::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
