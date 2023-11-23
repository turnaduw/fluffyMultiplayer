#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateCreateLobbyForm::StateCreateLobbyForm()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state createLobbyForm");
  }

  StateCreateLobbyForm::~StateCreateLobbyForm()
  {

  }

  void StateCreateLobbyForm::render(sf::RenderWindow& window)
  {
    window.draw(theText);
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
