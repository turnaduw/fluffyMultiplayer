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
    lobbyAsText = "------------------------------------------------";
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

    std::string final=   "state StateShowLobbyDetails\nare you sure to join this lobby?\npress enter to join.\n\nlobby=\n\n" + lobbyAsText;
    initSimpleText(fontPath,final);

    buttonConfirm.init("Join",200.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
    buttonCancel.init("Cancel",400.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
  }





  std::vector<int> StateShowLobbyDetails::dataIndexes(const std::string& data, const std::string& delimiter) const
  {
    std::vector<int> result;
    std::string str;
    str = data;

    int index;
    for(int i=0; i<data.length(); i++)
    {
      if(str.empty())
        break;

      index = str.find(delimiter);
      if (index == std::string::npos) //delimiter not found
        break;

      str = str.substr(index+delimiter.length() ,str.length()-1);
      result.push_back(index);
    }

    return result;
  }
  std::string StateShowLobbyDetails::dataSeparator(std::string& data, std::string delimiter)
  {
    std::string res;
    std::array<std::string,MS_GET_LOBBY_LIST_LOBBY_FILEDS> result;

    std::vector<int>indexes = dataIndexes(data,delimiter);
    int index;
    for(int i=0; i<MS_GET_LOBBY_LIST_LOBBY_FILEDS-1; i++)
    {
      index = indexes[i];
      result[i] = data.substr(0,index);
      data = data.substr(index+delimiter.length() ,data.length());
    }

    res = "------------------------------------------------";
    res += "\nis lobby locked:" +  result[0];
    res += "\nis voice chat forbidden:" +  result[1];
    res += "\nis text chat forbidden:" +  result[2];
    res += "\nis specter forbidden:" +  result[3];
    res += "\nis lobby in-game:" +  result[4];
    res += "\nlobby will show in lobbyList: " + result[5];
    res += "\nlobby id: " + result[6];
    res += "\nlobby maxplayers: " + result[7];
    res += "\nlobby currentplayers: " +result[8];
    res += "\nlobby gameMode: " + result[9];
    res += "\nlobby address: " + result[10];

    return res;
  }


  StateShowLobbyDetails::StateShowLobbyDetails(std::string selectedLobbyStr)
  {
    //convert string to lobby
    lobbyAsText = dataSeparator(selectedLobbyStr,MC_REQUEST_DELIMITER);

    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;


    std::string final=   "state StateShowLobbyDetails\nare you sure to join this lobby?\npress enter to join.\n\nlobby=\n\n" + lobbyAsText;
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
        }
        break;
    }
    return this;
  }
}
