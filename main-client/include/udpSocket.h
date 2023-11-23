#ifndef H_UDP_SOCKET_CLASS
#define H_UDP_SOCKET_CLASS

#include "config.h"
#include "dataType.h"

#include <boost/asio.hpp>
using boost::asio::ip::udp;

namespace FluffyMultiplayer
{
  class UdpSocket
  {
    private:
      udp::socket socket;
      udp::endpoint senderEndpoint;
      size_t receive_length;
      char tempData[MC_RECEIVE_BUFFER];


    public:
      UdpSocket(boost::asio::io_context& io_context, unsigned short port)
          : socket(io_context, udp::endpoint(udp::v4(), port))
      {
        socket.non_blocking(true);
      }
      ~UdpSocket();

      void changePort(unsigned short);
      void send(std::string data, boost::asio::ip::address receiverIp, unsigned short receiverPort);
      size_t receive(char* const data, udp::endpoint& senderAddress);
  };
}

#endif
