#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateWriteIdentityToLocal::StateWriteIdentityToLocal()
  {

  }

  StateWriteIdentityToLocal::~StateWriteIdentityToLocal()
  {

  }

  void StateWriteIdentityToLocal::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateWriteIdentityToLocal::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateWriteIdentityToLocal::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
