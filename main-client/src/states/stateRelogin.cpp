#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateRelogin::StateRelogin()
  {

  }

  StateRelogin::~StateRelogin()
  {

  }

  void StateRelogin::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateRelogin::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateRelogin::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
