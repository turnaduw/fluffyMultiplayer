#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateShowLobbyDetials::StateShowLobbyDetials(FluffyMultiplayer::LobbyData selectedLobby)
  {
    lobby = selectedLobby;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    std::string lobbyAsText = "------------------------------------------------";
    lobbyAsText += "\nlobby id: " + std::to_string(selectedLobby.id);
    lobbyAsText += "\nlobby maxplayers: " + std::to_string(selectedLobby.maxPlayers);
    lobbyAsText += "\nlobby currentplayers: " + std::to_string(selectedLobby.currentPlayers);
    lobbyAsText += "\nlobby gameMode: " + std::to_string(selectedLobby.gameMode);
    lobbyAsText += "\nlobby address: " + std::to_string(selectedLobby.address.ip) + ":" + std::to_string(selectedLobby.address.port);
    lobbyAsText += "\nis lobby locked:" + (selectedLobby.isLocked? "yes" : "no");
    lobbyAsText += "\nis voice chat forbidden:" + (selectedLobby.isVoiceChatForbidden? "yes" : "no");
    lobbyAsText += "\nis text chat forbidden:" + (selectedLobby.isTextChatForbidden? "yes" : "no");
    lobbyAsText += "\nis specter forbidden:" + (selectedLobby.isSpecterForbidden? "yes" : "no");
    lobbyAsText += "\nis lobby in-game:" + (selectedLobby.lobbyStatusInGame? "yes" : "no");
    lobbyAsText += "\nlobby will show in lobbyList: " + (selectedLobby.showLobbyInList? "yes" : "no");

    std::string final=   "state StateShowLobbyDetials\nare you sure to join this lobby?\npress enter to join other keys to cancel.\n\nlobby=\n" + lobbyAsText;
    initSimpleText(fontPath,final);
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
    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
          {
            return new FluffyMultiplayer::StateJoinLobby(lobby.address);
          }
          else
          {
            return new FluffyMultiplayer::StateMainPage;
          }
        }
        break;
    }
    return this;
  }
}
