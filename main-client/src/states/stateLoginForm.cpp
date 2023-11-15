#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateLoginForm::StateLoginForm()
  {

  }

  StateLoginForm::StateLoginForm( std::array<std::string, 2>inputs, std::array<std::string, 2>errors, bool rememberlogin )
  {

  }

  StateLoginForm::~StateLoginForm()
  {

  }

  void StateLoginForm::render(sf::RenderWindow& window)
  {
    sf::Sprite bgsp;
    sf::Texture bgtexture;
    bgtexture.loadFromFile("./assets/states/bgLoginForm.png");
    bgsp.setTexture(bgtexture);

    window.draw(bgsp);
  }


  FluffyMultiplayer::AppState* StateLoginForm::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {

      return this;
  }


  FluffyMultiplayer::AppState* StateLoginForm::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event&)
  {
    //..
    return this;
  }

}
