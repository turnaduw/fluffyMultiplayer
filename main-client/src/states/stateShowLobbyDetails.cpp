#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateShowLobbyDetials::StateShowLobbyDetials()
  {

  }

  StateShowLobbyDetials::~StateShowLobbyDetials()
  {

  }

  void StateShowLobbyDetials::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateShowLobbyDetials::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateShowLobbyDetials::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
