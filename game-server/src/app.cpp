#include "../include/app.h"

namespace FluffyMultiplayer
{

  void sendData() //thread function
  {
    while(true)
    {
      // socketText.send(...)

    }
  }

  void receiveData() //thread function
  {
    while(true)
    {
      // unpackData(..receiveddata..);

    }
  }

  void App::init()
  {
    currentGameMode=nullptr;
    gameIsRunning=false;
    appIsRunning=true; //a flag close or continue app while loop

    threadSend = boost::thread(&FluffyMultiplayer::App::sendData, this);
    threadReceive = boost::thread(&FluffyMultiplayer::App::receiveData, this);

    log.init(LOG_FILE,PRINT_LOGS_LEVEL);

    switch (lobbyData.gameMode)
    {
      case 1:
        currentGameMode = new FluffyMultiplayer::GameModeMensch; break;
      default:
        currentGameMode = nullptr; break;
    }
  }

  std::vector<int> App::dataIndexes(const std::string& data, const std::string& delimiter) const
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


  std::vector<std::string> App::dataSeparator(const std::string& data, std::string delimiter, int startIndex=0)
  {
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


  std::string App::getPlayerUsernameById(const int& _id)
  {
    for(auto e: inLobbyPlayers)
    {
      if(e.id == _id)
        return e.name;
    }
    return "";
  }


  int App::getIndexPlayerInLobbyByAddress(const FluffyMultiplayer::AnAddress& ad) const
  {
    for(int i=0; i<inLobbyPlayers.size(); i++)
    {
      if(inLobbyPlayers[i].address == ad)
        return i;
    }
    return -1;
  }
  bool App::isPlayerIdExistsOnLobby(const int& id)
  {
    for(auto e: inLobbyPlayers)
      if(e.id == id)
        return true;
    return false;
  }

  int App::getSenderId(const FluffyMultiplayer::AnAddress& ad) const
  {
    int index=getIndexPlayerInLobbyByAddress(ad);
    if(index>=0)
    {
      int id=inLobbyPlayers[index].id;
      if(isPlayerIdExistsOnLobby(id))
        return id;
    }
    return -1;
  }

  bool App::doesItHavePermission(const FluffyMultiplayer::AnAddress& sender)
  {
    int id=getSenderId(currentItem.sender);
    if(id>=1)
      if(inLobbyPlayers[id].isAdmin || id == lobbyData.ownerId)
        return true;
    return false;
  }

  bool App::isIdBannedFromLobby(const int& id) const
  {
    for(auto e: inLobbyPlayers)
    {
      for(auto b: bannedPlayers)
        if(e.id == b.id)
          return true;
    }
    return false;
  }

  FluffyMultiplayer::AnAddress App::getPlayerAddressById(const int& id) const
  {
    FluffyMultiplayer::AnAddress result;
    for(auto e: inLobbyPlayers)
    {
      if(e.id == id)
        result = e.address;
    }
    return result; //i guess if not found will return an 0.0.0.0 with a random port
  }

  void App::processText()
  {
    FluffyMultiplayer::SocketReceiveData currentItem;
    std::string basic_query;

    for(int i=0; i<receivedTextDataList.size(); i++)
    {
      currentItem = receivedTextDataList.front();
      log.print("sender="+currentItem.sender.getAsString()+
          "received data="+receiveData, FluffyMultiplayer::LogType::Information);

      log.print("process currentItem.code="
            +std::to_string(currentItem.code)+";~;",
            FluffyMultiplayer::LogType::Information);



      //check connection blocked
      if(isConnectionBlocked(currentItem.sender))
      {
        sendTemp.set(RESPONSE_ERROR_CONNECTION_BLOCKED,currentItem.sender); //maybe later return blocked time to client
        sendTextDataList.push(sendTemp);
      }
      else if(!isConnectionExists(currentItem.sender))
      {
        /*
        have to process connect and reconenct dedicated
        because if leave it will check connection and these
        requests (are not exsits or ..) will drop
        */
        if(currentItem.code == REQUEST_CONNECT_TO_LOBBY)
        {
          //add to connected list
          if(connectPlayer(currentItem.sender))
          {
            sendTemp.set(RESPONSE_CONNECTION_ACCEPTED,currentItem.sender);
            sendTextDataList.push(sendTemp);
          }
          else
          {
            sendTemp.set(RESPONSE_INTERNAL_ERROR_FAILED_TO_CONNECT,currentItem.sender);
            sendTextDataList.push(sendTemp);
          }
        }
        else if(currentItem.code == REQUEST_RECONNECT_TO_LOBBY)
        {
          /*
          have to process connect and reconenct dedicated
          because if leave it will check connection and these
          requests (are not exsits or ..) will drop
          */

          //...
        }
        else
        {
          sendTemp.set(RESPONSE_ERROR_CONNECTION_NOT_EXISTS,currentItem.sender);
          sendTextDataList.push(sendTemp);
        }
      }
      else
      {
          //ok except two down casese other cases needs data to be seperate and decrypted
          if(currentItem.data.length()>MS_RECEIVED_DATA_MINIMUM_LENGTH)
            ds.decryptData(currentItem.data);

          if(ds.isSQLCodeIncluded(currentItem.data))
            ds.removeSQLCodeFromData(currentItem.data);


          /*note: in threadReceive (that function receiveData) will remove
            request code and those end delimiter and closers
            also on sendData (also thread) will add closer and delimtier at end of data if exists*/
          std::vector<std::string>cData = dataSeparator(currentItem.data, MS_DATA_DELIMITER);


          //connection is ok and process all requests except connect to lobby
          switch (currentItem.code)
          {
            case REQUEST_CONNECT_TO_LOBBY:
            {
              sendTemp.set(RESPONSE_ERROR_CONNECTION_EXISTS,currentItem.sender);
              sendTextDataList.push(sendTemp);
            }break;

            case REQUEST_RECONNECT_TO_LOBBY:
            {
              //that ip and port have not exists while player want reconnect
              sendTemp.set(RESPONSE_ERROR_CONNECTION_EXISTS,currentItem.sender);
              sendTextDataList.push(sendTemp);
            }break;



            case REQUEST_DISCONNECT_FROM_LOBBY:
            {
              //get detials of that sender (id, name)
              int cid = getSenderId(currentItem.sender);
              if(cid>=1)
              {
                //delete from database table fm_client_in_lobby
                db.queryStr = "DELETE FROM fm_client_in_lobby WHERE clientId='";
                db.queryStr+= std::to_string(cid) + "' AND lobbyId='";
                db.queryStr+= std::to_string(lobbyData.id) + "';";
                if(db.query_to_db())
                {
                  // remove from connectedPlayers and inLobbyPlayers and lobbySpecter if exists
                  if(disconnectPlayer(currentItem.sender))
                  {
                    std::string response = std::to_string(cid) + std::to_string(MS_DATA_DELIMITER);

                    //broadcast to lobby players
                    sendTemp.set(RESPONSE_PLAYER_DISCONNECTED,response,&inLobbyPlayers, nullptr);
                    sendTextDataList.push(sendTemp);

                    //broadcast to specters
                    if(lobbySpecters.size()>=1)
                    {
                      sendTemp.set(RESPONSE_PLAYER_DISCONNECTED,response,&lobbySpecters, nullptr);
                      sendTextDataList.push(sendTemp);
                    }
                  }
                  else //connection not found to disconnect
                  {
                    sendTemp.set(RESPONSE_ERROR_DISCONNECT_YOU_ARE_NOT_CONNECTED,response,&lobbySpecters, nullptr);
                    sendTextDataList.push(sendTemp);
                  }
                }
                else
                {
                  sendTemp.set(RESPONSE_INTERNAL_ERROR_FAILED_TO_DISCONNECT,currentItem.sender);
                  sendTextDataList.push(sendTemp);
                }
              }
            }break;


            case REQUEST_JOIN_TO_LOBBY: // player will send cData = [0]->(identity), [1]->(password)
            {
                if(cData[1] == lobbyData.password)
                {
                  if(ds.isIdentityValid(currentItem.data))
                  {
                    //get client info by identity
                    db.queryStr="SELECT clientId FROM fm_client_login WHERE identity='";
                    db.queryStr+= cData[0] + "';";
                    int cId = stringToInt(db.search_in_db(db.queryStr,true));
                    if(cId>=1) //is client exsits?
                    {
                      //check for ban by id
                      if(isIdBannedFromLobby(tempPlayer.id))
                      {
                        sendTemp.set(RESPONSE_ERROR_JOIN_LOBBY_YOU_ARE_BANNED,currentItem.sender);
                        sendTextDataList.push(sendTemp);
                      }
                      else
                      {
                        //try to add client into lobby.
                        db.queryStr="INSERT OR REPLACE INTO fm_client_in_lobby (clientId,lobbyId) VALUES('";
                        db.queryStr+= std::to_string(cId) + "', '";
                        db.queryStr+= std::to_string(lobbyData.id) + "';";
                        if(db.query_to_db())
                        {
                          //increase currentplayers
                          lobbyData.currentPlayers++;

                          //get client info
                          db.queryStr="SELECT username FROM fm_client WHERE id='";
                          db.queryStr+= std::to_string(cId) + "';";
                          std::string cUsername = db.search_in_db(db.queryStr,true);

                          db.queryStr="SELECT isAdmin FROM fm_client WHERE id='";
                          db.queryStr+= std::to_string(cId) + "';";
                          bool cIsAdmin = stringToBool(db.search_in_db(db.queryStr,true));

                          //add to inLobbyPlayers
                          tempPlayer.set(cId,cData[0],currentItem.sender,cUsername,cIsAdmin);
                          inLobbyPlayers.push(tempPlayer);

                          //tell sender his id
                          sendTemp.set(RESPONSE_YOU_ARE_JOINT_INTO_LOBBY,"joint into lobby and your data is =.. + lobbyData + lobbyPlayers + ...",currentItem.sender);
                          sendTextDataList.push(sendTemp);

                          //broadcast to in lobby client joint
                          sendTemp.set(RESPONSE_PLAYER_JOINT_INTO_LOBBY,"player joint in lobby his info=..",&inLobbyPlayers,nullptr);
                          sendTextDataList.push(sendTemp);

                          //broadcast to speceter
                          if(lobbySpecters.size()>=1)
                          {
                            sendTemp.set(RESPONSE_PLAYER_JOINT_INTO_LOBBY,"player joint in lobby his info=..",&lobbySpecters,nullptr);
                            sendTextDataList.push(sendTemp);
                          }

                        }
                        else
                        {
                          //faield to join lobby maybe client is already in lobby or have some databse insert issue
                          // RESPONSE_ERROR_JOIN_LOBBY_YOU_ARE_ALREADY_JOINT -> because of using INSERT OR REPLACE INTO this problem solved for many cases
                          sendTemp.set(RESPONSE_INTERNAL_ERROR_FAILED_TO_JOIN_INTO_LOBBY,currentItem.sender);
                          sendTextDataList.push(sendTemp);
                        }
                      }

                    }
                    else
                    {
                      //id is <=0 so invalid. player not found -> invalid identity
                      sendTemp.set(RESPONSE_ERROR_JOIN_LOBBY_INVALID_IDENTITY,currentItem.sender);
                      sendTextDataList.push(sendTemp);
                    }
                  }
                  else
                  {
                    log.print("join to lobby: invalid identity. data="+currentItem.data, FluffyMultiplayer::LogType::Information);
                    sendTemp.set(RESPONSE_ERROR_JOIN_LOBBY_INVALID_IDENTITY,currentItem.sender);
                    sendTextDataList.push(sendTemp);
                  }
                }
                else //incorrect password
                {
                  sendTemp.set(RESPONSE_ERROR_JOIN_LOBBY_PASSWORD_INCORRECT,currentItem.sender);
                  sendTextDataList.push(sendTemp);
                }

            }break;

            case REQUEST_GET_LOBBY_SETTINGS:
            {
              if(doesItHavePermission(currentItem.sender))
                sendTemp.set(RESPONSE_LOBBY_SETTINGS_IS,lobbyData.getAsStringForOwner(),currentItem.sender);
              else
                sendTemp.set(RESPONSE_ERROR_GET_LOBBY_SETTINGS_NO_PERMISSION,currentItem.sender);

              sendTextDataList.push(sendTemp);
            }break;

            case REQUEST_UPDATE_LOBBY_SETTINGS:
            /*
                client will send: [0]->(maxPlayers), [1]->gameMode,
                                  [2]->currentPlayers, [3]->isVoiceChatForbidden
                                  [4]->isTextChatForbidden, [5]->isSpecterForbidden,
                                  [6]->password, [7]->ownerId
            */
            {
              if(doesItHavePermission(currentItem.sender))
              {
                //apply received changes into lobby
                jiogjotrjhiotrjiohjtrhjitrjhiotrj//........................................................................



                //broadcast lobby setting changes to in lobby
                sendTemp.set(RESPONSE_LOBBY_SETTINGS_UPDATED,lobbyData.getAsStringForPlayers(),&inLobbyPlayers,nullptr);
                sendTextDataList.push(sendTemp);

                //broadcast lobby setting changes to specters
                if(lobbySpecters.size()>=1)
                {
                  sendTemp.set(RESPONSE_LOBBY_SETTINGS_UPDATED,lobbyData.getAsStringForPlayers(),&lobbySpecters,nullptr);
                  sendTextDataList.push(sendTemp);
                }

              }
              else
              {
                sendTemp.set(RESPONSE_ERROR_UPDATE_LOBBY_SETTINGS_NO_PERMISSION,currentItem.sender);
                sendTextDataList.push(sendTemp);
              }

            }break;

            case REQUEST_START_GAME:
            {
              if(doesItHavePermission(currentItem.sender))
              {
                if(gameIsRunning)
                {
                  sendTemp.set(RESPONSE_ERROR_START_GAME_ALREADY_RUN,currentItem.sender);
                  sendTextDataList.push(sendTemp);
                }
                else
                {
                  if(startGame())
                  {
                    sendTemp.set(RESPONSE_GAME_STARTED,&inLobbyPlayers,nullptr);
                    sendTextDataList.push(sendTemp);
                  }
                  else
                  {
                    sendTemp.set(RESPONSE_INTERNAL_ERROR_FAILED_TO_START_GAME,currentItem.sender);
                    sendTextDataList.push(sendTemp);
                  }
                }
              }
              else
              {
                sendTemp.set(RESPONSE_ERROR_START_GAME_NO_PERMISSION,currentItem.sender);
                sendTextDataList.push(sendTemp);
              }
            }break;

            case REQUEST_STOP_GAME:
            {
              if(doesItHavePermission(currentItem.sender))
              {
                if(!gameIsRunning)
                {
                  sendTemp.set(RESPONSE_ERROR_STOP_GAME_NOT_STARTED,currentItem.sender);
                  sendTextDataList.push(sendTemp);
                }
                else
                {
                  if(stopGame())
                  {
                    sendTemp.set(RESPONSE_GAME_STOPPED,&inLobbyPlayers,nullptr);
                    sendTextDataList.push(sendTemp);
                  }
                  else
                  {
                    sendTemp.set(RESPONSE_INTERNAL_ERROR_FAILED_TO_STOP_GAME,currentItem.sender);
                    sendTextDataList.push(sendTemp);
                  }
                }
              }
              else
              {
                sendTemp.set(RESPONSE_ERROR_STOP_GAME_NO_PERMISSION,currentItem.sender);
                sendTextDataList.push(sendTemp);
              }
            }break;

            case REQUEST_DELETE_LOBBY:
            {
              if(doesItHavePermission(currentItem.sender))
              {
                //delete lobby from fm_lobby (automatically will remove all players from lobby fm_client_in_lobby)
                db.queryStr = "DELETE FROM fm_lobby WHERE id='";
                db.queryStr+= std::to_string(lobbyData.id) + "';";
                if(db.query_to_db())
                {
                  //tell inLobbyPlayers lobby is deleted.
                  sendTemp.set(RESPONSE_LOBBY_DELETED,&inLobbyPlayers,nullptr);
                  sendTextDataList.push(sendTemp);

                  //tell lobbySpecters lobby is deleted.
                  sendTemp.set(RESPONSE_LOBBY_DELETED,&lobbySpecters,nullptr);
                  sendTextDataList.push(sendTemp);

                  //close server application
                  log.print("lobby deleted. lobbyId="+std::to_string(lobbyData.id), FluffyMultiplayer::LogType::Information);
                  appIsRunning=false;
                }
                else
                {
                  sendTemp.set(RESPONSE_INTERNAL_ERROR_FAILED_TO_DELETE_LOBBY,currentItem.sender);
                  sendTextDataList.push(sendTemp);
                }
              }
              else
              {
                sendTemp.set(RESPONSE_ERROR_DELETE_LOBBY_NO_PERMISSION,currentItem.sender);
                sendTextDataList.push(sendTemp);
              }
            }break;

            case REQUEST_KICK_PLAYER: //client will send:  [0](targetId)
            {
              if(doesItHavePermission(currentItem.sender))
              {
                int targetId=stringToInt(cData[0]);
                if(isPlayerIdExistsOnLobby(targetId))
                {
                  //remove from database fm_client_in_lobby
                  db.queryStr = "DELETE FROM fm_client_in_lobby WHERE clientId='";
                  db.queryStr+= std::to_string(targetId) + "' AND lobbyId='";
                  db.queryStr+= std::to_string(lobbyData.id) + "';";
                  if(db.query_to_db())
                  {
                    lobbyData.currentPlayers--;
                    log.print("player ("+std::to_string(targetId)+
                              ") has been kicked from lobby ("+std::to_string(lobbyData.id)+")",
                              FluffyMultiplayer::LogType::Information);

                    std::string response = std::to_string(targetId) + std::to_string(MS_DATA_DELIMITER);

                    //broadcast to inLobbyPlayers, player has been kicked from lobby
                    sendTemp.set(RESPONSE_PLAYER_KICKED_FROM_LOBBY,response,&inLobbyPlayers,nullptr);
                    sendTextDataList.push(sendTemp);

                    //broadcast to specters, player has been kicked from lobby
                    if(lobbySpecters.size()>=1)
                    {
                      sendTemp.set(RESPONSE_PLAYER_KICKED_FROM_LOBBY,response,&lobbySpecters,nullptr);
                      sendTextDataList.push(sendTemp);
                    }

                    //this line written blow of those, because we want to tell all (speacilly that target to you are kicked if put this line up would not send to targetId)
                    disconnectPlayer(getPlayerAddressById(targetId));
                  }
                  else
                  {
                    sendTemp.set(RESPONSE_INTERNAL_ERROR_FAILED_TO_KICK_PLAYER,currentItem.sender);
                    sendTextDataList.push(sendTemp);
                  }
                }
                else
                {
                  sendTemp.set(RESPONSE_ERROR_KICK_PLAYER_INVALID_TARGET,currentItem.sender);
                  sendTextDataList.push(sendTemp);
                }
              }
              else
              {
                sendTemp.set(RESPONSE_ERROR_KICK_PLAYER_NO_PERMISSION,currentItem.sender);
                sendTextDataList.push(sendTemp);
              }
            }break;

            case REQUEST_BAN_PLAYER: //client will send (targetId, reason, time-duration)   NOTE time is int (time per second)
            {
              if(doesItHavePermission(currentItem.sender))
              {
                int targetId=stringToInt(cData[0]);
                if(isPlayerIdExistsOnLobby(targetId))
                {
                  //remove from database fm_client_in_lobby
                  db.queryStr = "DELETE FROM fm_client_in_lobby WHERE clientId='";
                  db.queryStr+= std::to_string(targetId) + "' AND lobbyId='";
                  db.queryStr+= std::to_string(lobbyData.id) + "';";
                  if(db.query_to_db())
                  {
                    lobbyData.currentPlayers--;
                    log.print("player ("+std::to_string(targetId)+
                              ") has been banned from lobby ("+std::to_string(lobbyData.id)+") "+
                              "reason:("+cData[1]+") for banTime:("+cData[2]+")seconds",
                              FluffyMultiplayer::LogType::Information);

                    FluffyMultiplayer::BanList targetAsBan
                    {
                      targetId, getPlayerAddressById(targetId),
                      FluffyMultiplayer::TimeAndDate::now(), convertStringToInt(cData[2])
                    };
                    bannedPlayers.push(targetAsBan);

                    std::string response = std::to_string(targetId) + std::to_string(MS_DATA_DELIMITER); //later can write reason and ban time to tell other clients

                    //broadcast to inLobbyPlayers, player has been kicked from lobby
                    sendTemp.set(RESPONSE_PLAYER_BANNED_FROM_LOBBY,response,&inLobbyPlayers,nullptr);
                    sendTextDataList.push(sendTemp);

                    //broadcast to specters, player has been kicked from lobby
                    if(lobbySpecters.size()>=1)
                    {
                      sendTemp.set(RESPONSE_PLAYER_BANNED_FROM_LOBBY,response,&lobbySpecters,nullptr);
                      sendTextDataList.push(sendTemp);
                    }

                    //this line written blow of those, because we want to tell all (speacilly that target to you are banned if put this line up would not send to targetId)
                    disconnectPlayer(getPlayerAddressById(targetId));
                }
                else
                {
                  sendTemp.set(RESPONSE_ERROR_BAN_PLAYER_INVALID_TARGET,currentItem.sender);
                  sendTextDataList.push(sendTemp);
                }
              }
              else
              {
                sendTemp.set(RESPONSE_ERROR_BAN_PLAYER_NO_PERMISSION,currentItem.sender);
                sendTextDataList.push(sendTemp);
              }
            }
            }break;

            case REQUEST_TRANSFER_LOBBY_OWNERSHIP: //client will send (targetId)
            {

            }break;

            case REQUEST_SEND_TEXT_CHAT: //client will send: [0]->(messageText)
            {
              if(lobbyData.isTextChatForbidden)
              {
                sendTemp.set(RESPONSE_ERROR_SEND_TEXT_CHAT_DISABLED,currentItem.sender);
                sendTextDataList.push(sendTemp);
              }
              else
              {
                  std::string response = getPlayerUsernameById(getSenderId(currentItem.sender)) +
                                              ": " + cData[0] + "\n";

                  //broadcast  new text message.. to inLobbyPlayers
                  sendTemp.set(REQUEST_SEND_TEXT_CHAT,response,&inLobbyPlayers,nullptr);
                  sendTextDataList.push(sendTemp);

                  //broadcast new text message.. to specters
                  if(lobbySpecters.size()>=1 && SEND_TEXT_CHAT_TO_SPECTERS)
                  {
                    sendTemp.set(REQUEST_SEND_TEXT_CHAT,response,&lobbySpecters,nullptr);
                    sendTextDataList.push(sendTemp);
                  }
              }
            }break;

            //case REQUEST_SEND_VOICE_CHAT: moved into processVoice()

            case REQUEST_ENABLE_VOICE_CHAT:
            {

            }break;

            case REQUEST_DISABLE_VOICE_CHAT:
            {

            }break;

            default:
            {
              if(gameIsRunning)
              {
                if(currentGameMode!=nullptr)
                {
                  log.print("unknown request code lets passing it to gamemode", FluffyMultiplayer::LogType::Information);
                  currentGameMode = currentGameMode->process(currentItem,sendTemp,sendTextDataList);
                  //response to client will push by currentGameMode->process
                }
                else
                {
                  log.print("unknown request code and gamemode is nullptr (game is not started)", FluffyMultiplayer::LogType::Warning);
                  sendTemp.set(RESPONSE_UNKNOWN_REQUEST_GAME_IS_NOT_STARTED,currentItem.sender);
                  sendTextDataList.push(sendTemp);
                }

              }
              else
              {
                log.print("unknown request code and game running = false (not started or paused)", FluffyMultiplayer::LogType::Warning);
                sendTemp.set(RESPONSE_UNKNOWN_REQUESST_GAME_PAUSED_OR_NOT_STARTED,currentItem.sender);
                sendTextDataList.push(sendTemp);
              }
            }

          }

      }
    }


    //remove processed element
    receivedTextDataList.pop();
  }

  void processVoice()
  {
    // case REQUEST_SEND_VOICE_CHAT:
    // {

    // }break;
  }
  FluffyMultiplayer::GameMode* App::process()
  {
    //process text requests
    processText();

    //process voice requests
    processVoice();

    return this;
  }


  bool addPlayerToVoiceChat(); //enalbe his voiceChat
  bool removePlayerFromVoiceChat(); //disable his voiceChat


  void App::run()
  {
    while(appIsRunning)
    {
      currentGameMode = process();
    }
  }

  bool App::isConnectionExists(const FluffyMultiplayer::AnAddress& address)
  {
    for(FluffyMultiplayer::AnAddress e : connectedPlayers.address)
    {
      if(e == address)
        return true;
    }
    return false;
  }


  //convert
  FluffyMultiplayer::TimeAndDate App::stringToTime(const std::string& time)
  {
      std::tm tm = {};
      strptime(time.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
      return FluffyMultiplayer::TimeAndDate {1900 + tm.tm_year, 1 + tm.tm_mon,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec};
  }

  FluffyMultiplayer::Player App::stringToPlayer(const std::string&);
  FluffyMultiplayer::LobbyData App::stringToLobbyData(const std::string&);
  FluffyMultiplayer::AnAddress App::stringToAnAddress(const std::string&);
  int App::stringToInt(const std::string&);
  bool App::stringToBool(const std::string&);


  //player
  bool App::connectPlayer(FluffyMultiplayer::Player& p)
  {
    connectedPlayers.push(p);
    log.print("id(" + p.id + ") name(" + p.name + ") ip(" + p.address.getAsString() + ") "
      + "connected to the lobby.", FluffyMultiplayer::LogType::Information);
  }
  bool App::disconnectPlayer(FluffyMultiplayer::AnAddress& ad)
  {
    int currentPlayersBefore = lobbyData.currentPlayers;
    //remove from connectedPlayers
    std::queue<FluffyMultiplayer::AnAddress> _connectedPlayers;
    for(auto e: connectedPlayers)
    {
      if(e == ad)
        lobbyData.currentPlayers--;
      else
        _connectedPlayers.push(e);
    }
    connectedPlayers = _connectedPlayers;

    //check if that connection does not exists on connectedPlayers skip other commands
    if(currentPlayersBefore == currentPlayersBefore)
    {
      log.print("disconnect player failed, Currentplayers are still same old value.", FluffyMultiplayer::LogType::Warning);
      return false; //could not remove there is no connection exists
    }


    //remove from inLobbyPlayers
    std::queue<FluffyMultiplayer::Player> _inLobbyPlayers;
    for(auto e: inLobbyPlayers)
    {
      if(e.address == ad)
        continue;
      else
        _inLobbyPlayers.push(e);
    }
    inLobbyPlayers = _inLobbyPlayers;


    //remove from lobbySpecters
    std::queue<FluffyMultiplayer::Player> _lobbySpecters;
    for(auto e: lobbySpecters)
    {
      if(e.address == ad)
        continue;
      else
        _lobbySpecters.push(e);
    }
    lobbySpecters = _lobbySpecters;

    return true;
  }

  bool App::reconnectPlayer(FluffyMultiplayer::Player&);
  bool App::checkEnteredPassword(const std::string& password)
  {
    if(lobby.password == password)
      return true;
    return false;
  }

  bool App::textChat(const std::string& text)
  {

  }

  bool App::voiceChat(const std::string&);
  bool App::kickPlayer(FluffyMultiplayer::Player&, const std::string& reason);
  bool App::banPlayer(FluffyMultiplayer::Player&, const std::string& reason, FluffyMultiplayer::TimeAndDate duration);
  bool App::playerAsSpecter(FluffyMultiplayer::Player&);

  //lobby
  bool App::transferLobbyOwnerShip(FluffyMultiplayer::Player& newOwner);
  std::string App::getLobbySettings();
  bool App::updateLobby(FluffyMultiplayer::LobbyData);
  std::string App::lobbyInfo(); //will report lobby players and details for first time to connected player
  bool App::startGame()
  {
    gameIsRunning=true;
    db.queryStr="UPDATE fm_lobby SET lobbyStatusInGame='1' WHERE id='";
    db.queryStr+= std::to_string(lobbyData.id) + "';";
    if(db.query_to_db())
      return true;
    return false;
  }
  bool App::stopGame()
  {
    gameIsRunning=false;
    db.queryStr="UPDATE fm_lobby SET lobbyStatusInGame='0' WHERE id='";
    db.queryStr+= std::to_string(lobbyData.id) + "';";
    if(db.query_to_db())
      return true;
    return false;
  }

  bool App::deleteLobby();
}
