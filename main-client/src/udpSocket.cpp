#include "../include/udpSocket.h"

namespace FluffyMultiplayer
{
  void UdpSocket::changePort(unsigned short newPort)
  {
    socket.close(); // Close the existing socket

    udp::endpoint newEndpoint(udp::v4(), newPort);
    socket.open(newEndpoint.protocol());
    socket.bind(newEndpoint);
  }

  void UdpSocket::send(std::string data, boost::asio::ip::address receiverIp,
      unsigned short receiverPort)
  {
    udp::endpoint receiverEndpoint(receiverIp, receiverPort);
    socket.send_to(boost::asio::buffer(data), receiverEndpoint);
  }

  size_t UdpSocket::receive(char * const data, udp::endpoint& senderAddress)
  {
    //make tempData empty
    for(int i=0; i<MC_RECEIVE_BUFFER; i++)
      tempData[i] = '\0';


    //will return to tell caller how much has length
    receive_length = socket.receive_from(boost::asio::buffer(tempData), senderEndpoint);


    //set data
    for(int i=0; i<MC_RECEIVE_BUFFER; i++)
      data[i] = tempData[i];


    //by ref to tell caller what are sender info
    senderAddress = senderEndpoint;

    return receive_length;
  }


  UdpSocket::~UdpSocket()
  {

  }
}
