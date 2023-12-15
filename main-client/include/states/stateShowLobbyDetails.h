#ifndef H_STATE_SHOW_LOBBY_DETAILS
#define H_STATE_SHOW_LOBBY_DETAILS

#include "../appState.h"
#include "../uiComponents/button.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateShowLobbyDetails : public AppState
  {
  private:
    FluffyMultiplayer::LobbyData lobby;

    FluffyMultiplayer::Button buttonConfirm;
    FluffyMultiplayer::Button buttonCancel;
    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;

    
    std::string lobbyAsText;
    std::string dataSeparator(std::string&, std::string);
    std::vector<int> dataIndexes(const std::string&, const std::string&) const;

    std::string boolToString(bool);
  public:
    StateShowLobbyDetails(FluffyMultiplayer::LobbyData);
    StateShowLobbyDetails(std::string);
    ~StateShowLobbyDetails();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
