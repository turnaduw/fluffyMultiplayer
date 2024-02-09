#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateMainPage::StateMainPage(FluffyMultiplayer::App& app)
  {
    std::cout << "statemainPage constructor called=======================\n";
    // app.currentGameMode = new FluffyMultiplayer::GM_MENSCH(app.appWindow,app.lobby);
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    std::string txttemp = "";//+std::to_string(app.lobby->id);
    initSimpleText(fontPath, txttemp);
    setSimpleTextPosition(27.5, 27.5);

    textChatLines=0;

    pauseResumeGameButton.init("pause\nresume", ICON_PAUSE , 772.0, 27.5, sf::Color::White,sf::Color::White, 12);
    lobbySettingsButton.init("settings", ICON_SETTINGS , 858.0, 27.5, sf::Color::White,sf::Color::White, 12);
    quitButton.init("quit", PICTURE_BUTTON_QUIT_TEXTURE , 946.0, 27.5, sf::Color::White,sf::Color::White, 12);


    inputFocus = &chatInput;
    textChat.initText("",27.0, 450.0);
    textChat.setFontSize(15);
    chatInput.init("",""," chat:","enter text", 27.0, 725.0);
    sendChatButton.init("", ICON_SEND , 300.0, 725.0, sf::Color::White,sf::Color::White, 12);

    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      playerList[i].init(i,PLAYERS_LOBBY_EMPTY_SLOT_NAME,PLAYER_LIST_X, i*PLAYER_LIST_BOX_PER_PLAYER_Y, false,false,false,false,false);
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
    textChat.render(window);

    //player list
    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      playerList[i].render(window);
    }

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
    if(app.receivedTextDataList.size()>=1)
    {
      for(int i=0; i<app.receivedTextDataList.size(); i++)
      {
        currentItem = app.receivedTextDataList.front();
        cData = dataSeparator(currentItem.data, MS_DATA_DELIMITER);

        app.log.print("update called, currentItem.Code="+std::to_string(currentItem.code), FluffyMultiplayer::LogType::Information);

        switch(currentItem.code)
        {
          case RESPONSE_CONNECTION_ACCEPTED:
          case RESPONSE_INTERNAL_ERROR_FAILED_TO_CONNECT:
          case RESPONSE_ERROR_CONNECTION_NOT_EXISTS:
          case RESPONSE_ERROR_CONNECTION_EXISTS:
          case RESPONSE_ERROR_DISCONNECT_YOU_ARE_NOT_CONNECTED:
          case RESPONSE_INTERNAL_ERROR_FAILED_TO_DISCONNECT:
          case RESPONSE_ERROR_JOIN_LOBBY_YOU_ARE_BANNED:
          case RESPONSE_INTERNAL_ERROR_FAILED_TO_JOIN_INTO_LOBBY:
          case RESPONSE_ERROR_YOUR_GAME_CLIENT_VERSION_IS_OUT_OF_DATE:
          case RESPONSE_ERROR_JOIN_LOBBY_INVALID_IDENTITY:
          case RESPONSE_ERROR_JOIN_LOBBY_PASSWORD_INCORRECT:
          case RESPONSE_ERROR_GET_LOBBY_SETTINGS_NO_PERMISSION:
          case RESPONSE_ERROR_UPDATE_LOBBY_SETTINGS_NO_PERMISSION:
          case RESPONSE_INTERNAL_ERROR_FAILED_TO_STOP_GAME:
          case RESPONSE_INTERNAL_ERROR_FAILED_TO_START_GAME:
          case RESPONSE_ERROR_START_GAME_NO_PERMISSION:
          case RESPONSE_INTERNAL_ERROR_FAILED_TO_DELETE_LOBBY:
          case RESPONSE_ERROR_DELETE_LOBBY_NO_PERMISSION:
          case RESPONSE_INTERNAL_ERROR_FAILED_TO_KICK_PLAYER:
          case RESPONSE_ERROR_KICK_PLAYER_INVALID_TARGET:
          case RESPONSE_ERROR_KICK_PLAYER_NO_PERMISSION:
          case RESPONSE_ERROR_BAN_PLAYER_INVALID_TARGET:
          case RESPONSE_ERROR_BAN_PLAYER_NO_PERMISSION:
          case RESPONSE_ERROR_SEND_TEXT_CHAT_DISABLED:
          case RESPONSE_UNKNOWN_REQUEST_GAME_IS_NOT_STARTED:
          case RESPONSE_UNKNOWN_REQUEST_GAME_PAUSED_OR_NOT_STARTED:
          case RESPONSE_ERROR_SEND_VOICE_CHAT_DISABLED:
          {
            std::cout << "mainState: something received. code=" << currentItem.code << std::endl;
          }


          case RESPONSE_PLAYER_SENT_VOICE_MESSAGE:
          {

          }break;


          case RESPONSE_LOBBY_SETTINGS_UPDATED:
          {

          }break;

          case RESPONSE_LOBBY_SETTINGS_IS:
          {

          }break;

          case RESPONSE_PLAYER_DISCONNECTED:
          {

          }break;

          // RESPONSE_PLAYER_SENT_VOICE_MESSAGE
          // RESPONSE_LOBBY_SETTINGS_IS
          case RESPONSE_YOU_ARE_JOINT_INTO_LOBBY:
          {
            std::cout << "you joint into lobby.\n";

          }break;

          case RESPONSE_PLAYER_JOINT_INTO_LOBBY:
          {
            int id=stringToInt(cData[0]);
            std::string name=cData[1];
            bool owner=stringToBool(cData[2]);
            bool admin=stringToBool(cData[3]);
            bool specter=stringToBool(cData[4]);
            bool voiceChat=stringToBool(cData[5]);
            std::cout << "player joint into lobby player: " << id << "\tname:" << name << "\tvc:" << voiceChat << "\towner:" << owner << "\tspecter:" << specter << "\tadmin:" << admin << std::endl;
            tempPlayer.set(id,name,admin,voiceChat,owner,specter,false); //this is another players evertime isMe is false (only first item is me when connected and receied player data)
            players.push_back(tempPlayer);
            std::cout << "players size=" << players.size() << std::endl;

            if(players.size()-1 >= MAX_PLAYERS_IN_LOBBY)
            {
              std::cout << "out of range player, players in lobby are too many.\n";
            }
            else
            {
              //check for empty slot
              for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
              {
                if(playerList[i].getName() == PLAYERS_LOBBY_EMPTY_SLOT_NAME)
                {
                  playerList[i].init(id,name,PLAYER_LIST_X,i*PLAYER_LIST_BOX_PER_PLAYER_Y,false,voiceChat,owner,specter,admin);//false is for IsMe (this is another player always is false)
                  break;
                }
              }
            }


          }break;

          case RESPONSE_PLAYER_KICKED_FROM_LOBBY:
          {

          }break;

          case RESPONSE_PLAYER_BANNED_FROM_LOBBY:
          {

          }break;

          case RESPONSE_GAME_STOPPED:
          {
            app.gameIsRunning=false;
            std::cout << "game is stopped\n";
          }break;

          case RESPONSE_GAME_STARTED:
          {
            app.gameIsRunning=true;
            std::cout << "game is started\n";
          }break;

          case RESPONSE_PLAYER_VOICE_CHAT_ENABLED:
          {

          }break;


          case RESPONSE_PLAYER_VOICE_CHAT_DISABLED:
          {

          }break;


          case RESPONSE_PLAYER_SENT_TEXT_MESSAGE:
          {
            //limit lenght textbox
            if(textChatLines>TEXT_CHAT_BOX_MAXIMUM_LINES)
            {
              textChat.setText("");//clear
              textChatLines=0;
            }

            textChatLines++;
            textChat.appendToText(cData[0]);
          }break;

          case RESPONSE_PLAYER_CONNECTION_LOST:
          {

          }break;

          case RESPONSE_LOBBY_DELETED:
          {

          }break;

          case RESPONSE_LOBBY_OWNER_CHANGED:
          {

          }break;


          case RESPONSE_LOBBY_PLAYERS_ARE:
          //for each player: id, name, isOwner, isAdmin, isSpecter, voiceChatStatus
          //first element received is this client.
          {
            const int eachPlayerData = 6;
            // playerList.push/add
            std::string lobbyplayersAre = "lobby details received, count players=" + std::to_string(cData.size()/eachPlayerData);
            app.log.print(lobbyplayersAre, FluffyMultiplayer::LogType::Information);


            bool owner,specter,admin,voiceChat,isme;
            int id;
            std::string name;
            std::cout << "cData.size()=" << cData.size() << std::endl;

            for(int i=0; i<cData.size(); i+=eachPlayerData)
            {
              isme=false;


              if(i==0) //becuase first element is this client :)
              isme=true;

              if(i+eachPlayerData-1 >= cData.size())
              break;

              id=stringToInt(cData[i]);
              name=cData[i+1];
              owner=stringToBool(cData[i+2]);
              admin=stringToBool(cData[i+3]);
              specter=stringToBool(cData[i+4]);
              voiceChat=stringToBool(cData[i+5]);
              // playerList.push_back(FluffyMultiplayer::PlayerList{id,name,isme,voiceChat,owner,specter,admin});
              std::cout << "RESPONSE_LOBBY_PLAYERS_ARE player: " << id << "\tname:" << name << "\tisme:" << isme << "\tvc:" << voiceChat << "\towner:" << owner << "\tspecter:" << specter << "\tadmin:" << admin << std::endl;

              tempPlayer.set(id,name,admin,voiceChat,owner,specter,isme); //this is another players evertime isMe is false (only first item is me when connected and receied player data)
              players.push_back(tempPlayer);


              //check for empty slot and place current player
              for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
              {
                if(playerList[i].getName() == PLAYERS_LOBBY_EMPTY_SLOT_NAME)
                {
                  playerList[i].init(id,name,0.0,i*PLAYER_LIST_BOX_PER_PLAYER_Y,isme,voiceChat,owner,specter,admin);
                  break;
                }
              }
            }

          }break;

          default:
          {
            //apply commands from server into client game
            if(app.currentGameMode!=nullptr && app.gameIsRunning)
              app.currentGameMode->update(currentItem.code,cData);
            else
            std::cout << "gameMode is null and received response code =" << currentItem.code << std::endl;
          }
        }


        //remove proccess item
        app.receivedTextDataList.pop();
      }
    }
    // else
    // {
    //   std::cout << "ELSEEE update main state size receivedTextDataList is < 1, size=" << app.receivedTextDataList.size()  << std::endl;
    // }


    return this;
  }

  int StateMainPage::stringToInt(const std::string& str)
  {
    const char* c = str.c_str();
    return std::atoi(c);
  }
  bool StateMainPage::stringToBool(const std::string& str)
  {
    const char* c = str.c_str();
    return static_cast<bool>(std::atoi(c));
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
          std::cout << "on lobby settings clicked.\n";
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
          if(inputFocus!=nullptr)
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
