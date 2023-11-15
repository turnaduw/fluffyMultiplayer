#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateRegisterForm::StateRegisterForm()
  {

  }

  StateRegisterForm::~StateRegisterForm()
  {

  }

  void StateRegisterForm::render(sf::RenderWindow& window)
  {

  }


  FluffyMultiplayer::AppState* StateRegisterForm::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateRegisterForm::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
