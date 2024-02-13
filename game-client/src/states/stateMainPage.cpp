#include "../../include/states.h"

namespace FluffyMultiplayer
{

  StateMainPage::StateMainPage(std::vector<FluffyMultiplayer::Player> _players,
                              int _textChatLines,
                              std::array<FluffyMultiplayer::PlayerList,MAX_PLAYERS_IN_LOBBY> _playerList,
                              FluffyMultiplayer::Text _textChat,
                              bool _amILobbyOwner,FluffyMultiplayer::App& app)
  {
    app.isLobbySettingsOn=false;
    players = _players;
    textChatLines = _textChatLines;
    amILobbyOwner = _amILobbyOwner;

    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    std::string txttemp = "Lobby Id: " + std::to_string(app.lobby->id);
    initSimpleText(fontPath, txttemp);
    setSimpleTextPosition(255.0,27.5);
    setSimpleTextFontsize(15);

    pauseResumeGameButton.init("", ICON_PAUSE , 772.0, 27.5, sf::Color::White,sf::Color::White, 12);
    lobbySettingsButton.init("", ICON_SETTINGS , 858.0, 27.5, sf::Color::White,sf::Color::White, 12);
    quitButton.init("", PICTURE_BUTTON_QUIT_TEXTURE , 946.0, 27.5, sf::Color::White,sf::Color::White, 12);

    //intit lines
    topLine[0] = sf::Vertex(sf::Vector2f(250 , 27.0+70));
    topLine[1] = sf::Vertex(sf::Vector2f(998, 27.0+70));
    chatAndPlayerListLine[0] = sf::Vertex(sf::Vector2f(250 , 0));
    chatAndPlayerListLine[1] = sf::Vertex(sf::Vector2f(250, 750));
    seperatorChatWithPlayerListLine[0] = sf::Vertex(sf::Vector2f(0 , 440));
    seperatorChatWithPlayerListLine[1] = sf::Vertex(sf::Vector2f(250, 440));


    inputFocus = &chatInput;
    textChat.initText("",5.0, 450.0);
    textChat.setFontSize(15);
    chatInput.init("","","",PLACE_HOLDER_TEXT_CHAT, 5.0, 740.0);
    sendChatButton.init("", ICON_SEND , 303.0, 740.0, sf::Color::White,sf::Color::White, 12);
    textChat = _textChat;

    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      playerList[i].init(-1,PLAYERS_LOBBY_EMPTY_SLOT_NAME,PLAYER_LIST_X, i*PLAYER_LIST_BOX_PER_PLAYER_Y, false,false,false,false,false);
    }
    playerList = _playerList;

