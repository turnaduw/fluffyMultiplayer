#ifndef H_MAIN_SERVER_DATATYPE_FILE
#define H_MAIN_SERVER_DATATYPE_FILE

#include <iostream>
#include <string>
#include <boost/asio.hpp>

namespace FluffyMultiplayer
{
  struct SocketDataStack
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

}

#endif
