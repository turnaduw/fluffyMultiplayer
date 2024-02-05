#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateMainPage::StateMainPage(FluffyMultiplayer::App& app)
  {
    std::cout << "statemainPage constructor called=======================\n";
    app.currentGameMode = new FluffyMultiplayer::GM_MENSCH(app.appWindow,app.lobby);
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    std::string txttemp = "lobbyId:"+std::to_string(app.lobby->id);
    initSimpleText(fontPath, txttemp);
    setSimpleTextPosition(150.0, 5.0);



    lobbySettingsButton.init("settings", ICON_SETTINGS , 867.0, 25.0, sf::Color::Black,sf::Color::White, 12);
    quitButton.init("quit", PICTURE_BUTTON_QUIT_TEXTURE , 946.0, 25.0, sf::Color::Black,sf::Color::White, 12);
    pauseResumeGameButton.init("pause\nresume", ICON_PAUSE , 946.0, 25.0, sf::Color::Black,sf::Color::White, 12);


    inputFocus = &chatInput;
    chatInput.init("","","chat:","enter text", 27.0, 500.0);
    sendChatButton.init("semd", ICON_SEND , 75.0, 500.0, sf::Color::Black,sf::Color::White, 12);


    //example
    float startX=200.0;
    float startY=100.0;
    float eachXstep=0.0;
    float eachYstep=30.0;
    std::array<std::string,MAX_PLAYERS_IN_LOBBY> tempNames = {"peter","alex","mamad","joker","Yray"};
    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      playerList[i] = FluffyMultiplayer::PlayerList(i+1,tempNames[i],startX,startY);
      startX+=eachXstep;
      startY+=eachYstep;
    }
  }

  StateMainPage::~StateMainPage()
  {

  }

  void StateMainPage::render(sf::RenderWindow& window)
  {
    window.draw(theText); //lobby id label

    quitButton.render(window);
    lobbySettingsButton.render(window);
    chatInput.render(window);
    sendChatButton.render(window);
    pauseResumeGameButton.render(window);


    //player list
    // for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    // {
      // playerList[i].render(window);
    // }
    //chat box

    //game..

  }

  std::vector<int> dataIndexes(const std::string& data, const std::string& delimiter)
  {
    std::vector<int> result;
    std::string str;
    str = data;

    int index;
    for(int i=0; i<data.length(); i++)
    {
      if(str.empty())
        break;

      index = str.find(delimiter);
      if (index == std::string::npos) //delimiter not found
        break;

      str = str.substr(index+delimiter.length() ,str.length()-1);
      result.push_back(index);
    }

    return result;
  }

  std::vector<std::string> dataSeparator(const std::string& data, std::string delimiter, int startIndex=0)
  {
    std::cout << "dataSeparator.data="+data << std::endl;
    std::vector<std::string> result;
    std::string str = data.substr(startIndex,data.length()-1);

    std::vector<int>indexes = dataIndexes(str,delimiter);
    for(int i=0; i<indexes.size(); i++)
    {
      int index=indexes[i];

      result.push_back(str.substr(0,index));
      str = str.substr(index+delimiter.length() ,str.length()-1);
    }
    return result;
  }



  FluffyMultiplayer::AppState* StateMainPage::update(FluffyMultiplayer::App& app)
  {
    //read from received data..
    FluffyMultiplayer::SocketReceiveData currentItem;
    std::vector<std::string> cData;
    if(app.receivedTextDataList.size()>1)
      for(int i=0; i<app.receivedTextDataList.size(); i++)
      {
        currentItem = app.receivedTextDataList.front();
        cData = dataSeparator(currentItem.data, MS_DATA_DELIMITER);



        switch(currentItem.code)
        {

          // RESPONSE_PLAYER_SENT_VOICE_MESSAGE
          // RESPONSE_LOBBY_SETTINGS_IS


          case RESPONSE_PLAYER_JOINT_INTO_LOBBY:
          {

          }break;

          case RESPONSE_PLAYER_KICKED_FROM_LOBBY:
          {

          }break;

          case RESPONSE_PLAYER_BANNED_FROM_LOBBY:
          {

          }break;

          case RESPONSE_GAME_STOPPED:
          {

          }break;

          case RESPONSE_GAME_STARTED:
          {

          }break;

          case RESPONSE_PLAYER_VOICE_CHAT_ENABLED:
          {

          }break;


          case RESPONSE_PLAYER_VOICE_CHAT_DISABLED:
          {

          }break;


          case RESPONSE_PLAYER_SENT_TEXT_MESSAGE:
          {

          }break;

          case RESPONSE_PLAYER_CONNECTION_LOST:
          {

          }break;

          case RESPONSE_LOBBY_DELETED:
          {

          }break;

          case RESPONSE_LOBBY_SETTINGS_UPDATED:
          {

          }break;


          case RESPONSE_LOBBY_OWNER_CHANGED:
          {

          }break;


          case RESPONSE_UNKNOWN_REQUEST_GAME_PAUSED_OR_NOT_STARTED:
          {

          }break;


          case RESPONSE_UNKNOWN_REQUEST_GAME_IS_NOT_STARTED:
          {

          }break;


          case RESPONSE_LOBBY_PLAYERS_ARE: //playerId, playerName
          {
            // playerList.push/add
            app.log.print("lobby details..", FluffyMultiplayer::LogType::Information);
            if(cData.size()%2==0) //to avoid 3 items then we call segfault by pres
            {
              for(int i=0; i<cData.size(); i+=2)
              {
                std::cout << "player: id=" << cData[i] << "\tname=" << cData[i+1] << std::endl;
              }
            }
            else
              std::cout << "a problem while loading players\n";
          }break;

          default:
          {
            //apply commands from server into client game
            if(app.currentGameMode!=nullptr)
              app.currentGameMode->update(currentItem.code,cData);
          }
        }


        //remove proccess item
         app.receivedTextDataList.pop();
      }


    return this;
  }

  void StateMainPage::sendChat(FluffyMultiplayer::App& app)
  {
    std::string txt = chatInput.getEnteredText();
    if(!txt.empty())
    {
      app.addSendText(REQUEST_SEND_TEXT_CHAT,txt);
      chatInput.clear();

      //remove focus from chat
      inputFocus=nullptr;
    }
  }

  FluffyMultiplayer::AppState* StateMainPage::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        //remove focus from chat
        inputFocus=nullptr;

        // #define REQUEST_KICK_PLAYER 109
        // #define REQUEST_BAN_PLAYER 110
        // #define REQUEST_SEND_VOICE_CHAT 113
        // #define REQUEST_ENABLE_DISABLE_VOICE_CHAT 115 //exit client from voice chats

        if(sendChatButton.getButtonBound().contains(mousePosition))
        {
          sendChat(app);
        }
        else if(quitButton.getButtonBound().contains(mousePosition))
        {
          app.addSendText(REQUEST_DISCONNECT_FROM_LOBBY);
        }
        else if(chatInput.getInputBoxBound().contains(mousePosition))
        {
          inputFocus=&chatInput;
        }
        else if(lobbySettingsButton.getButtonBound().contains(mousePosition))
        {
          // app.addSendText(REQUEST_GET_LOBBY_SETTINGS);
          //
          // //pass
          // return new FluffyMultiplayer::StateWaitForResponse
          // (
          //   "request get lobby settings sent..\nplease wait..",
          //   this,
          //   std::vector<FluffyMultiplayer::AppState*>
          //       {
          //         new FluffyMultiplayer::StateLobbySettings(app)
          //       },
          //   std::vector<int>
          //     {
          //       RESPONSE_LOBBY_SETTINGS_IS
          //     }
          // );
        }
        else if(pauseResumeGameButton.getButtonBound().contains(mousePosition))
        {
          app.addSendText(REQUEST_STOP_START_GAME);
        }
        else
        {
          std::cout << "posx:" << mousePosition.x << "\tposy:" << mousePosition.y << std::endl;
        }

    }

    //keyboard
    switch(event.type)
    {
      case sf::Event::KeyPressed:
      {
        if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
        {
          sendChat(app);
        }
        if(event.key.code == sf::Keyboard::Backspace)
        {
          if(inputFocus!=nullptr)
            inputFocus->removeFromText();
        }
      }break;

      case sf::Event::TextEntered:
      {
        if (event.text.unicode < 128)
        {
          if(inputFocus != nullptr)
            inputFocus->update(static_cast<char>(event.text.unicode));
        }
      }break;

    }



    //keyboards:
    return this;
  }
}
