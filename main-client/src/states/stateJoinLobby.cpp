#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateJoinLobby::StateJoinLobby(FluffyMultiplayer::AnAddress target_address)
  {
    gameServerAddress = target_address;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state joinLobby\n game has been launched.");
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
    app.openGame(gameServerAddress);
    return this;
  }


  FluffyMultiplayer::AppState* StateJoinLobby::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
