#ifndef H_STATE_JOIN_LOBBY
#define H_STATE_JOIN_LOBBY

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateJoinLobby : public AppState
  {
  private:
    FluffyMultiplayer::AnAddress gameServerAddress;
    FluffyMultiplayer::AnAddress convertStringToAddress(std::string);
    int findIndexOfDelimiter(const std::string& str, std::string c);
    int convertToInt(const std::string& str);

  public:
    StateJoinLobby(FluffyMultiplayer::AnAddress);
    StateJoinLobby(std::string);
    StateJoinLobby();
    ~StateJoinLobby();


    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
