#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailedToBindPickPort::StateFailedToBindPickPort()
  {

  }

  StateFailedToBindPickPort::~StateFailedToBindPickPort()
  {

  }

  void StateFailedToBindPickPort::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateFailedToBindPickPort::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateFailedToBindPickPort::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
