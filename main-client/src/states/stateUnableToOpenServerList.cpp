#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateUnableToReadServerList::StateUnableToReadServerList()
  {

  }

  StateUnableToReadServerList::~StateUnableToReadServerList()
  {

  }

  void StateUnableToReadServerList::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateUnableToReadServerList::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateUnableToReadServerList::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
