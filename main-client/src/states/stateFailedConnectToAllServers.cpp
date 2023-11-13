#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailedConnectToAllServers::StateFailedConnectToAllServers()
  {

  }

  StateFailedConnectToAllServers::~StateFailedConnectToAllServers()
  {

  }

  void StateFailedConnectToAllServers::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateFailedConnectToAllServers::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateFailedConnectToAllServers::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
