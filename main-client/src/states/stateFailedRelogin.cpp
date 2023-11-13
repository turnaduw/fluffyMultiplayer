#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailedRelogin::StateFailedRelogin()
  {

  }

  StateFailedRelogin::~StateFailedRelogin()
  {

  }

  void StateFailedRelogin::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateFailedRelogin::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateFailedRelogin::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
