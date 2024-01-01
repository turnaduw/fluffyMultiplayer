#include "../include/app.h"

namespace FluffyMultiplayer
{
  void App::sendData()
  {
      FluffyMultiplayer::DataSecurity dSecurity;
      std::string data;
      while(true)
      {
        if(getSendDataStatus() && sendDataQueue.size()>=1)
        {
          FluffyMultiplayer::AnAddress server = getServerAddress();
          data = sendDataQueue.front();
          dSecurity.encryptData(data);
          socket.send(data, server.ip, server.port);
          sendDataQueue.pop();
          std::cout << "data sent = " << data << " to " << server.ip << ":" << server.port << " size() = " << sendDataQueue.size() << std::endl;
        }
      }
  }

  void App::receiveData()
  {
    FluffyMultiplayer::DataSecurity dSecurity;
    std::string data;
    while (true)
    {
      try
      {
        if(getReceiveDataStatus())
        {
          FluffyMultiplayer::AnAddress server = getServerAddress();
          char receive_data[MC_RECEIVE_BUFFER];
          udp::endpoint senderEndpoint;
          size_t receive_length = socket.receive(receive_data,senderEndpoint);
          if(receive_length >=1)
          {
            //if this dont call maybe sometimes thread starts and another section change ip n port in that time and time ip,port still wrong make program wrong
            server = getServerAddress();
          }
          if(receive_length >=1 &&
            senderEndpoint.address() == server.ip &&
            senderEndpoint.port() == server.port)
            {
              data = std::string(receive_data,receive_length);
              std::cout << "received from: " <<  senderEndpoint.address() << ":" << senderEndpoint.port() << " data = " << data << "]" << std::endl;
              dSecurity.decryptData(data);
              receivedDataQueue.push(data);
            }
          }
        }
        catch (std::exception& e)
        {
            std::string errorMsg = e.what();
            if (errorMsg.find("receive_from: Resource temporarily unavailable") != std::string::npos)
            {
                continue;
            }
            else
            {
                throw;
            }
        }
  }

  }


  void App::addDataToSendQueue(const std::string& req)
  {
      sendDataQueue.push(req);
  }


  std::string App::getReceivedDataQueue()
  {
    std::string data = receivedDataQueue.front();
    receivedDataQueue.pop();
    return data;
  }

  void App::openGame(FluffyMultiplayer::AnAddress address)
  {
    std::cout << "open game\n target server address is= " << address.ip << ":" << address.port << "\tidentity=" << getIdentity() << std::endl;

    //open new terminal and pass args innit
    std::string gclient = "gnome-terminal -- " +
            std::string(GAME_CLIENT_APPLICATION_PATH) +
            std::string(GAME_CLIENT_APPLICATION_NAME) +
            " " +
            address.ip.to_string() +
            " " +
            std::to_string(address.port) +
            " " +
            getIdentity();

    //convert stirnt to const char* then pass into system
    std::system(gclient.c_str());
  }

  void App::init(FluffyMultiplayer::AnAddress _server, std::string _identity)
  {
    lobby.address = _server;
    identity = _identity;

    appIsRunning=true;
    gameIsRunning=false;

    //init log
    log.init(APP_LOG_FILENAME,APP_PRINT_LOGS_LEVEL);


    //init sockets
    socketVoice = new FluffyMultiplayer::UdpSocket(ioContextVoice, DEFAULT_TEXT_PORT, TEXT_CHAT_BUFFER_SIZE);
    socketText = new FluffyMultiplayer::UdpSocket(ioContextText, DEFAULT_VOICE_PORT, VOICE_CHAT_BUFFER_SIZE);


    //init voice chat
    voiceChat.init();


    //init threads
    receive_thread = boost::thread(&FluffyMultiplayer::App::receiveData, this);
    send_thread = boost::thread(&FluffyMultiplayer::App::sendData, this);

    //init state
    currentState = new FluffyMultiplayer::StateConnectingToServer;
    currentGameMode = nullptr;

    //init window
    appWindow.setFramerateLimit(WINDOW_MAX_FPS);

  }
  void App::close()
  {
    log.print("app has been safely closed.", FluffyMultiplayer::LogType::Information);
    appWindow.close();
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
                close();

           //notification box buttons
           if(event.type == sf::Event::MouseButtonPressed && notificationQueue.size()>=1)
           {
               mousePosition = appWindow.mapPixelToCoords(sf::Mouse::getPosition(appWindow));
               if(notificationBox.closeButton.getButtonBound().contains(mousePosition))
               {
                 notificationBox.closeBox();
                 notificationQueue.pop();
               }
               else if(notificationBox.copyButton.getButtonBound().contains(mousePosition))
               {
                 std::cout << "clipboard -> error is: " << notificationBox.copyError() << std::endl;
               }
               else if(notificationBox.getBackofBackgroundBound().contains(mousePosition))
               {
                 notificationBox.closeBox();
                 notificationQueue.pop();
               }
           }

           //state events
           currentState = currentState->eventHandle((*this),event);
       }

       // Clear the whole window before rendering a new frame
       appWindow.clear(WINDOW_BACKGROUND_COLOR);

       currentState = currentState->update((*this),receivedDataQueue,sendDataQueue);

       // Draw some graphical entities
       currentState->render(appWindow);

       //draw notifications
       if(notificationQueue.size()>=1)
       {
         notificationBox.init(notificationQueue.front(), appWindow.getSize());
         notificationBox.render(appWindow);
       }

       // End the current frame and display its contents on screen
       appWindow.display();
    }

  }

  void App::clearIdentity()
  {
      try
      {

        //try to remove identity file
        const char* filename = CLIENT_LOCAL_APP_CONFIG_FILE;

        if (std::remove(filename) != 0)
        {
            std::cout << "while clearIdentity failed to delete file " CLIENT_LOCAL_APP_CONFIG_FILE << std::endl;


            //delete failed go fill identity with empty value
            std::string filename = CLIENT_LOCAL_APP_CONFIG_FILE;
            std::ofstream theFile(filename);
            theFile << "";
            theFile.close();
        }
        else
        {
            std::cout << CLIENT_LOCAL_APP_CONFIG_FILE " file successfully deleted." << std::endl;
        }

        setIdentity("");
        std::cout << "success to clean identity" << std::endl;
      }
      catch (std::exception& e)
      {
        std::cout << "failed to clean identity" << std::endl;
      }
  }
  void App::setIdentity(std::string str)
  {
    identity=str;
  }
  std::string App::getIdentity() const
  {
    return identity;
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
