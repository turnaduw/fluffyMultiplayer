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
     int maxPlayers;
     int currentPlayers;
     int gameMode;
     std::string address;
  };
}

#endif
