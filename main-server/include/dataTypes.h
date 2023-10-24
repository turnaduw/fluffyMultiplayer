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
}

#endif
