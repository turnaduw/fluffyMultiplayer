#include "../include/app.h"

namespace FluffyMultiplayer
{
  void App::sendData()
  {
    FluffyMultiplayer::SocketSendData currentItem;
    while(true)
    {
      try
      {
        //text data
        if(sendTextDataList.size()>=1) //on that socket self will check socketStatus before send
        {
          currentItem = sendTextDataList.front();
          ds.encryptData(currentItem.data);

          socketText->send(currentItem);

          //remove proceessed element
          sendTextDataList.pop();
        }
      }
      catch (std::exception& e)
      {
          std::string errorMsg = e.what();
          log.print("from App::sendData catched exception: "+errorMsg, FluffyMultiplayer::LogType::Warning);
          continue;
      }
    }
  }




  void App::receiveData()
  {
    FluffyMultiplayer::SocketReceiveData currentItem;
    udp::endpoint senderEndpoint;
    size_t receive_length;

    while (true)
    {
      try
      {
        //text socket receive
        char receive_data[TEXT_CHAT_BUFFER_SIZE];
        receive_length = socketText->receive(receive_data,senderEndpoint);
        currentItem.sender.setFromEndpoint(senderEndpoint);

        if(isConnectionBlocked(currentItem.sender))
        {
          // RESPONSE_ERROR_CONNECTION_BLOCKED
        }
        else
        {
          if(receive_length >=1)
          {
            currentItem.data = std::string(receive_data,receive_length);
            ds.decryptData(currentItem.data);

            //sperate c.code and data and remove code and closers from .data
            prepareData(currentItem);

            log.print("received text from="+currentItem.sender.getAsString()+
            "\tcode="+std::to_string(currentItem.code)+"\tdata="+
            currentItem.data, FluffyMultiplayer::LogType::Information);

            // std::cout << "received from: " <<  senderEndpoint.address() << ":" << senderEndpoint.port() << " data = " << data << "]" << std::endl;
            receivedTextDataList.push(currentItem);
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
            log.print("from App::receiveData catched exception: "+errorMsg, FluffyMultiplayer::LogType::Warning);
            continue;
            // throw;
          }
      }
    }
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
    socketVoice = new FluffyMultiplayer::UdpSocket(ioContextVoice, DEFAULT_TEXT_PORT,FluffyMultiplayer::AnAddress{lobby.address.ip, lobby.address.port}, TEXT_CHAT_BUFFER_SIZE);
    socketText = new FluffyMultiplayer::UdpSocket(ioContextText, DEFAULT_VOICE_PORT,FluffyMultiplayer::AnAddress{lobby.address.ip, lobby.voicePort}, VOICE_CHAT_BUFFER_SIZE);

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

}
