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
  enum AppStates
  {
    INIT_APP,
    READING_SERVER_LIST,
    INIT_SOCKET,
    CONNECTING_TO_SERVER,

    LOGIN_FORM,
    SEND_LOGIN_DATA,
    REGISTER_FROM,
    SEND_REGISTER_DATA,
    MAIN_PAGE,

    LOGOUT
  };
}

#endif
