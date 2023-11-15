#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateLogout::StateLogout()
  {

  }

  StateLogout::~StateLogout()
  {

  }

  void StateLogout::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateLogout::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateLogout::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
