#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailedLogin::StateFailedLogin()
  {

  }

  StateFailedLogin::~StateFailedLogin()
  {

  }

  void StateFailedLogin::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateFailedLogin::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateFailedLogin::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
