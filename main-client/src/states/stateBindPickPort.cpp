#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateBindPickPort::StateBindPickPort()
  {

  }

  StateBindPickPort::~StateBindPickPort()
  {

  }

  void StateBindPickPort::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateBindPickPort::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateBindPickPort::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
