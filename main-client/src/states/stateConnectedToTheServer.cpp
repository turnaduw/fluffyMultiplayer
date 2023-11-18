#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateConnectedToTheServer::StateConnectedToTheServer()
  {

  }

  StateConnectedToTheServer::~StateConnectedToTheServer()
  {

  }

  void StateConnectedToTheServer::render(sf::RenderWindow& window)
  {

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
