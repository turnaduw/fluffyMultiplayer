#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailedRegister::StateFailedRegister()
  {

  }

  StateFailedRegister::~StateFailedRegister()
  {

  }

  void StateFailedRegister::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateFailedRegister::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateFailedRegister::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
