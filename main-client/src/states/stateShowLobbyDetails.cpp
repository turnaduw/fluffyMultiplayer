#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateShowLobbyDetials::StateShowLobbyDetials(FluffyMultiplayer::LobbyData selectedLobby)
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state StateShowLobbyDetials");
  }

  StateShowLobbyDetials::~StateShowLobbyDetials()
  {

  }

  void StateShowLobbyDetials::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateShowLobbyDetials::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateShowLobbyDetials::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
