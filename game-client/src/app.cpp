#include "../include/app.h"

#include "../include/states.h"

namespace FluffyMultiplayer
{

  void App::stopGame()
  {
    gameIsRunning=false;
  }

  void App::startGame()
  {
    gameIsRunning=true;

  }

  void App::changeGameMode(int gameModeId)
  {
    switch (gameModeId)
    {
      case GAME_MODE_MENSCH_ID:
      {
        stopGame();
        log.print("selected gameMode is Mensch", FluffyMultiplayer::LogType::Information);
        currentGameMode = new FluffyMultiplayer::GM_MENSCH(appWindow,lobby);
      }break;

      default:
      {
        log.print("unknown lobby gameMode... gm-code="+std::to_string(lobby->gameMode),
                  FluffyMultiplayer::LogType::Warning);
        currentGameMode = nullptr;
      }break;
    }
  }

  void App::sendData()
  {
    FluffyMultiplayer::SocketSendData currentItem;
    while(true)
    {
      try
      {
        //lock mutex for socket to avoid segment fault or data corruption.
        boost::lock_guard<boost::mutex> lock(sendMutex);


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


  bool App::addSendVoice(int code, std::string data)
  {
    sendVoiceDataList.push
    (
        {code,data}
    );
    return true;
  }
  bool App::addSendVoice(int code)
  {
    sendVoiceDataList.push
    (
        {code,APP_EMPTY_DATA_SEND}
    );
    return true;
  }
  bool App::addSendText(int code, std::string data)
  {
    sendTextDataList.push
    (
      {code,data}
    );
    return true;
  }
  bool App::addSendText(int code)
  {
    sendTextDataList.push
    (
      {code,APP_EMPTY_DATA_SEND}
    );
    return true;
  }

  void App::setIdentity(std::string _identity)
  {
    identity= _identity;
  }
  std::string App::getIdentity() const
  {
    return identity;
  }


  bool App::isSenderIsServer(FluffyMultiplayer::AnAddress sender)
  {
    if
      (
        sender == lobby->address //check for text port
        ||
        (sender.ip == lobby->address.ip && sender.port == lobby->address.port) //check for voice port
      )
    {
      return true;
    }
    return false;
  }


  void App::prepareData(FluffyMultiplayer::SocketReceiveData& currentItem)
  {

    //get code
    //these MS_DATA_CODE_INDEX_X are from config.h
    char codes [3] = {currentItem.data[MS_DATA_CODE_INDEX_A], currentItem.data[MS_DATA_CODE_INDEX_B], currentItem.data[MS_DATA_CODE_INDEX_C]};
    const char* temp = codes;
    currentItem.code = std::atoi(temp);


    std::string delimiter = MS_DATA_DELIMITER;
    std::string closer = MS_REQUEST_CLOSER;
    //remove code and end (delimiter and closer)
    currentItem.data = currentItem.data.substr(3,currentItem.data.length()-(delimiter.length()+closer.length()));
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

        if(!isSenderIsServer(currentItem.sender))
        {
          //invalid sender..
          log.print("received sender is invalid.", FluffyMultiplayer::LogType::Information);
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
    isLobbySettingsOn=false;
    inLobby=false; //a flag turn off to avoid to run gameMode->render after constructor StateMainPage called, turn on when received code == joint into lobby
    //init log
    log.init(APP_LOG_FILENAME,APP_PRINT_LOGS_LEVEL);

    log.print("game init.", FluffyMultiplayer::LogType::Information);
    lobby = new FluffyMultiplayer::LobbyData;

    lobby->address.set(_server);
    identity = _identity;

    log.print("game lobby address=."+lobby->address.getAsString(), FluffyMultiplayer::LogType::Information);
    log.print("game identity=."+identity, FluffyMultiplayer::LogType::Information);


    appIsRunning=true;
    gameIsRunning=false;


    //init sockets
    socketVoice = new FluffyMultiplayer::UdpSocket(ioContextVoice, DEFAULT_TEXT_PORT,FluffyMultiplayer::AnAddress{lobby->address.ip, lobby->voicePort}, TEXT_CHAT_BUFFER_SIZE);
    socketText = new FluffyMultiplayer::UdpSocket(ioContextText, DEFAULT_VOICE_PORT,FluffyMultiplayer::AnAddress{lobby->address.ip, lobby->address.port}, VOICE_CHAT_BUFFER_SIZE);

    //init voice chat
    // voiceChat.init(DEFAULT_PLAYER_VOICE_ENABLE);


    //init threads
    receive_thread = boost::thread(&FluffyMultiplayer::App::receiveData, this);
    send_thread = boost::thread(&FluffyMultiplayer::App::sendData, this);

    //init state
    currentState = new FluffyMultiplayer::StateBindPickPort;
    currentGameMode=nullptr;

    //init window
    appWindow.setFramerateLimit(WINDOW_MAX_FPS);

  }
  void App::close()
  {
    log.print("game has been safely closed.", FluffyMultiplayer::LogType::Information);
    appIsRunning=false;
    appWindow.close();
  }

  void App::run()
  {
    log.print("game run.", FluffyMultiplayer::LogType::Information);
    while (appWindow.isOpen())
    {
      if(!appIsRunning)
        break;
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

           if(currentGameMode!=nullptr)
            currentGameMode->eventHandle(appWindow,event,sendTextDataList,sendMutex);
       }

       // Clear the whole window before rendering a new frame
       appWindow.clear(WINDOW_BACKGROUND_COLOR);

       currentState = currentState->update((*this));

       // Draw some graphical entities (z:0)
       if(currentGameMode!=nullptr && inLobby && isLobbySettingsOn==false)
        if(currentGameMode->getGameStarted())
        {
          /*
          this top condition is for to avoid render gameMode Elements before gameMode
           turn his flag on, this is for to avoid render gameMode when that gameMode is not ready some
           gameModes have problem to render/setposition to elements before game start.
          */
          currentGameMode->render(appWindow);
        }

       currentState->render(appWindow);


       //draw notifications (z:2)
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
