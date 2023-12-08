#include "../../include/states.h"

namespace FluffyMultiplayer
{

  std::string StateShowLobbyDetails::boolToString(bool b)
  {
    std::string result = (b ? "true" : "false");
    return result;
  }

  StateShowLobbyDetails::StateShowLobbyDetails(FluffyMultiplayer::LobbyData selectedLobby)
  {
    lobby = selectedLobby;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    std::string lobbyAsText = "------------------------------------------------";
    lobbyAsText += "\nlobby id: " + std::to_string(selectedLobby.id);
    lobbyAsText += "\nlobby maxplayers: " + std::to_string(selectedLobby.maxPlayers);
    lobbyAsText += "\nlobby currentplayers: " + std::to_string(selectedLobby.currentPlayers);
    lobbyAsText += "\nlobby gameMode: " + std::to_string(selectedLobby.gameMode);
    lobbyAsText += "\nlobby address: " + selectedLobby.address.ip.to_string() + ":" + std::to_string(selectedLobby.address.port);
    lobbyAsText += "\nis lobby locked:" + boolToString(selectedLobby.isLocked);
    lobbyAsText += "\nis voice chat forbidden:" + boolToString(selectedLobby.isVoiceChatForbidden);
    lobbyAsText += "\nis text chat forbidden:" + boolToString(selectedLobby.isTextChatForbidden);
    lobbyAsText += "\nis specter forbidden:" + boolToString(selectedLobby.isSpecterForbidden);
    lobbyAsText += "\nis lobby in-game:" + boolToString(selectedLobby.lobbyStatusInGame);
    lobbyAsText += "\nlobby will show in lobbyList: " + boolToString(selectedLobby.showLobbyInList);

    std::string final=   "state StateShowLobbyDetails\nare you sure to join this lobby?\npress enter to join other keys to cancel.\n\nlobby=\n\n" + lobbyAsText;
    initSimpleText(fontPath,final);

    buttonConfirm.init("Join",200.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
    buttonCancel.init("Cancel",400.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
  }

  StateShowLobbyDetails::~StateShowLobbyDetails()
  {

  }

  void StateShowLobbyDetails::render(sf::RenderWindow& window)
  {
    window.draw(theText);
    buttonConfirm.render(window);
    buttonCancel.render(window);
  }


  FluffyMultiplayer::AppState* StateShowLobbyDetails::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateShowLobbyDetails::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        if(buttonConfirm.getButtonBound().contains(mousePosition))
        {
          return new FluffyMultiplayer::StateJoinLobby(lobby.address);
        }
        else if(buttonCancel.getButtonBound().contains(mousePosition))
        {
          return new FluffyMultiplayer::StateMainPage;
        }
    }





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
