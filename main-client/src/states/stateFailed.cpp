#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailed::StateFailed()
  {

  }

  StateFailed::~StateFailed()
  {

  }

  void StateFailed::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateFailed::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateFailed::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
