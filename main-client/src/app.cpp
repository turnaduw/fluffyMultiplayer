#include "../include/app.h"

namespace FluffyMultiplayer
{
  App::~App()
  {

  }

  void App::init()
  {
    // currentState = ;
    appWindow.setFramerateLimit(60);

  }

  void App::run(std::queue<std::string>& received_data_queue, std::queue<std::string>& send_data_queue)
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

       currentState = currentState->update((*this),received_data_queue,send_data_queue);

       // Draw some graphical entities
       currentState->render(appWindow);

       // End the current frame and display its contents on screen
       appWindow.display();
    }

  }

  FluffyMultiplayer::AnAddress App::getServerAddress()
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
  }

  unsigned short App::getAppPort()
  {
    return appPort;
  }

  bool App::getReceiveDataStatus()
  {
    return receiveDataStatus;
  }

  bool App::getSendDataStatus()
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