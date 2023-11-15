#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateJoinLobby::StateJoinLobby()
  {

  }

  StateJoinLobby::~StateJoinLobby()
  {

  }

  void StateJoinLobby::render(sf::RenderWindow& window)
  {

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
