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


  enum LogType
  {
      Error=0,
      Warning,
      Success,
      Information,
      All
  };

  enum NotificationType
  {
    normal=0,
    error,
    success,
    warning
  };

  enum NotificationPosition
  {
    center=0,
    bottomLeft,
    bottomRight,
    bottomCenter
  };

  struct NotificationData
  {
    int code;
    std::string title;
    std::string message;
    NotificationType type;
    NotificationPosition position;
  };
}

#endif
