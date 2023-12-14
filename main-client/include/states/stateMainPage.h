#ifndef H_STATE_MAIN_PAGE
#define H_STATE_MAIN_PAGE

#include "../appState.h"
#include "../uiComponents/textInput.h"
#include "../uiComponents/button.h"
#include "../uiComponents/pictureButton.h"
#include "../uiComponents/lobbyCell.h"
#include "../config.h"
#include <array>
#include <vector>
#include <string>

//random number
#include <cstdlib>
#include <ctime>

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateMainPage : public AppState
  {
  private:

    //lobby
    std::vector<FluffyMultiplayer::LobbyData> lobbyList;
    FluffyMultiplayer::LobbyData selectedLobby;

    //to avoid create variable each round of loop
    std::vector<std::string> lobbyGameModeTexturePathList;

    int findIndexOfDelimiter(const std::string&, std::string);
    FluffyMultiplayer::LobbyData convertStringToLobby(const std::array<std::string,MS_GET_LOBBY_LIST_LOBBY_FILEDS>&);
    int convertToInt(const std::string&);
    bool convertToBool(const std::string&);
    FluffyMultiplayer::AnAddress convertToAnAddress(const std::string&);

    //to avoid duplicate return code while calling them from event mouse, keyboard
    FluffyMultiplayer::AppState* formFinishedResult(bool isSubmit);
    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;


    // ---------------- UI

    sf::Vertex line[2];

    //focus
    FluffyMultiplayer::TextInput* inputFocus;

    //text inputs
    FluffyMultiplayer::TextInput lobbyIdInput;

    //buttons
    FluffyMultiplayer::Button buttonSubmitLobbyId;
    FluffyMultiplayer::Button buttonCreateLobby;
    FluffyMultiplayer::PictureButton buttonLogout;
    FluffyMultiplayer::PictureButton buttonRefreshLobbyList;
    FluffyMultiplayer::PictureButton buttonQuit;


    //lobby
    std::array<FluffyMultiplayer::LobbyCell,MS_GET_LOBBY_LIST_COUNT_OF_RESULTS> lobbyCells;

    std::array<std::string,MS_GET_LOBBY_LIST_LOBBY_FILEDS> dataSeparator(std::string&, std::string, int);
    std::vector<int> dataIndexes(const std::string& data, const std::string& delimiter) const;

  public:
    StateMainPage();
    StateMainPage(std::string);
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
