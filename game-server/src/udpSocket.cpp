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


  void UdpSocket::prepareData(const int& code, std::string& data)
  {
     data = std::to_string(code) + data + std::string(MS_DATA_DELIMITER) + std::string(MS_REQUEST_CLOSER);
  }

  void UdpSocket::broadcast(FluffyMultiplayer::SocketSendData& currentItem)
  {
    udp::endpoint receiverEndpoint;


    auto sendTo = [&] (std::string& data, FluffyMultiplayer::AnAddress& address) -> void
    {
      receiverEndpoint.ip= address.ip;
      receiverEndpoint.port= address.port;
      socket.send_to(boost::asio::buffer(data), receiverEndpoint);
    };

    for(FluffyMultiplayer::Player receiver : currentItem.receivers)
    {
      if(currentItem.except != nullptr)
        for(FluffyMultiplayer::Player except: currentItem.except)
          if(receiver == except) //skip this client
            continue;
          else
            sendTo(currentItem.data, receiver.address);
      else //there is no exception send to all
        sendTo(currentItem.data, receiver.address);
    }
  }

  void udpSocket::send(FluffyMultiplayer::SocketSendData& currentItem)
  {
    //if socket is disabled skip send
    if(!status)
      return;

    //combine code with data and add some delimiter and closer at end of data
    prepareData(currentItem.code, currentItem.data);


    //check if receivers are only one sendDirect else send as broadcast
    if(currentItem.receivers == nullptr)
      sendDirect(currentItem.data,currentItem.receiver);
    else
      broadcast(currentItem);
  }
  void UdpSocket::sendDirect(std::string& data,
                const FluffyMultiplayer::AnAddress& receiver,
                bool areDataPrepared=true, int& code=0)
  {
    if(!areDataPrepared)
      prepareData(code,data);

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
