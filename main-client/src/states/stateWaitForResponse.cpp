#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateWaitForResponse::StateWaitForResponse()
  {

  }

  StateWaitForResponse::~StateWaitForResponse()
  {

  }

  void StateWaitForResponse::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateWaitForResponse::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateWaitForResponse::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
