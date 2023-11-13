#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailedWriteIdentityToLocal::StateFailedWriteIdentityToLocal()
  {

  }

  StateFailedWriteIdentityToLocal::~StateFailedWriteIdentityToLocal()
  {

  }

  void StateFailedWriteIdentityToLocal::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateFailedWriteIdentityToLocal::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateFailedWriteIdentityToLocal::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
