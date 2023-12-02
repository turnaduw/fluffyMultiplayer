#ifndef H_STATE_MAIN_PAGE
#define H_STATE_MAIN_PAGE

#include "../appState.h"
#include "../uiComponents/textInput.h"
#include "../uiComponents/button.h"
#include "../uiComponents/pictureButton.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateMainPage : public AppState
  {
  private:
    std::vector<FluffyMultiplayer::LobbyData> lobbyList;
    FluffyMultiplayer::LobbyData selectedLobby;

    bool isPedding;//to make a popup as loading plase wait, avoid multiple requests from client


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

    //to avoid duplicate return code while calling them from event mouse, keyboard
    FluffyMultiplayer::AppState* formFinishedResult(bool isSubmit);
    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;


    // ---------------- UI

    sf::Text stateIsBusyText;

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
