#include "../include/udpSocket.h"

namespace FluffyMultiplayer
{
  void UdpSocket::enable()
  {
    statusSocket=true;
  }
  void UdpSocket::disable()
  {
    statusSocket=true;
  }
  bool UdpSocket::getStatus() const
  {
    return statusSocket;
  }

  void UdpSocket::setPort(unsigned short newPort)
  {
    try
    {
      socket.close(); // Close the existing socket

      udp::endpoint newEndpoint(udp::v4(), newPort);
      socket.open(newEndpoint.protocol());
      socket.bind(newEndpoint);
    }
    catch (std::exception& e)
    {
        std::string errorMsg = e.what();
        log.print("from UdpSocket::setPort catched exception: "+errorMsg, FluffyMultiplayer::LogType::Warning);
    }
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


    // auto sendTo = [&] (std::string& data, FluffyMultiplayer::AnAddress& address) -> void
    // {
    //   udp::endpoint receiverEndpoint(address.ip, address.port);
    //   socket.send_to(boost::asio::buffer(data), receiverEndpoint);
    // };

    for(int i=0; i<currentItem.receivers->size();i++)
    {
      if(currentItem.except != nullptr)
        for(int j=0; j<currentItem.except->size();j++)
          if(currentItem.receivers[i] == currentItem.except[j]) //skip this client
            continue;
          else
            sendDirect(currentItem.data, (*currentItem.receivers)[i].address,true,0);
      else //there is no exception send to all
        sendDirect(currentItem.data, (*currentItem.receivers)[i].address,true,0);
    }
  }

  void UdpSocket::send(FluffyMultiplayer::SocketSendData& currentItem)
  {
    //if socket is disabled skip send
    if(!statusSocket)
      return;

    //combine code with data and add some delimiter and closer at end of data
    prepareData(currentItem.code, currentItem.data);


    //check if receivers are only one sendDirect else send as broadcast
    if(currentItem.receivers == nullptr)
      sendDirect(currentItem.data,currentItem.receiver,true,0);
    else
      broadcast(currentItem);
  }
  void UdpSocket::sendDirect(std::string& data,
                const FluffyMultiplayer::AnAddress& receiver,
                bool areDataPrepared, int code)
  {
    try
    {
      if(!areDataPrepared)
        prepareData(code,data);

      udp::endpoint receiverEndpoint(receiver.ip, receiver.port);
      socket.send_to(boost::asio::buffer(data), receiverEndpoint);
      log.print("from UdpSocket::sendDirect successfully sent. "+data, FluffyMultiplayer::LogType::Success);
    }
    catch (std::exception& e)
    {
        // std::string errorMsg = e.what();
        // log.print("from UdpSocket::sendDirect catched exception: "+errorMsg, FluffyMultiplayer::LogType::Warning);
    }
  }



  size_t UdpSocket::receive(char * const data, udp::endpoint& senderAddress)
  {
    try
    {
      if (!statusSocket)
        return 0;

      char buffer[bufferSize];
      std::memset(buffer, 0, bufferSize);  // Initialize buffer with null characters using memset

      size_t receive_length = socket.receive_from(boost::asio::buffer(buffer, bufferSize), senderEndpoint);

      if(receive_length > bufferSize)
      {
        log.print("fron udpSocket::receive received_lenght is more than buffer size.",FluffyMultiplayer::LogType::Warning);
      }
      else
      {
        // Copy received data to the output buffer
        std::copy_n(buffer, receive_length, data);

        // Set the sender address
        senderAddress = senderEndpoint;

        log.print("from UdpSocket::receive successfully received. len="+receive_length, FluffyMultiplayer::LogType::Success);
        return receive_length;
      }
    }
    catch (std::exception& e)
    {
      // std::string errorMsg = e.what();
      // log.print("from UdpSocket::receive catched exception: " + errorMsg, FluffyMultiplayer::LogType::Warning);
    }
    return 0;
  }



}
