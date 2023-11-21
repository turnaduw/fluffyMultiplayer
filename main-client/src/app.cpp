#include "../include/app.h"

#include "../include/states.h"

namespace FluffyMultiplayer
{
  void App::sendData()
  {
    FluffyMultiplayer::DataSecurity dSecurity;
    std::string data;
    while(true)
    {
      FluffyMultiplayer::AnAddress server = getServerAddress();
      if(getSendDataStatus() && sendDataQueue.size()>=1)
      {
          data = sendDataQueue.front();
          dSecurity.encryptData(data);
          socket.send(data, server.ip, server.port);
          sendDataQueue.pop();
      }
    }
  }

  void App::receiveData()
  {
    FluffyMultiplayer::DataSecurity dSecurity;
    std::string data;
    while (true)
    {
      FluffyMultiplayer::AnAddress server = getServerAddress();
      if(getReceiveDataStatus())
      {
        char receive_data[MC_RECEIVE_BUFFER];
        udp::endpoint senderEndpoint;
        size_t receive_length = socket.receive(receive_data,senderEndpoint);

        if(receive_length >=1 &&
            senderEndpoint.address() == server.ip &&
            senderEndpoint.port() == server.port)
        {
          data = std::string(receive_data,receive_length);
          dSecurity.decryptData(data);
          receivedDataQueue.push(data);
        }
      }
    }
  }

  void App::init()
  {
    currentState = new FluffyMultiplayer::StateReadServerList;
    appWindow.setFramerateLimit(60);

  }

  int App::getServerListCount() const
  {
    return serverList.size()-1;
  }

  FluffyMultiplayer::AnAddress App::popServerAddress()
  {
    FluffyMultiplayer::AnAddress temp = serverList.front();
    serverList.pop();
    return temp;
  }

  void App::run()
  {

    while (appWindow.isOpen())
    {
       // Event processing
       sf::Event event;
       while (appWindow.pollEvent(event))
       {
           // Request for closing the window
           if (event.type == sf::Event::Closed)
               appWindow.close();

           currentState = currentState->eventHandle((*this),event);
       }

       // Clear the whole window before rendering a new frame
       appWindow.clear();

       currentState = currentState->update((*this),receivedDataQueue,sendDataQueue);

       // Draw some graphical entities
       currentState->render(appWindow);

       // End the current frame and display its contents on screen
       appWindow.display();
    }

  }

  FluffyMultiplayer::AnAddress App::getServerAddress() const
  {
    return serverAddress;
  }

  void App::setServer(FluffyMultiplayer::AnAddress address)
  {
    //check address

    //set
    serverAddress.ip = address.ip;
    serverAddress.port = address.port;
  }

  void App::addServer(FluffyMultiplayer::AnAddress address)
  {
    //check address

    //add
    serverList.push(address);
  }

  void App::setAppPort(unsigned short port)
  {
      appPort = port;
      socket.changePort(appPort);
  }

  unsigned short App::getAppPort() const
  {
    return appPort;
  }

  bool App::getReceiveDataStatus() const
  {
    return receiveDataStatus;
  }

  bool App::getSendDataStatus() const
  {
    return sendDataStatus;
  }

  void App::setReceiveDataStatus(bool status)
  {
    receiveDataStatus = status;
  }

  void App::setSendDataStatus(bool status)
  {
    sendDataStatus = status;
  }

}
