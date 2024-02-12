#ifndef H_STATE_MAIN_PAGE
#define H_STATE_MAIN_PAGE

#include "../appState.h"

#include "../uiComponents/playerList.h"
#include "../uiComponents/pictureButton.h"
#include "../uiComponents/textInput.h"

#include "../config.h"
#include <array>
#include <vector>
#include <string>

//random number
#include <cstdlib>
#include <ctime>

#include "../gameModes.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class
  class StateMainPage : public AppState
  {
  private:
    //userinterface
    std::vector<FluffyMultiplayer::Player> players;
    FluffyMultiplayer::Player tempPlayer; //to avoid delecre everytime a player.
    int textChatLines;//to count line of text chat received.

    std::array<FluffyMultiplayer::PlayerList,MAX_PLAYERS_IN_LOBBY> playerList;


    FluffyMultiplayer::Text textChat;

    sf::Vertex topLine[2];
    sf::Vertex chatAndPlayerListLine[2];
    sf::Vertex seperatorChatWithPlayerListLine[2];

    bool amILobbyOwner; //this flag will use for render or not owner options for this client

    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;

    FluffyMultiplayer::PictureButton quitButton;
    FluffyMultiplayer::PictureButton lobbySettingsButton;
    FluffyMultiplayer::PictureButton pauseResumeGameButton;

    FluffyMultiplayer::TextInput* inputFocus;
    FluffyMultiplayer::TextInput chatInput;
    FluffyMultiplayer::PictureButton sendChatButton;

    bool stringToBool(const std::string&);
    int stringToInt(const std::string&);

    void sendChat(FluffyMultiplayer::App& app); //to avoid duplicate code for send chat
    void appendToTextChat(std::string&);
    std::string getPlayerNameById(int&);
    void removeFromLobby(int&);
    void isThisPcOwner(int);

  public:
    StateMainPage(FluffyMultiplayer::App&);
    StateMainPage(std::vector<FluffyMultiplayer::Player> players,
                                int textChatLines,
                                std::array<FluffyMultiplayer::PlayerList,MAX_PLAYERS_IN_LOBBY> playerList,
                                FluffyMultiplayer::Text textChat,
                                bool amILobbyOwner, FluffyMultiplayer::App&);
    ~StateMainPage();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
