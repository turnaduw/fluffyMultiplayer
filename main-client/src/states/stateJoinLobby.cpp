#include "../../include/states.h"

namespace FluffyMultiplayer
{

  int StateJoinLobby::findIndexOfDelimiter(const std::string& str, std::string c)
  {
    int index = str.find(c);
    if (index != std::string::npos)
      return index;
    else
      return -1;
  }
  int StateJoinLobby::convertToInt(const std::string& str)
  {
    const char* val = str.c_str();
    return std::atoi(val);
  }

  FluffyMultiplayer::AnAddress StateJoinLobby::convertStringToAddress(std::string str)
  {

    int posEndIp = findIndexOfDelimiter(str,MC_IP_PORT_SEPARATOR);
    str = str.substr(posEndIp,str.length());

    int posCol = findIndexOfDelimiter(str,MC_IP_PORT_SEPARATOR);
    FluffyMultiplayer::AnAddress tempAddress
    {
      boost::asio::ip::address::from_string( str.substr(0,posEndIp) ),
      static_cast<unsigned short>( convertToInt(str.substr(posEndIp,str.length()) ) )
    };

    return tempAddress;
  }

  StateJoinLobby::StateJoinLobby(FluffyMultiplayer::AnAddress target_address)
  {
    gameServerAddress = target_address;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state joinLobby\n game has been launched.");
  }

  StateJoinLobby::StateJoinLobby(std::string target_address)
  {
    //convert address from string to FluffyMultiplayer::AnAddress
    gameServerAddress = convertStringToAddress(target_address);
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state joinLobby\n game has been launched.");
  }

  StateJoinLobby::StateJoinLobby()
  {

  }
  
  StateJoinLobby::~StateJoinLobby()
  {

  }

  void StateJoinLobby::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateJoinLobby::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    app.openGame(gameServerAddress);
    return this;
  }


  FluffyMultiplayer::AppState* StateJoinLobby::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