    //send a request to get latest lobby info maybe after update owner or other data of lobby changed.
    app.addSendText(REQUEST_GET_LOBBY_INFO);
  }


  StateMainPage::StateMainPage(FluffyMultiplayer::App& app)
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    std::string txttemp = "Lobby Id: ????";
    initSimpleText(fontPath, txttemp);
    setSimpleTextPosition(255.0,27.5);
    setSimpleTextFontsize(15);

    textChatLines=0;
    amILobbyOwner=false;

    pauseResumeGameButton.init("", ICON_PAUSE , 772.0, 27.5, sf::Color::White,sf::Color::White, 12);
    lobbySettingsButton.init("", ICON_SETTINGS , 858.0, 27.5, sf::Color::White,sf::Color::White, 12);
    quitButton.init("", PICTURE_BUTTON_QUIT_TEXTURE , 946.0, 27.5, sf::Color::White,sf::Color::White, 12);

    //intit lines
    topLine[0] = sf::Vertex(sf::Vector2f(250 , 27.0+70));
    topLine[1] = sf::Vertex(sf::Vector2f(998, 27.0+70));
    chatAndPlayerListLine[0] = sf::Vertex(sf::Vector2f(250 , 0));
    chatAndPlayerListLine[1] = sf::Vertex(sf::Vector2f(250, 750));
    seperatorChatWithPlayerListLine[0] = sf::Vertex(sf::Vector2f(0 , 440));
    seperatorChatWithPlayerListLine[1] = sf::Vertex(sf::Vector2f(250, 440));


    inputFocus = &chatInput;
    textChat.initText("",5.0, 450.0);
    textChat.setFontSize(15);
    chatInput.init("","","",PLACE_HOLDER_TEXT_CHAT, 5.0, 740.0);
    sendChatButton.init("", ICON_SEND , 303.0, 740.0, sf::Color::White,sf::Color::White, 12);

    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      playerList[i].init(-1,PLAYERS_LOBBY_EMPTY_SLOT_NAME,PLAYER_LIST_X, i*PLAYER_LIST_BOX_PER_PLAYER_Y, false,false,false,false,false);
    }

    //send a request to get lobby info then if resposne code received will apply into app.lobby pointer's
    app.addSendText(REQUEST_GET_LOBBY_INFO);
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

    //lines
    window.draw(topLine, 2, sf::Lines);
    window.draw(chatAndPlayerListLine, 2, sf::Lines);
    window.draw(seperatorChatWithPlayerListLine, 2, sf::Lines);

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
          case RESPONSE_LOBBY_INFO_IS:
          //id,gm,max,current,voicePort,voiceStatus,textStatus,specterStatus
          {
            app.lobby->id=stringToInt(cData[0]);
            app.lobby->gameMode=stringToInt(cData[1]);
            app.lobby->maxPlayers=stringToInt(cData[2]);
            app.lobby->currentPlayers=stringToInt(cData[3]);
            app.lobby->voicePort=static_cast<unsigned short>(stringToInt(cData[4]));
            app.lobby->isVoiceChatForbidden=stringToBool(cData[5]);
            app.lobby->isTextChatForbidden=stringToBool(cData[6]);
            app.lobby->isSpecterForbidden=stringToBool(cData[7]);

            //set lobby id to show to player
            setSimpleTextValue("Lobby Id: "+cData[0]);

            //set lobby gameMode
            app.changeGameMode(app.lobby->gameMode,playerList);


          }break;

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
          case RESPONSE_START_GAME_NOT_ENOUGH_PLAYER_TO_START:
          {
            app.log.print("mainState: something received. code="+std::to_string(currentItem.code), FluffyMultiplayer::LogType::Information);
          }


          case RESPONSE_PLAYER_SENT_VOICE_MESSAGE:
          {
            std::cout << "received voice message from other clients..\n";
          }break;


          case RESPONSE_LOBBY_OWNER_CHANGED:  //new owner id
          {
            //owner left the lobby so owner changed..
            app.lobby->ownerId=stringToInt(cData[0]);

            int newOwnerId = app.lobby->ownerId;

            isThisPcOwner(newOwnerId);
            //try to find new owner and apply
            for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
            {
               if(playerList[i].getId() == newOwnerId)
               {
                 //add owner to new owner
                 playerList[i].setOwner(true);

                 //remove owner from old owner.
                 for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
                 {
                   if(playerList[i].getIsOwner() == true && playerList[i].getId() != newOwnerId)
                   {
                     playerList[i].setOwner(false);
                     break; //only one client were owner do not to check others if old owner found
                   }
                 }
               }
            }
          }break;

          case RESPONSE_LOBBY_SETTINGS_UPDATED:
          //id,gm,max,current,voicePort,voiceStatus,textStatus,specterStatus,ownerid
          {
              app.lobby->id=stringToInt(cData[0]);
              //set lobby id to show to player
              setSimpleTextValue("Lobby Id: "+cData[0]);

              app.lobby->gameMode=stringToInt(cData[1]);
              //set lobby gameMode
              app.changeGameMode(app.lobby->gameMode,playerList);

              app.lobby->maxPlayers=stringToInt(cData[2]);
              app.lobby->currentPlayers=stringToInt(cData[3]);
              app.lobby->voicePort=static_cast<unsigned short>(stringToInt(cData[4]));
              app.lobby->isVoiceChatForbidden=stringToBool(cData[5]);
              app.lobby->isTextChatForbidden=stringToBool(cData[6]);
              app.lobby->isSpecterForbidden=stringToBool(cData[7]);

              app.lobby->ownerId=stringToInt(cData[8]);


              int newOwnerId = app.lobby->ownerId;
              isThisPcOwner(newOwnerId);
              //check for owner changes:
              for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
              {
                if(playerList[i].getId() == newOwnerId)
                  if(playerList[i].getIsOwner() == true) //owner didnt changed.
                    break;
                  else //owner changed..
                  {
                    //add owner to new owner
                    playerList[i].setOwner(true);

                    //remove owner from old owner.
                    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
                      if(playerList[i].getIsOwner() == true && playerList[i].getId() != newOwnerId)
                      {
                        playerList[i].setOwner(false);
                        break; //only one client were owner do not to check others if old owner found
                      }
                    }
               }


          }break;

          case RESPONSE_LOBBY_SETTINGS_IS:
          //lobby id, maxplayer, gameMode, currentplayers, voiceChatStatus, textChatStatus, specterStatus, password, ownerId, owner username
          {
            app.isLobbySettingsOn=true;
            //update applobby

            std::cout << "open lobby settings form and insert data into it\n"
                      << "lobby data for owner: lobbyId:" << cData[0] << "\tmaxP:"
                      << cData[1] << "\tGameMode:" << cData[2] << "\tcurrentP:" << cData[3]
                      << "\tvoiceChat:" << cData[4] << "\ttextChat:" << cData[5]
                      << "\tspecterStatus:" << cData[6] << "\tpassowrd:" << cData[7]
                      << "\townerId:" << cData[8] << "\townerUsername:" << cData[9]
                      << std::endl;

            //gamemode, maxplayers, textchat, voicechat, specter, owner, password
            std::vector<std::string> lobbyStr = {cData[2], cData[1], cData[5], cData[4], cData[6], cData[8], cData[7]};

            //remove proccessed elemnt to avoid re proccess them becuase we are getting out of this state,
            app.receivedTextDataList.pop();
            return new FluffyMultiplayer::StateLobbySettings(players,textChatLines,playerList,textChat,amILobbyOwner,app,lobbyStr);
          }break;

          case RESPONSE_PLAYER_DISCONNECTED: //id
          {
            int playerid = stringToInt(cData[0]);
            std::string disconnectMessage = "player (";
            disconnectMessage += getPlayerNameById(playerid);
            disconnectMessage += ") left the lobby.\n";
            removeFromLobby(playerid);
            appendToTextChat(disconnectMessage);
          }break;

          // RESPONSE_PLAYER_SENT_VOICE_MESSAGE
          // RESPONSE_LOBBY_SETTINGS_IS
          case RESPONSE_YOU_ARE_JOINT_INTO_LOBBY:
          {
            std::string _message = "you joint into lobby.\n";
            appendToTextChat(_message);
          }break;

          case RESPONSE_PLAYER_JOINT_INTO_LOBBY:
          {
            int id=stringToInt(cData[0]);
            std::string name=cData[1];
            bool owner=stringToBool(cData[2]);
            bool admin=stringToBool(cData[3]);
            bool specter=stringToBool(cData[4]);
            bool voiceChat=stringToBool(cData[5]);
            tempPlayer.set(id,name,admin,voiceChat,owner,specter,false); //this is another players evertime isMe is false (only first item is me when connected and receied player data)
            players.push_back(tempPlayer);

            std::string connectMessage = "player (";
            connectMessage += name;
            connectMessage += ") joint to the lobby.\n";
            appendToTextChat(connectMessage);


            //check for empty slot
            for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
            {
              if(playerList[i].getName() == PLAYERS_LOBBY_EMPTY_SLOT_NAME)
              {
                playerList[i].init(id,name,PLAYER_LIST_X,i*PLAYER_LIST_BOX_PER_PLAYER_Y,false,voiceChat,owner,specter,admin);//false is for IsMe (this is another player always is false)

                if(!specter && app.currentGameMode!=nullptr)
                {
                  app.currentGameMode->addPlayerToGame(playerList[i]);
                }
                break;
              }
            }


          }break;

          case RESPONSE_PLAYER_KICKED_FROM_LOBBY: //player id
          {
            int playerid = stringToInt(cData[0]);
            std::string messageKick = "Player (";
            messageKick += getPlayerNameById(playerid);
            messageKick += ") has been kicked from lobby.\n";
            appendToTextChat(messageKick);
            removeFromLobby(playerid);
          }break;

          case RESPONSE_PLAYER_BANNED_FROM_LOBBY: //player id
          {
            int playerid = stringToInt(cData[0]);
            std::string messageBan = "Player (";
            messageBan += getPlayerNameById(playerid);
            messageBan += ") has been banned from lobby.\n";
            appendToTextChat(messageBan);
            removeFromLobby(playerid);
          }break;

          case RESPONSE_GAME_STOPPED:
          {
            app.stopGame();
            std::cout << "game is stopped\n";
          }break;

          case RESPONSE_GAME_STARTED:
          {
            app.startGame();
            std::cout << "game is started\n";
          }break;

          case RESPONSE_PLAYER_VOICE_CHAT_ENABLED: //clientId
          {
            int clientid = stringToInt(cData[0]);
            for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
            {
              if(playerList[i].getId() == clientid)
              {
                playerList[i].updateVoiceChatStatus(true);
                break;
              }
            }
          }break;


          case RESPONSE_PLAYER_VOICE_CHAT_DISABLED: //clientId
          {
            int clientid = stringToInt(cData[0]);
            for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
            {
              if(playerList[i].getId() == clientid)
              {
                playerList[i].updateVoiceChatStatus(false);
                break;
              }
            }
          }break;


          case RESPONSE_PLAYER_SENT_TEXT_MESSAGE: //message
          {
            appendToTextChat(cData[0]);
          }break;

          case RESPONSE_PLAYER_CONNECTION_LOST:
          {
            std::string connectionlostmessage="someone connection lost.\n";
            appendToTextChat(connectionlostmessage);
          }break;

          case RESPONSE_LOBBY_DELETED:
          {
            app.stopGame();
            std::string lobbydeleted = "lobby deleted.\n";
            appendToTextChat(lobbydeleted);
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



              if(i+eachPlayerData-1 >= cData.size())
              break;

              id=stringToInt(cData[i]);
              name=cData[i+1];
              owner=stringToBool(cData[i+2]);
              admin=stringToBool(cData[i+3]);
              specter=stringToBool(cData[i+4]);
              voiceChat=stringToBool(cData[i+5]);
              if(i==0) //becuase first element is this client :)
              {
                isme=true;
                if(owner==true)
                {
                  amILobbyOwner=true;
                }
              }
              // playerList.push_back(FluffyMultiplayer::PlayerList{id,name,isme,voiceChat,owner,specter,admin});
              std::cout << "RESPONSE_LOBBY_PLAYERS_ARE player: " << id << "\tname:" << name << "\tisme:" << isme << "\tvc:" << voiceChat << "\towner:" << owner << "\tspecter:" << specter << "\tadmin:" << admin << std::endl;

              tempPlayer.set(id,name,admin,voiceChat,owner,specter,isme); //this is another players evertime isMe is false (only first item is me when connected and receied player data)
              players.push_back(tempPlayer);


              //check for empty slot and place current player
              for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
              {
                if(playerList[i].getName() == PLAYERS_LOBBY_EMPTY_SLOT_NAME)
                {
                  playerList[i].init(id,name,PLAYER_LIST_X,i*PLAYER_LIST_BOX_PER_PLAYER_Y,isme,voiceChat,owner,specter,admin);
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
    return this;
  }

  void StateMainPage::isThisPcOwner(int oid)
  {
    if(playerList[THIS_CLIENT_PLYARE_LOBBY_INDEX].getId() == oid) //index 0 is always for this pc
    {
      amILobbyOwner=true;
    }
    else
    {
      amILobbyOwner=false;
    }
  }

  void StateMainPage::removeFromLobby(int& id)
  {
    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      if(playerList[i].getId() == id)
      {
        playerList[i].clear();

        //also later remove this player from vector<player>players


        break;
      }
    }
  }

  std::string StateMainPage::getPlayerNameById(int& id)
  {
    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      if(playerList[i].getId() == id)
      {
        return playerList[i].getName();
      }
    }
    return PLAYER_NAME_NOT_FOUND_NAME;
  }

  void StateMainPage::appendToTextChat(std::string& str)
  {
    //limit lenght textbox
    if(textChatLines>TEXT_CHAT_BOX_MAXIMUM_LINES)
    {
      textChat.setText("");//clear
      textChatLines=0;
    }

    textChatLines++;
    textChat.appendToText(str);
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
    if(!txt.empty() && txt != PLACE_HOLDER_TEXT_CHAT)
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

        if(sendChatButton.getButtonBound().contains(mousePosition))
        {
          sendChat(app);
        }
        else if(quitButton.getButtonBound().contains(mousePosition))
        {
          app.addSendText(REQUEST_DISCONNECT_FROM_LOBBY);
          app.close();
        }
        else if(chatInput.getInputBoxBound().contains(mousePosition))
        {
          inputFocus=&chatInput;
        }
        else if(lobbySettingsButton.getButtonBound().contains(mousePosition))
        {
          app.addSendText(REQUEST_GET_LOBBY_SETTINGS);
        }
        else if(pauseResumeGameButton.getButtonBound().contains(mousePosition))
        {
          app.addSendText(REQUEST_STOP_START_GAME);
        }
        else if(playerList[THIS_CLIENT_PLYARE_LOBBY_INDEX].voiceChatPB.getButtonBound().contains(mousePosition))
        {
          app.addSendText(REQUEST_ENABLE_DISABLE_VOICE_CHAT);
        }
        else
        {
          std::cout << "posx:" << mousePosition.x << "\tposy:" << mousePosition.y << std::endl;
        }

    }

    //keyboard
    switch(event.type)
    {
      case sf::Event::Closed:
      {
        app.addSendText(REQUEST_DISCONNECT_FROM_LOBBY);
        app.close();
      }break;

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
