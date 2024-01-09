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

  void UdpSocket::send(FluffyMultiplayer::SocketSendData& currentItem)
  {
    //if socket is disabled skip send
    if(!statusSocket)
      return;

    //combine code with data and add some delimiter and closer at end of data
    sendDirect(currentItem.data,false,currentItem.code);
  }

  void UdpSocket::sendDirect(std::string& data,
                bool areDataPrepared, const int& code)
  {
    try
    {
      if(!areDataPrepared)
        prepareData(code,data);

      socket.send_to(boost::asio::buffer(data), receiverEndpoint);
    }
    catch (std::exception& e)
    {
        std::string errorMsg = e.what();
        log.print("from UdpSocket::sendDirect catched exception: "+errorMsg, FluffyMultiplayer::LogType::Warning);
    }
  }


  size_t UdpSocket::receive(char * const data, udp::endpoint& senderAddress)
  {
    try
    {
      char buffer[bufferSize];
      if(!statusSocket)
        return 0;

      //make buffer empty
      for(int i=0; i<bufferSize; i++)
        buffer[i] = '\0';


      //will return to tell caller how much has length
      char temp[bufferSize];
      receive_length = socket.receive_from(boost::asio::buffer(buffer,bufferSize), senderEndpoint);


      //check if sender is that server continue
      if(senderEndpoint == receiverEndpoint)
      {
        //by ref to tell caller what are sender info
        senderAddress = senderEndpoint;

        //set data
        for(int i=0; i<bufferSize; i++)
        data[i] = buffer[i];


        return receive_length;
      }
      else
      {
        return -1;
      }
      return -1;
    }
    catch (std::exception& e)
    {
        std::string errorMsg = e.what();
        log.print("from UdpSocket::receive catched exception: "+errorMsg, FluffyMultiplayer::LogType::Warning);
    }
    return 0;
  }

}