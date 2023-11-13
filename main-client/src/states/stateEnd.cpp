#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateEnd::StateEnd()
  {

  }

  StateEnd::~StateEnd()
  {

  }

  void StateEnd::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateEnd::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateEnd::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
