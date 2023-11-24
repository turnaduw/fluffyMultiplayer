#ifndef H_STATE_MAIN_PAGE
#define H_STATE_MAIN_PAGE

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateMainPage : public AppState
  {
  private:
    std::string enteredLobbyId;
    std::vector<FluffyMultiplayer::LobbyData> lobbyList;
    FluffyMultiplayer::LobbyData selectedLobby;

    bool isPedding;//to make a popup as loading plase wait, avoid multiple requests from client
    sf::Text stateIsBusyText;


    bool updateLobbyList();
    int findIndexOfDelimiter(const std::string&, std::string);
    int countLobbies(const std::string&);
    FluffyMultiplayer::LobbyData convertStringToLobby(const std::array<std::string,11>&);
    int convertToInt(const std::string&);
    bool convertToBool(const std::string&);
    FluffyMultiplayer::AnAddress convertToAnAddress(const std::string&);

    int checkResponseCode(const std::string& _data);
    int refreshLobbyListCounter;
    int refreshLobbyResultCode;
    int refreshLobbyTimeoutCounter;
    std::string receivedData;
    bool successToRefreshLobbyList;

  public:
    StateMainPage();
    ~StateMainPage();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
