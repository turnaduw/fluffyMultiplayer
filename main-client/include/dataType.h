#ifndef H_MAIN_CLIENT_DATA_TYPE
#define H_MAIN_CLIENT_DATA_TYPE
#include <boost/asio.hpp>
using boost::asio::ip::udp;

namespace FluffyMultiplayer
{
  struct AnAddress
  {
    boost::asio::ip::address ip;
    unsigned short port;
    void setFrom(const std::string& str, unsigned short _port)
    {
      ip = boost::asio::ip::address::from_string(str);
      port = _port;
    }
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
  struct CreateLobbyFormData
  {
    std::string clientIdentity;
    int gameMode;
    int maxPlayers;
    bool isTextChatAllowed;
    bool isVoiceChatAllowed;
    bool isSpecterAllowed;
    std::string password;
    std::string globalErrors; //like you're limited, maxplayers is invalid and so
    std::string address; //dont need AnAddress type, will convert it..
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
