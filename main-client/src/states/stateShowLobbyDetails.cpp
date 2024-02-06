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
    // lobbyAsText = "------------------------------------------------";
    lobbyAsText += "\nLobby Id: " + std::to_string(selectedLobby.id);
    lobbyAsText += "\n\nLobby Max players: " + std::to_string(selectedLobby.maxPlayers);
    lobbyAsText += "\n\nLobby Current Players: " + std::to_string(selectedLobby.currentPlayers);
    lobbyAsText += "\n\nLobby Game Mode: " + std::to_string(selectedLobby.gameMode);
    lobbyAsText += "\n\nLobby Address: " + selectedLobby.address.ip.to_string() + ":" + std::to_string(selectedLobby.address.port);
    lobbyAsText += "\n\nIs Lobby Locked: " + boolToString(selectedLobby.isLocked);
    lobbyAsText += "\n\nIs Voice Chat Forbidden: " + boolToString(selectedLobby.isVoiceChatForbidden);
    lobbyAsText += "\n\nIs Text Chat Forbidden: " + boolToString(selectedLobby.isTextChatForbidden);
    lobbyAsText += "\n\nIs Specter Forbidden: " + boolToString(selectedLobby.isSpecterForbidden);
    lobbyAsText += "\n\nIs Lobby In-game: " + boolToString(selectedLobby.lobbyStatusInGame);
    lobbyAsText += "\n\nReport To LobbyList: " + boolToString(selectedLobby.showLobbyInList);

    std::string final= "Are you sure to join this lobby?\n" + lobbyAsText;
    initSimpleText(fontPath,final);

    setSimpleTextPosition(340.0,50.0);
    buttonConfirm.init("   Join",340.0,700.0, sf::Color::White, sf::Color::White, 60,30, 22);
    buttonCancel.init("  Cancel",540.0,700.0, sf::Color::White, sf::Color::White, 60,30, 22);
  }




  int StateShowLobbyDetails::stringToInt(const std::string& str)
  {
    const char* c = str.c_str();
    return std::atoi(c);
  }
  bool StateShowLobbyDetails::stringToBool(const std::string& str)
  {
    const char* c = str.c_str();
    return static_cast<bool>(std::atoi(c));
  }


  FluffyMultiplayer::AnAddress StateShowLobbyDetails::stringToAnAddress(const std::string& str)
  {
    std::vector<int> indexesIp = dataIndexes(str,MC_IP_PORT_SEPARATOR);

    std::string ipReceived = str.substr(0,indexesIp[0]);
    std::string portReceived = str.substr(indexesIp[0]+1,str.length());
    std::cout << "stringToAnAddress() -> ipReceived=" << ipReceived << "\tportReceived="<< portReceived << std::endl;
    unsigned short portFromString = static_cast<unsigned short>(stringToInt(portReceived));

    FluffyMultiplayer::AnAddress temp;
    temp.setFrom(ipReceived,portFromString);
    return temp;
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

  std::vector<std::string> StateShowLobbyDetails::dataSeparator(std::string& data, std::string delimiter)
  {
    int startIndex=0;
    std::vector<std::string> result;
    std::string str = data.substr(startIndex,data.length()-1);

    std::vector<int>indexes = dataIndexes(str,delimiter);
    for(int i=0; i<indexes.size(); i++)
    {
      int index=indexes[i];

      result.push_back(str.substr(0,index));
      str = str.substr(index+delimiter.length() ,str.length()-1);
    }
    return result;
  }


  StateShowLobbyDetails::StateShowLobbyDetails(std::string selectedLobbyStr)
  {
    //convert string to lobby
    std::vector<std::string>lData = dataSeparator(selectedLobbyStr,MC_REQUEST_DELIMITER);

    std::cout << "StateShowLobbyDetails(string) ldata.size=" << lData.size() << std::endl;
    std::cout << "StateShowLobbyDetails(string) ldata=\n";
    for(auto l: lData)
    {
        std::cout << l << std::endl;
    }

    if(lData.size()>=11)
    {
      //set on lobby
      FluffyMultiplayer::LobbyData receivedLobby
      {
        stringToBool(lData[0]),
        stringToBool(lData[1]),
        stringToBool(lData[2]),
        stringToBool(lData[3]),
        stringToBool(lData[4]),
        stringToBool(lData[5]),
        stringToInt(lData[6]),
        stringToInt(lData[7]),
        stringToInt(lData[8]),
        stringToInt(lData[9]),
        stringToAnAddress(lData[10])
      };

      lobby = receivedLobby;
      std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
      // lobbyAsText = "------------------------------------------------";
      lobbyAsText += "\nLobby Id: " + std::to_string(receivedLobby.id);
      lobbyAsText += "\n\nLobby Max players: " + std::to_string(receivedLobby.maxPlayers);
      lobbyAsText += "\n\nLobby Current Players: " + std::to_string(receivedLobby.currentPlayers);
      lobbyAsText += "\n\nLobby Game Mode: " + std::to_string(receivedLobby.gameMode);
      lobbyAsText += "\n\nLobby Address: " + receivedLobby.address.ip.to_string() + ":" + std::to_string(receivedLobby.address.port);
      lobbyAsText += "\n\nIs Lobby Locked: " + boolToString(receivedLobby.isLocked);
      lobbyAsText += "\n\nIs Voice Chat Forbidden: " + boolToString(receivedLobby.isVoiceChatForbidden);
      lobbyAsText += "\n\nIs Text Chat Forbidden: " + boolToString(receivedLobby.isTextChatForbidden);
      lobbyAsText += "\n\nIs Specter Forbidden: " + boolToString(receivedLobby.isSpecterForbidden);
      lobbyAsText += "\n\nIs Lobby In-game: " + boolToString(receivedLobby.lobbyStatusInGame);
      lobbyAsText += "\n\nReport To LobbyList: " + boolToString(receivedLobby.showLobbyInList);

      std::string final= "Are you sure to join this lobby?\n" + lobbyAsText;
      initSimpleText(fontPath,final);

      setSimpleTextPosition(340.0,50.0);
      buttonConfirm.init("   Join",340.0,700.0, sf::Color::White, sf::Color::White, 60,30, 22);
      buttonCancel.init("  Cancel",540.0,700.0, sf::Color::White, sf::Color::White, 60,30, 22);
    }
    else
      std::cout << "StateShowLobbyDetails(string) input is small size=" << lData.size() << std::endl;
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
