#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateMessage::StateMessage()
  {

  }

  StateMessage::~StateMessage()
  {

  }

  void StateMessage::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateMessage::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateMessage::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
