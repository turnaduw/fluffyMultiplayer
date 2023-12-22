#include "../include/udpSocket.h"

namespace FluffyMultiplayer
{
  void UdpSocket::enable()
  {
    status=true;
  }
  void UdpSocket::disable()
  {
    status=true;
  }
  bool UdpSocket::getStatus() const
  {
    return status;
  }

  void UdpSocket::setPort(unsigned short newPort)
  {
    socket.close(); // Close the existing socket

    udp::endpoint newEndpoint(udp::v4(), newPort);
    socket.open(newEndpoint.protocol());
    socket.bind(newEndpoint);
  }
  unsigned short UdpSocket::getPort() const
  {
    return port;
  }


  void UdpSocket::prepareData(std::string& data)
  {
     data = send_data.code + send_data.data + std::string(DELIMITER) + std::string(CLOSER);
  }

  void UdpSocket::broadcast(FluffyMultiplayer::SocketSendData& send_data)
  {
    if(!status)
      return;

    for(FluffyMultiplayer::Player receiver : (*send_data.receivers))
    {
      if(if send_data.except != nullptr)
      {
        for(FluffyMultiplayer::Player except: (*send_data.except))
        {
          if(receiver == except) //skip this client
            continue;
          else
          {
            prepareData(send_data.data);
            udp::endpoint receiverEndpoint(receiver.address.ip, receiver.address.port);
            socket.send_to(boost::asio::buffer(send_data.data), receiverEndpoint);
          }
        }
      }
      else //there is no exception send to all
      {
        prepareData(send_data.data);
        udp::endpoint receiverEndpoint(receiver.address.ip, receiver.address.port);
        socket.send_to(boost::asio::buffer(send_data.data), receiverEndpoint);
      }
    }
  }

  void UdpSocket::send(std::string& data, const FluffyMultiplayer::AnAddress& receiver)
  {
    if(!status)
      return;
    udp::endpoint receiverEndpoint(receiver.ip, receiver.port);
    socket.send_to(boost::asio::buffer(data), receiverEndpoint);
  }


  size_t UdpSocket::receive(char * const data, udp::endpoint& senderAddress)
  {
    if(!status)
      return 0;

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

}
