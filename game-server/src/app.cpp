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


  FluffyMultiplayer::GameMode* App::processText()
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
        sendTemp.set(RESPONSE_ERROR_CONNECTION_BLOCKED,"",currentItem.sender); //maybe later return blocked time to client
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
            sendTemp.set(RESPONSE_CONNECTION_ACCEPTED,"",currentItem.sender);
            sendTextDataList.push(sendTemp);
          }
          else
          {
            sendTemp.set(RESPONSE_INTERNAL_ERROR_FAILED_TO_CONNECT,"",currentItem.sender);
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
          sendTemp.set(RESPONSE_ERROR_CONNECTION_NOT_EXISTS,"",currentItem.sender);
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
              sendTemp.set(RESPONSE_ERROR_CONNECTION_EXISTS,"",currentItem.sender);
              sendTextDataList.push(sendTemp);
            }break;

            case REQUEST_RECONNECT_TO_LOBBY:
            {
              //that ip and port have not exists while player want reconnect
              sendTemp.set(RESPONSE_ERROR_CONNECTION_EXISTS,"",currentItem.sender);
              sendTextDataList.push(sendTemp);
            }break;



            case REQUEST_DISCONNECT_FROM_LOBBY:
            {
              //get detials of that sender (id, name)


              //delete from database table fm_client_in_lobby

              // remove from connectedPlayers and inLobbyPlayers if exists

              //broadcast to lobby players
              sendTemp.set(RESPONSE_PLAYER_DISCONNECTED,"player (x) disconnected",&inLobbyPlayers, nullptr);
              sendTextDataList.push(sendTemp);

              //broadcast to specters
              if(lobbySpecters.size()>=1)
              {
                sendTemp.set(RESPONSE_PLAYER_DISCONNECTED,"player (x) disconnected",&lobbySpecters, nullptr);
                sendTextDataList.push(sendTemp);
              }
            }break;

            case REQUEST_JOIN_TO_LOBBY: // player will send cData = [0]->(identity), [1]->(password)
            {
                if(ds.isIdentityValid(currentItem.data))
                {
                  //get client info by identity
                  dbQueryStr="SELECT clientId FROM fm_client_login WHERE identity='";
                  dbQueryStr+= cData[0] + "';";
                  int cId = stringToInt(db.search_in_db(dbQueryStr,true));
                  if(cId>=1) //is client exsits?
                  {
                    //check for ban by id
                    if(isIdBannedFromLobby(tempPlayer.id))
                    {
                      sendTemp.set(RESPONSE_ERROR_JOIN_LOBBY_YOU_ARE_BANNED,"",currentItem.sender);
                      sendTextDataList.push(sendTemp);
                    }
                    else
                    {
                      //try to add client into lobby.
                      dbQueryStr="INSERT OR REPLACE INTO fm_client_in_lobby (clientId,lobbyId) VALUES('";
                      dbQueryStr+= std::to_string(cId) + "', '";
                      dbQueryStr+= std::to_string(lobbyData.id) + "';";
                      if(db.query_to_db(dbQueryStr))
                      {
                        //get client info
                        dbQueryStr="SELECT username FROM fm_client WHERE id='";
                        dbQueryStr+= std::to_string(cId) + "';";
                        std::string cUsername = db.search_in_db(dbQueryStr,true);

                        dbQueryStr="SELECT isAdmin FROM fm_client WHERE id='";
                        dbQueryStr+= std::to_string(cId) + "';";
                        bool cIsAdmin = stringToBool(db.search_in_db(dbQueryStr,true));

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
                        sendTemp.set(RESPONSE_INTERNAL_ERROR_FAILED_TO_JOIN_INTO_LOBBY,"",currentItem.sender);
                        sendTextDataList.push(sendTemp);
                      }
                    }

                  }
                  else
                  {
                    //id is <=0 so invalid. player not found -> invalid identity
                    sendTemp.set(RESPONSE_ERROR_JOIN_LOBBY_INVALID_IDENTITY,"",currentItem.sender);
                    sendTextDataList.push(sendTemp);
                  }
                }
                else
                {
                  log.print("join to lobby: invalid identity. data="+currentItem.data, FluffyMultiplayer::LogType::Information);
                  sendTemp.set(RESPONSE_ERROR_JOIN_LOBBY_INVALID_IDENTITY,"",currentItem.sender);
                  sendTextDataList.push(sendTemp);
                }

            }break;

            case REQUEST_GET_LOBBY_SETTINGS:
            {

            }break;

            case REQUEST_UPDATE_LOBBY_SETTINGS: //client will send (?)
            {

            }break;

            case REQUEST_START_GAME:
            {

            }break;

            case REQUEST_STOP_GAME:
            {

            }break;

            case REQUEST_DELETE_LOBBY:
            {

            }break;

            case REQUEST_KICK_PLAYER: //client will send (?)
            {

            }break;

            case REQUEST_BAN_PLAYER: //client will send (?)
            {

            }break;

            case REQUEST_TRANSFER_LOBBY_OWNERSHIP: //client will send (?)
            {

            }break;

            case REQUEST_SEND_TEXT_CHAT: //client will send (messageText)
            {

            }break;

            // case REQUEST_SEND_VOICE_CHAT:
            // {

            // }break;

            case REQUEST_ENABLE_VOICE_CHAT:
            {

            }break;

            case REQUEST_DISABLE_VOICE_CHAT:
            {

            }break;

            default:
            {
              if(currentGameMode!=nullptr)
              {
                log.print("unknown request code passing it to gamemode", FluffyMultiplayer::LogType::Information);
                currentGameMode = currentGameMode->process(currentItem);
              }
              else
                log.print("unknown request code and gamemode is nullptr", FluffyMultiplayer::LogType::Warning);
            }

          }

      }
    }


    //remove processed element
    receivedTextDataList.pop();
  }


  FluffyMultiplayer::GameMode* processText()
  {

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
    while(true)
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
    socketText.broadcast
    (
        FluffyMultiplayer::SocketSendData
        {
          PLAYER_CONNECTED,
          "id(" + p.id + ") name(" + p.name + ") ip(" + p.address.getAsString() + ")",
          &connectedPlayers,
          nullptr
        }
    );
  }
  bool App::disconnectPlayer(FluffyMultiplayer::Player&)
  {

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
  bool App::startGame();
  bool App::stopGame();
  bool App::deleteLobby();
}
