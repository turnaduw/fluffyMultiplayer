#ifndef H_MAIN_CLIENT_DATA_TYPE
#define H_MAIN_CLIENT_DATA_TYPE
#include <boost/asio.hpp>

namespace FluffyMultiplayer
{
  struct AnAddress
  {
    boost::asio::ip::address ip;
    unsigned short port;
  };
  struct LobbyData
  {
     bool isLocked;
     bool isVoiceChatForbidden;
     bool isTextChatForbidden;
     bool isSpecterForbidden;
     bool lobbyStatusInGame;
     bool showLobbyInList;
     int id;
     int maxPlayers;
     int currentPlayers;
     int gameMode;
     FluffyMultiplayer::AnAddress address;
  };

  //for StateWaitForResponse forms
  /*because these forms need to receive same args passed into
      state if state has received error to refill form automatically.*/
  struct LoginFormData
  {
      std::array<std::string,2> _inputs;
      std::array<std::string,2> _errors;
      bool _saveLoginStatus;
      std::string identity;
  };
  struct RegisterFormData
  {
    std::array<std::string,3> _inputs;
    std::array<std::string,3> _errors;
    std::string identity;
  };
  // struct CreateLobbyFormData
  // {
  //
  // };
}

#endif
