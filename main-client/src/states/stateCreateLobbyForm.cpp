#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateCreateLobbyForm::StateCreateLobbyForm()
  {

  }

  StateCreateLobbyForm::~StateCreateLobbyForm()
  {

  }

  void StateCreateLobbyForm::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateCreateLobbyForm::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateCreateLobbyForm::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
