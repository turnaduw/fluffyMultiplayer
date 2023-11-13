#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateAccountIsBanned::StateAccountIsBanned()
  {

  }

  StateAccountIsBanned::~StateAccountIsBanned()
  {

  }

  void StateAccountIsBanned::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateAccountIsBanned::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateAccountIsBanned::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
