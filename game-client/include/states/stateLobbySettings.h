#ifndef H_STATE_LOBBY_SETTINGS_FORM
#define H_STATE_LOBBY_SETTINGS_FORM

#include "../appState.h"
#include "../uiComponents/textInput.h"
#include "../uiComponents/button.h"
#include "../uiComponents/checkBox.h"
#include "../uiComponents/playerList.h"
#include "../uiComponents/spinBox.h"
#include "../uiComponents/text.h"
#include "../dataType.h"
#include "../config.h"

#include <vector>
#include <array>

//convert string to int
#include <cstdlib>

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateLobbySettings : public AppState
  {
  private:
    FluffyMultiplayer::LobbyData lobby;

    //focus
    FluffyMultiplayer::TextInput* inputFocus;

    //text inputs
    FluffyMultiplayer::TextInput passwordInput;

    //spinboxes
    FluffyMultiplayer::SpinBox gameModeSpinBox;
    FluffyMultiplayer::SpinBox maxPlayersSpinBox;
    FluffyMultiplayer::SpinBox ownerSpinBox;


    //check boxes
    FluffyMultiplayer::CheckBox specterCheckBox;
    FluffyMultiplayer::CheckBox voiceChatCheckBox;
    FluffyMultiplayer::CheckBox textChatCheckBox;

    //buttons
    FluffyMultiplayer::Button buttonSubmit;
    FluffyMultiplayer::Button buttonCancel;
    FluffyMultiplayer::Button buttonDeleteLobby;


    //to avoid duplicate return code while calling them from event mouse, keyboard
    // FluffyMultiplayer::AppState* formFinishedResult(std::string clientIdentity, bool isSubmit);
    std::vector<std::string> maxPlayersList;
    int stringToInt(const std::string&);
    bool stringToBool(const std::string&);

    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;
    std::array<sf::FloatRect,2> gameModeSpinBoxBounds;
    std::array<sf::FloatRect,2> maxPlayersSpinBoxBounds;
    std::array<sf::FloatRect,2> ownerSpinBoxBounds;



    //data pointers..
    std::vector<FluffyMultiplayer::Player>* players;
    int* textChatLines;
    std::array<FluffyMultiplayer::PlayerList,MAX_PLAYERS_IN_LOBBY>* playerList;
    FluffyMultiplayer::Text* textChat;
    bool* amILobbyOwner;
    FluffyMultiplayer::App* app;


    //to receive and hold lobby data from mainState
    std::vector<std::string>* lobbyStr;  //gamemode, maxplayers, textchat, voicechat, specter, owner, password

    void init();

  public:
    StateLobbySettings(std::vector<FluffyMultiplayer::Player>&,
                                int&,
                                std::array<FluffyMultiplayer::PlayerList,MAX_PLAYERS_IN_LOBBY>&,
                                FluffyMultiplayer::Text&,
                                bool&,
                                FluffyMultiplayer::App&,
                                std::vector<std::string>&);
    ~StateLobbySettings();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
