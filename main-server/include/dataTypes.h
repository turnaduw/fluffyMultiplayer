#ifndef H_MAIN_SERVER_DATATYPE_FILE
#define H_MAIN_SERVER_DATATYPE_FILE

#include <iostream>
#include <string>
#include <boost/asio.hpp>

namespace FluffyMultiplayer
{
  struct SocketDataQueue
  {
    int code;
    boost::asio::ip::address ip;
    unsigned short port;
    std::string data;
  };

  struct ConnectedClients
  {
    boost::asio::ip::address ip;
    unsigned short port;
  };

  struct CreateLobbyData
  {
    std::string identity;
    int gameMode;
    int maxPlayers;
    bool voiceChatForbidden;
    bool textChatForbidden;
    bool specterForbidden;
    std::string password;
  };

  struct TimeAndDate
  {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
  };

  struct LoginClientData
  {
    std::string username;
    std::string password;
    std::string hardwareId;
    std::string oldIdentity;
  };

  struct RegisterClientData
  {
    std::string email;
    std::string username;
    std::string password;
    std::string hardwareId;
  };

  int convertStringToInt(const std::string&);
}

#endif
