#include "../include/app.h"
#include "../include/gameMode.h"
#include "../include/gameModes/gameMode-mensch.h"

namespace FluffyMultiplayer
{

  void App::sendData()
  {
    FluffyMultiplayer::SocketSendData currentItem;
    try
    {

      {//lock and unlock mutex for send Text (in this case dont wait for whole function ends to unlock)
        //lock mutex for socket to avoid segment fault or data corruption.
        boost::lock_guard<boost::mutex> lock(sendTextDataListMutex);

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



      {//lock and unlock mutex for send voice (in this case dont wait for whole function ends to unlock)
        //voice data

        boost::lock_guard<boost::mutex> lock(sendVoiceDataListMutex);

        if(sendVoiceDataList.size()>=1) //on that socket self will check socketStatus before send
        {
          currentItem = sendVoiceDataList.front();
          ds.encryptData(currentItem.data);

          socketVoice->send(currentItem);

          //remove proccessed element
          sendVoiceDataList.pop();
        }
      }

    }
    catch (std::exception& e)
    {
      std::string errorMsg = e.what();
      log.print("from App::sendData catched exception: "+errorMsg, FluffyMultiplayer::LogType::Warning);
    }
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
    log.print("prepareData code="+std::to_string(currentItem.code)+" data="+currentItem.data, FluffyMultiplayer::LogType::Information);
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
        char receive_data[MC_RECEIVE_BUFFER_TEXT];
        receive_length = socketText->receive(receive_data,senderEndpoint);
        currentItem.sender.setFromEndpoint(senderEndpoint);

        if(receive_length >=1)
        {
          currentItem.data = std::string(receive_data,receive_length);
          ds.decryptData(currentItem.data);

          if(ds.isSQLCodeIncluded(currentItem.data))
            ds.removeSQLCodeFromData(currentItem.data);


          //sperate c.code and data and remove code and closers from .data
          prepareData(currentItem);

          if(currentItem.code>=MC_MINUMUM_RESPONSE_CODE)
          {
            log.print("received text from="+currentItem.sender.getAsString()+
                  "\tcode="+std::to_string(currentItem.code)+"\tdata="+currentItem.data,
                  FluffyMultiplayer::LogType::Information);

            receivedTextDataList.push(currentItem);
            log.print("receivedTextDataList.size after push="+std::to_string(receivedTextDataList.size()), FluffyMultiplayer::LogType::Information);
            processText();
          }
        }

        //socket voice receive
        {
          if(!lobbyData.isVoiceChatForbidden)
          {
            char receive_data[MC_RECEIVE_BUFFER_VOICE];
            receive_length = socketVoice->receive(receive_data,senderEndpoint);
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

                log.print("received voice from="+currentItem.sender.getAsString()+
                        "\tcode="+std::to_string(currentItem.code)+"\tdata="+
                          currentItem.data, FluffyMultiplayer::LogType::Information);

                receivedVoiceDataList.push(currentItem);
                processVoice();
              }
            }
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


  void App::safePushToList(bool isVoiceData)
  {
    if(isVoiceData)
    {
      boost::lock_guard<boost::mutex> lock(sendVoiceDataListMutex);
      sendTextDataList.push(sendTemp);
    }
    else
    {
      boost::lock_guard<boost::mutex> lock(sendTextDataListMutex);
      sendTextDataList.push(sendTemp);
    }

    //call that method to check send lists then use socket to send data,
    sendData();
  }


  void App::response(int code,
                FluffyMultiplayer::AnAddress receiver,
                bool isVoiceData=false)
  {
    sendTemp.set(code,receiver);
    safePushToList(isVoiceData);
  }

  void App::response(int code, std::string data,
                FluffyMultiplayer::AnAddress receiver,
                bool isVoiceData=false)
  {
    sendTemp.set(code,data,receiver);
    safePushToList(isVoiceData);
  }

  void App::response(int code,
                const std::vector<FluffyMultiplayer::Player>* receivers,
                const std::vector<FluffyMultiplayer::Player>* except,
                bool isVoiceData=false)
  {
    sendTemp.set(code,receivers,except);
    safePushToList(isVoiceData);
  }

  void App::response(int code, std::string data,
                      const std::vector<FluffyMultiplayer::Player>* receivers,
                      const std::vector<FluffyMultiplayer::Player>* except,
                      bool isVoiceData=false)
  {
    sendTemp.set(code,data,receivers,except);
    safePushToList(isVoiceData);
  }


  App::App()
  {

  }

  App::~App()
  {
    log.close();
    db.close();
  }

  void App::init(FluffyMultiplayer::LobbyData _lobby)
  {
    //because of non-blocking turned-on on socket this ip will receive after each second so better way is to ignore so now we just block that
    blockedAddresses.push_back({"0.0.0.0",0});

    lobbyData = _lobby;
    log.print("currentplayers="+std::to_string(lobbyData.currentPlayers), FluffyMultiplayer::LogType::Information);

    currentGameMode=nullptr;
    gameIsRunning=false;
    appIsRunning=true; //a flag close or continue app while loop

    threadReceive = boost::thread(&FluffyMultiplayer::App::receiveData, this);

    socketText = new FluffyMultiplayer::UdpSocket(io_context_text, _lobby.textPort, MC_RECEIVE_BUFFER_TEXT);
    socketVoice = new FluffyMultiplayer::UdpSocket(io_context_voice, _lobby.voicePort, MC_RECEIVE_BUFFER_VOICE);

    //here we can not make condition to check isTextChatForbidden becuase we using this socket also to send application/game data, beside textchat
    socketText->enable();

    if(!lobbyData.isVoiceChatForbidden)
      socketVoice->enable();

    log.init(LOG_FILE,PRINT_LOGS_LEVEL);
    db.init(DATABASE_FILENAME);

    changeGameMode();
  }

  void App::changeGameMode()
  {
    log.print("selected gameMode code:"+std::to_string(lobbyData.gameMode), FluffyMultiplayer::LogType::Information);
    switch (lobbyData.gameMode)
    {
      case GAME_MODE_MENSCH_ID:
      {
        log.print("selected gameMode is Mensch", FluffyMultiplayer::LogType::Information);
        currentGameMode = new FluffyMultiplayer::GameModeMensch((*this));
      }break;

      default:
      {
        log.print("unknown lobby gameMode... gm-code="+std::to_string(lobbyData.gameMode),
                  FluffyMultiplayer::LogType::Warning);
        currentGameMode = nullptr;
      }break;
    }
  }

  bool App::isConnectionBlocked(const FluffyMultiplayer::AnAddress& address) const
  {
    for(auto e: blockedAddresses)
      if(e == address)
        return true;
    return false;
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
    log.print("dataSeparator.data="+data,FluffyMultiplayer::LogType::Information);
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

  std::string App::getPlayerUsernameById(const int& _id) const
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
  bool App::isPlayerIdExistsOnLobby(const int& id) const
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
    int index=getIndexPlayerInLobbyByAddress(sender);
    if(inLobbyPlayers[index].isAdmin || inLobbyPlayers[index].id == lobbyData.ownerId)
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



  void App::updatePlayerVoiceChatStatus(const int& index, bool status)
  {
    inLobbyPlayers[index].voiceChatEnable=status;
  }

  bool App::isPlayerOwner(int pid)
  {
    if(pid == lobbyData.ownerId)
      return true;
    return false;
  }

  void App::processText()
  {
    FluffyMultiplayer::SocketReceiveData currentItem;
    log.print("[text] receivedTextDataList.size()="+std::to_string(receivedTextDataList.size()), FluffyMultiplayer::LogType::Information);


    for(int i=0; i<receivedTextDataList.size(); i++)
    {
      // log.print("[text] current item = code="+std::to_string(currentItem.code) +"\tdata=" + currentItem.data, FluffyMultiplayer::LogType::Information);
      currentItem = receivedTextDataList.front();

      //check connection blocked
      if(isConnectionBlocked(currentItem.sender))
      {
        // log.print("[text] connection is blocked.",FluffyMultiplayer::LogType::Information);
        // response(RESPONSE_ERROR_CONNECTION_BLOCKED,currentItem.sender, false); //maybe later return blocked time to client
      }
      else if(!isConnectionExists(currentItem.sender))
      {
        log.print("[text] size="+std::to_string(receivedTextDataList.size()), FluffyMultiplayer::LogType::Information);
        log.print("[text] sender="+currentItem.sender.getAsString()+
                    "received data="+currentItem.data, FluffyMultiplayer::LogType::Information);

        log.print("process currentItem.code="
              +std::to_string(currentItem.code)+";~;",
              FluffyMultiplayer::LogType::Information);



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
            response(RESPONSE_CONNECTION_ACCEPTED, currentItem.sender, false);
          }
          else
          {
            response(RESPONSE_INTERNAL_ERROR_FAILED_TO_CONNECT, currentItem.sender, false);
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
          response(RESPONSE_ERROR_CONNECTION_NOT_EXISTS,currentItem.sender, false);
        }
      }
      else
      {
          /*note: in threadReceive (that function receiveData) will remove
            request code and those end delimiter and closers
            also on sendData (also thread) will add closer and delimtier at end of data if exists*/
          std::vector<std::string>cData = dataSeparator(currentItem.data, MS_DATA_DELIMITER);
          log.print("[text process] cData:", FluffyMultiplayer::LogType::Information);
          for(int i=0; i<cData.size(); i++)
          {
            log.print("[text process] cData["+std::to_string(i)+"]:"+cData[i], FluffyMultiplayer::LogType::Information);
          }


          //connection is ok and process all requests except connect to lobby
          switch (currentItem.code)
          {
            case REQUEST_CONNECT_TO_LOBBY:
            {
              log.print("[text] REQUEST_CONNECT_TO_LOBBY", FluffyMultiplayer::LogType::Information);
              response(RESPONSE_ERROR_CONNECTION_EXISTS,currentItem.sender, false);
            }break;

            case REQUEST_RECONNECT_TO_LOBBY:
            {
              //that ip and port have not exists while player want reconnect
              response(RESPONSE_ERROR_CONNECTION_EXISTS,currentItem.sender, false);
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

                  //get owner status before disocnnect player, maybe after disconnect player that player not found and owner status miss.
                  bool isThatPlayerOwner = isPlayerOwner(cid);


                  // remove from connectedPlayers and inLobbyPlayers and lobbySpecter if exists
                  std::string responseStr = std::to_string(cid) + MS_DATA_DELIMITER;

                  if(disconnectPlayer(currentItem.sender))
                  {
                    //broadcast to lobby players
                    response(RESPONSE_PLAYER_DISCONNECTED,responseStr,&inLobbyPlayers, nullptr,false);

                    //broadcast to specters
                    if(lobbySpecters.size()>=1)
                    {
                      response(RESPONSE_PLAYER_DISCONNECTED,responseStr,&lobbySpecters, nullptr,false);
                    }

                    //check for is that player left were owner or not
                    if(isThatPlayerOwner)
                    {
                        if(inLobbyPlayers.size() >= 1)
                          changeOwner(inLobbyPlayers[INDEX_NEXT_OWNER_AFTER_OWNER_LEFT].id);
                        else if(lobbySpecters.size() >= 1)
                          changeOwner(lobbySpecters[INDEX_NEXT_OWNER_AFTER_OWNER_LEFT].id);
                        else //delete lobby, lobby is empty..
                          destroyLobby();
                    }
                    else
                      log.print("that player left, were not owner.",FluffyMultiplayer::LogType::Information);

                  }
                  else //connection not found to disconnect
                  {
                    response(RESPONSE_ERROR_DISCONNECT_YOU_ARE_NOT_CONNECTED,responseStr,&lobbySpecters, nullptr,false);
                  }
                }
                else
                {
                  response(RESPONSE_INTERNAL_ERROR_FAILED_TO_DISCONNECT,currentItem.sender, false);
                }
              }
            }break;


            case REQUEST_JOIN_TO_LOBBY: // player will send cData = [0]->(identity), [1]->(password), [2]->(his client version)
            {
                if(cData[1] == lobbyData.password)
                {
                  if(ds.isIdentityValid(cData[0]))
                  {
                    if(cData[2] == GAME_SERVER_VERSION)
                    {



                      //get client info by identity
                      db.queryStr="SELECT clientId FROM fm_client_login WHERE identity='";
                      db.queryStr+= cData[0] + "';";
                      int cId = stringToInt(db.search_in_db(db.queryStr,true));
                      if(cId>=1) //is client exsits?
                      {
                        //check for old connected with that id and kick them out,
                        //e.g player timedout and connected again we have to remove that old one from player lists
                        if(isIdExistsInLobby(cId))
                        {
                          kickOutPlayerFromLobby(cId);
                        }

                        //check for ban and lobby size
                        // if(lobbyData.currentPlayers>=lobbyData.maxPlayers)
                        // {
                          // std::string lobbyFullstr = " lobby is full, current-players:" + std::to_string(lobbyData.currentPlayers) + " max-players:" + std::to_string(lobbyData.maxPlayers);
                          // log.print(lobbyFullstr,FluffyMultiplayer::LogType::Information);
                          // response(RESPONSE_ERROR_LOBBY_IS_FULL, currentItem.sender, false);
                        // }
                        if(isIdBannedFromLobby(cId))
                        {
                          response(RESPONSE_ERROR_JOIN_LOBBY_YOU_ARE_BANNED,currentItem.sender, false);
                        }
                        else
                        {
                          //try to add client into lobby.
                          db.queryStr="INSERT OR REPLACE INTO fm_client_in_lobby (clientId,lobbyId) VALUES('";
                          db.queryStr+= std::to_string(cId) + "', '";
                          db.queryStr+= std::to_string(lobbyData.id) + "');";
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

                            //set connected player as tempplayer (this will push into list specter or in lobby)
                            tempPlayer.set(cId,cData[0],currentItem.sender,
                                      cUsername,cIsAdmin,isPlayerOwner(cId),gameIsRunning);

                            //check that connected is player in lobby (inGame) or as specter
                            if(gameIsRunning)
                            {
                              log.print("player added into lobby as SPECTER.",FluffyMultiplayer::LogType::Information);
                              lobbySpecters.push_back(tempPlayer);
                            }
                            else
                            {
                              log.print("player added into lobby as PLAYER.",FluffyMultiplayer::LogType::Information);
                              inLobbyPlayers.push_back(tempPlayer);
                            }
                            std::string serverStatusPrint = "\n----------------------------\nserver status:\ntotal connected:" + std::to_string(connectedPlayers.size());
                            serverStatusPrint += "\n players in lobby:" +  std::to_string(inLobbyPlayers.size());
                            serverStatusPrint += "\n players as specter:" +  std::to_string(lobbySpecters.size());
                            log.print(serverStatusPrint, FluffyMultiplayer::LogType::Information);

                            //tell sender ur accepted but this response will popout and that client has no access to data because will pop() from WaitForResponse due to Pointers and States
                            response(RESPONSE_YOU_ARE_JOINT_INTO_LOBBY,currentItem.sender, false);



                            //broadcast to in lobby client joint except that connected player
                            std::vector<FluffyMultiplayer::Player> exceptSenderList
                            {
                              tempPlayer
                            };

                            //package connected player information: id, name, isOwner, isAdmin, isSpecter, voiceChatStatus
                            std::string playerConnectedStr = std::to_string(tempPlayer.id);
                            playerConnectedStr += MS_DATA_DELIMITER;
                            playerConnectedStr += tempPlayer.name;
                            playerConnectedStr += MS_DATA_DELIMITER;
                            playerConnectedStr += std::to_string(static_cast<int>(tempPlayer.isOwner));
                            playerConnectedStr += MS_DATA_DELIMITER;
                            playerConnectedStr += std::to_string(static_cast<int>(tempPlayer.isAdmin));
                            playerConnectedStr += MS_DATA_DELIMITER;
                            playerConnectedStr += std::to_string(static_cast<int>(tempPlayer.isSpecter));
                            playerConnectedStr += MS_DATA_DELIMITER;
                            playerConnectedStr += std::to_string(static_cast<int>(tempPlayer.voiceChatEnable));
                            playerConnectedStr += MS_DATA_DELIMITER;


                            //package old players into a string
                            std::string oldPlayers;
                            for(int i=0; i< inLobbyPlayers.size(); i++)
                            {
                              if(inLobbyPlayers[i].id == tempPlayer.id)
                                continue;//skip this player were added (becuase its that player who new connected must be first)
                              else
                              {
                                oldPlayers += std::to_string(inLobbyPlayers[i].id);
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += inLobbyPlayers[i].name;
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += std::to_string(static_cast<int>(inLobbyPlayers[i].isOwner));
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += std::to_string(static_cast<int>(inLobbyPlayers[i].isAdmin));
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += std::to_string(static_cast<int>(inLobbyPlayers[i].isSpecter));
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += std::to_string(static_cast<int>(inLobbyPlayers[i].voiceChatEnable));
                                oldPlayers += MS_DATA_DELIMITER;
                              }
                            }

                            //package specters into a string
                            for(int i=0; i< lobbySpecters.size(); i++)
                            {
                              if(lobbySpecters[i].id == tempPlayer.id)
                                continue;//skip this player were added (becuase its that player who new connected must be first)
                              else
                              {
                                oldPlayers += std::to_string(lobbySpecters[i].id);
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += lobbySpecters[i].name;
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += std::to_string(static_cast<int>(lobbySpecters[i].isOwner));
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += std::to_string(static_cast<int>(lobbySpecters[i].isAdmin));
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += std::to_string(static_cast<int>(lobbySpecters[i].isSpecter));
                                oldPlayers += MS_DATA_DELIMITER;
                                oldPlayers += std::to_string(static_cast<int>(lobbySpecters[i].voiceChatEnable));
                                oldPlayers += MS_DATA_DELIMITER;
                              }
                            }



                            //playerConnectedStr must hold only that newly conencted player because needs to send that into others just that new one player.
                            oldPlayers = playerConnectedStr + oldPlayers;

                            //tell sender his information and others information
                            response(RESPONSE_LOBBY_PLAYERS_ARE,
                              oldPlayers, //first player is that client conected new, other is players in lobby then specters
                              currentItem.sender, false);


                            //if game is on report game data.. for specters or reconnecter player
                            //...


                            //broadcast to inlobby players except sender
                            response(RESPONSE_PLAYER_JOINT_INTO_LOBBY,
                                     playerConnectedStr,&inLobbyPlayers,&exceptSenderList);

                            //broadcast to speceters except sender
                            if(lobbySpecters.size()>=1)
                            {
                              response(RESPONSE_PLAYER_JOINT_INTO_LOBBY,
                                       playerConnectedStr,&lobbySpecters,&exceptSenderList);
                            }

                          }
                          else
                          {
                            //faield to join lobby maybe client is already in lobby or have some databse insert issue
                            // RESPONSE_ERROR_JOIN_LOBBY_YOU_ARE_ALREADY_JOINT -> because of using INSERT OR REPLACE INTO this problem solved for many cases
                            response(RESPONSE_INTERNAL_ERROR_FAILED_TO_JOIN_INTO_LOBBY,currentItem.sender, false);
                          }
                        }

                      }
                      else
                      {
                        //id is <=0 so invalid. player not found -> invalid identity
                        response(RESPONSE_ERROR_JOIN_LOBBY_INVALID_IDENTITY,currentItem.sender, false);
                      }
                    }
                    else
                    {
                      std::string strVersionError = "client version is out of date. entered version: "+  cData[2];
                      log.print(strVersionError,FluffyMultiplayer::LogType::Information);
                      response(RESPONSE_ERROR_YOUR_GAME_CLIENT_VERSION_IS_OUT_OF_DATE,currentItem.sender, false);
                    }
                  }
                  else
                  {
                    log.print("join to lobby: invalid identity. data="+currentItem.data, FluffyMultiplayer::LogType::Information);
                    response(RESPONSE_ERROR_JOIN_LOBBY_INVALID_IDENTITY,currentItem.sender, false);
                  }
                }
                else //incorrect password
                {
                  response(RESPONSE_ERROR_JOIN_LOBBY_PASSWORD_INCORRECT,currentItem.sender, false);
                }

            }break;

            case REQUEST_GET_LOBBY_INFO:
            //id,gm,max,current,voicePort,voiceStatus,textStatus,specterStatus
            {
              std::string responseLobbyInfoIs = std::to_string(lobbyData.id);
              responseLobbyInfoIs += MS_DATA_DELIMITER;
              responseLobbyInfoIs += std::to_string(lobbyData.gameMode);
              responseLobbyInfoIs += MS_DATA_DELIMITER;
              responseLobbyInfoIs += std::to_string(lobbyData.maxPlayers);
              responseLobbyInfoIs += MS_DATA_DELIMITER;
              responseLobbyInfoIs += std::to_string(lobbyData.currentPlayers);
              responseLobbyInfoIs += MS_DATA_DELIMITER;
              responseLobbyInfoIs += std::to_string(lobbyData.voicePort);
              responseLobbyInfoIs += MS_DATA_DELIMITER;
              responseLobbyInfoIs += std::to_string(lobbyData.isVoiceChatForbidden);
              responseLobbyInfoIs += MS_DATA_DELIMITER;
              responseLobbyInfoIs += std::to_string(lobbyData.isTextChatForbidden);
              responseLobbyInfoIs += MS_DATA_DELIMITER;
              responseLobbyInfoIs += std::to_string(lobbyData.isSpecterForbidden);
              responseLobbyInfoIs += MS_DATA_DELIMITER;
              response(RESPONSE_LOBBY_INFO_IS,responseLobbyInfoIs, currentItem.sender, false);
            }break;


            case REQUEST_GET_LOBBY_SETTINGS:
            {
              if(doesItHavePermission(currentItem.sender))
                response(RESPONSE_LOBBY_SETTINGS_IS,lobbyData.getAsStringForOwner(getPlayerUsernameById(lobbyData.ownerId)),currentItem.sender, false);
              else
                response(RESPONSE_ERROR_GET_LOBBY_SETTINGS_NO_PERMISSION,currentItem.sender, false);

            }break;

            case REQUEST_UPDATE_LOBBY_SETTINGS:
            /*
                client will send: [0]->(maxPlayers), [1]->gameMode,
                                  [2]->isVoiceChatForbidden
                                  [3]->isTextChatForbidden, [4]->isSpecterForbidden,
                                  [5]->password, [6]->ownerId
            */
            {
              if(doesItHavePermission(currentItem.sender))
              {
                //apply received changes into lobby
                lobbyData.maxPlayers = stringToInt(cData[0]);
                lobbyData.gameMode = stringToInt(cData[1]);
                lobbyData.isVoiceChatForbidden = stringToBool(cData[2]);
                lobbyData.isTextChatForbidden = stringToBool(cData[3]);
                lobbyData.isSpecterForbidden = stringToBool(cData[4]);
                lobbyData.password = cData[5];
                lobbyData.ownerId = stringToInt(cData[6]);

                //update lobby on database
                db.queryStr = "UPDATE fm_lobby SET maxPlayers='";
                db.queryStr+= cData[0] + "', gameMode='";
                db.queryStr+= cData[1] + "', voiceChatForbidden='";
                db.queryStr+= cData[2] + "', textChatForbidden='";
                db.queryStr+= cData[3] + "', specterForbidden='";
                db.queryStr+= cData[4] + "', password='";
                db.queryStr+= cData[5] + "', owner='";
                db.queryStr+= cData[6] + "' WHERE id='";
                db.queryStr+= std::to_string(lobbyData.id) + "';";
                if(db.query_to_db())
                {
                  log.print("lobby settings updated "+lobbyData.getAsStringForOwner(getPlayerUsernameById(lobbyData.ownerId)), FluffyMultiplayer::LogType::Information);

                  changeGameMode();

                  //lobby settings updated: id,gm,max,current,voicePort,voiceStatus,textStatus,specterStatus,ownerid
                  std::string responseLobbySettingsUpdated = std::to_string(lobbyData.id);
                  responseLobbySettingsUpdated += MS_DATA_DELIMITER;
                  responseLobbySettingsUpdated += std::to_string(lobbyData.gameMode);
                  responseLobbySettingsUpdated += MS_DATA_DELIMITER;
                  responseLobbySettingsUpdated += std::to_string(lobbyData.maxPlayers);
                  responseLobbySettingsUpdated += MS_DATA_DELIMITER;
                  responseLobbySettingsUpdated += std::to_string(lobbyData.currentPlayers);
                  responseLobbySettingsUpdated += MS_DATA_DELIMITER;
                  responseLobbySettingsUpdated += std::to_string(lobbyData.voicePort);
                  responseLobbySettingsUpdated += MS_DATA_DELIMITER;
                  responseLobbySettingsUpdated += std::to_string(lobbyData.isVoiceChatForbidden);
                  responseLobbySettingsUpdated += MS_DATA_DELIMITER;
                  responseLobbySettingsUpdated += std::to_string(lobbyData.isTextChatForbidden);
                  responseLobbySettingsUpdated += MS_DATA_DELIMITER;
                  responseLobbySettingsUpdated += std::to_string(lobbyData.isSpecterForbidden);
                  responseLobbySettingsUpdated += MS_DATA_DELIMITER;
                  responseLobbySettingsUpdated += std::to_string(lobbyData.ownerId);
                  responseLobbySettingsUpdated += MS_DATA_DELIMITER;

                  //broadcast lobby setting changes to in lobby
                  response(RESPONSE_LOBBY_SETTINGS_UPDATED,responseLobbySettingsUpdated,&inLobbyPlayers,nullptr,false);

                  //broadcast lobby setting changes to specters
                  if(lobbySpecters.size()>=1)
                  {
                    response(RESPONSE_LOBBY_SETTINGS_UPDATED,responseLobbySettingsUpdated,&lobbySpecters,nullptr,false);
                  }
                }
                else
                {
                  log.print("failed to update lobby, internal error. ", FluffyMultiplayer::LogType::Information);
                  response(RESPONSE_INTERNAL_ERROR_FAILED_TO_UPDATE_LOBBY_SETTINGS,currentItem.sender, false);
                }

              }
              else
              {
                response(RESPONSE_ERROR_UPDATE_LOBBY_SETTINGS_NO_PERMISSION,currentItem.sender, false);
              }

            }break;

            case REQUEST_STOP_START_GAME:
            {
              if(doesItHavePermission(currentItem.sender))
              {
                if(gameIsRunning)
                {
                    if(stopGame())
                    {
                      response(RESPONSE_GAME_STOPPED,&inLobbyPlayers,nullptr,false);
                    }
                    else
                    {
                      response(RESPONSE_INTERNAL_ERROR_FAILED_TO_STOP_GAME,currentItem.sender, false);
                    }
                }
                else
                {
                  if(startGame())
                  {
                    response(RESPONSE_GAME_STARTED,&inLobbyPlayers,nullptr,false);
                  }
                  else
                  {
                    response(RESPONSE_INTERNAL_ERROR_FAILED_TO_START_GAME,currentItem.sender, false);
                  }
                }
              }
              else
              {
                response(RESPONSE_ERROR_START_GAME_NO_PERMISSION,currentItem.sender, false);
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
                  response(RESPONSE_LOBBY_DELETED,&inLobbyPlayers,nullptr,false);

                  //tell lobbySpecters lobby is deleted.
                  response(RESPONSE_LOBBY_DELETED,&lobbySpecters,nullptr,false);

                  //close server application
                  log.print("lobby deleted. lobbyId="+std::to_string(lobbyData.id), FluffyMultiplayer::LogType::Information);
                  appIsRunning=false;
                }
                else
                {
                  response(RESPONSE_INTERNAL_ERROR_FAILED_TO_DELETE_LOBBY,currentItem.sender, false);
                }
              }
              else
              {
                response(RESPONSE_ERROR_DELETE_LOBBY_NO_PERMISSION,currentItem.sender, false);
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

                    std::string responseStr = std::to_string(targetId) + MS_DATA_DELIMITER;

                    //broadcast to inLobbyPlayers, player has been kicked from lobby
                    response(RESPONSE_PLAYER_KICKED_FROM_LOBBY,responseStr,&inLobbyPlayers,nullptr,false);

                    //broadcast to specters, player has been kicked from lobby
                    if(lobbySpecters.size()>=1)
                    {
                      response(RESPONSE_PLAYER_KICKED_FROM_LOBBY,responseStr,&lobbySpecters,nullptr,false);
                    }

                    //this line written blow of those, because we want to tell all (speacilly that target to you are kicked if put this line up would not send to targetId)
                    FluffyMultiplayer::AnAddress targetAddress = getPlayerAddressById(targetId);
                    disconnectPlayer(targetAddress);
                  }
                  else
                  {
                    response(RESPONSE_INTERNAL_ERROR_FAILED_TO_KICK_PLAYER,currentItem.sender, false);
                  }
                }
                else
                {
                  response(RESPONSE_ERROR_KICK_PLAYER_INVALID_TARGET,currentItem.sender, false);
                }
              }
              else
              {
                response(RESPONSE_ERROR_KICK_PLAYER_NO_PERMISSION,currentItem.sender, false);
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
                      FluffyMultiplayer::TimeAndDate::now(), stringToInt(cData[2])
                    };
                    bannedPlayers.push_back(targetAsBan);

                    std::string responseStr = std::to_string(targetId) + MS_DATA_DELIMITER; //later can write reason and ban time to tell other clients

                    //broadcast to inLobbyPlayers, player has been kicked from lobby
                    response(RESPONSE_PLAYER_BANNED_FROM_LOBBY,responseStr,&inLobbyPlayers,nullptr,false);

                    //broadcast to specters, player has been kicked from lobby
                    if(lobbySpecters.size()>=1)
                    {
                      response(RESPONSE_PLAYER_BANNED_FROM_LOBBY,responseStr,&lobbySpecters,nullptr,false);
                    }

                    //this line written blow of those, because we want to tell all (speacilly that target to you are banned if put this line up would not send to targetId)
                    FluffyMultiplayer::AnAddress targetAddress = getPlayerAddressById(targetId);
                    disconnectPlayer(targetAddress);
                }
                else
                {
                  response(RESPONSE_ERROR_BAN_PLAYER_INVALID_TARGET,currentItem.sender, false);
                }
              }
              else
              {
                response(RESPONSE_ERROR_BAN_PLAYER_NO_PERMISSION,currentItem.sender, false);
              }
            }
            }break;

            case REQUEST_SEND_TEXT_CHAT: //client will send: [0]->(messageText)
            {
              if(lobbyData.isTextChatForbidden)
              {
                response(RESPONSE_ERROR_SEND_TEXT_CHAT_DISABLED,currentItem.sender, false);
              }
              else
              {
                  std::string responseStr = getPlayerUsernameById(getSenderId(currentItem.sender)) + ": " + cData[0] + "\n";
                  log.print(responseStr, FluffyMultiplayer::LogType::Information);

                  //broadcast  new text message.. to inLobbyPlayers
                  response(RESPONSE_PLAYER_SENT_TEXT_MESSAGE,responseStr,&inLobbyPlayers,nullptr,false);

                  //broadcast new text message.. to specters
                  if(lobbySpecters.size()>=1 && SEND_TEXT_CHAT_TO_SPECTERS)
                  {
                    response(RESPONSE_PLAYER_SENT_TEXT_MESSAGE,responseStr,&lobbySpecters,nullptr,false);
                  }
              }
            }break;

            //NOTE case REQUEST_SEND_VOICE_CHAT: moved into processVoice()


            case REQUEST_ENABLE_DISABLE_VOICE_CHAT:
            {
              int cid = getSenderId(currentItem.sender);
              int responseCode = 0;
              if(cid>=1)
              {
                int pindex = getIndexPlayerInLobbyByAddress(currentItem.sender);

                if(inLobbyPlayers[pindex].voiceChatEnable)
                {
                  updatePlayerVoiceChatStatus(pindex,false);
                  responseCode = RESPONSE_PLAYER_VOICE_CHAT_DISABLED;
                }
                else
                {
                  updatePlayerVoiceChatStatus(pindex,true);
                  responseCode = RESPONSE_PLAYER_VOICE_CHAT_ENABLED;
                }
              }

                std::string responseStr = std::to_string(cid) + MS_DATA_DELIMITER;

                //broadcast to inLobbyPlayers, player has been kicked from lobby
                response(responseCode,responseStr,&inLobbyPlayers,nullptr,false);

                //broadcast to specters, player has been kicked from lobby
                if(lobbySpecters.size()>=1)
                {
                  response(responseCode,responseStr,&lobbySpecters,nullptr,false);
                }

            }break;

            default:
            {
              if(gameIsRunning)
              {
                if(currentGameMode!=nullptr)
                {
                  log.print("unknown request code lets passing it to gamemode", FluffyMultiplayer::LogType::Information);
                  currentGameMode = currentGameMode->process((*this),currentItem,cData);
                  //response to client will push by currentGameMode->process
                }
                else
                {
                  log.print("unknown request code and gamemode is nullptr (game is not started)", FluffyMultiplayer::LogType::Warning);
                  response(RESPONSE_UNKNOWN_REQUEST_GAME_IS_NOT_STARTED,currentItem.sender, false);
                }

              }
              else
              {
                log.print("unknown request code and game running = false (not started or paused)", FluffyMultiplayer::LogType::Warning);
                response(RESPONSE_UNKNOWN_REQUEST_GAME_PAUSED_OR_NOT_STARTED,currentItem.sender, false);
              }
            }

          }

      }
    }


    //remove processed element
    receivedTextDataList.pop();
  }


  void App::changeOwner(const int& oid)
  {
    if(oid<=0)
    {
      log.print("change owner id failed, invalid id..", FluffyMultiplayer::LogType::Information);
      return;
    }


    lobbyData.ownerId = oid;

    //apply into db
    db.queryStr="UPDATE fm_lobby SET owner='";
    db.queryStr+= std::to_string(oid) + "' WHERE id='";
    db.queryStr+= std::to_string(lobbyData.id) + "';";
    if(db.query_to_db())
    {
      std::string responseStr = std::to_string(oid) + MS_DATA_DELIMITER;

      //broadcast result of owner changed to lobby players
      response(RESPONSE_LOBBY_OWNER_CHANGED,responseStr,&inLobbyPlayers, nullptr,false);

      //broadcast to specters
      if(lobbySpecters.size()>=1)
        response(RESPONSE_LOBBY_OWNER_CHANGED,responseStr,&lobbySpecters, nullptr,false);
    }
    else
    {
      log.print("Internal errro while changing owner of lobby..", FluffyMultiplayer::LogType::Warning);
    }
  }

  void App::destroyLobby()
  {
    db.queryStr = "DELETE FROM fm_lobby WHERE id='";
    db.queryStr+= std::to_string(lobbyData.id) + "';";
    if(db.query_to_db())
    {
      appIsRunning=false;
    }
    else
    {
      log.print("failed to destroy lobby, (internal error because of database while deleting lobby.)", FluffyMultiplayer::LogType::Information);
    }
  }

  bool App::isIdExistsInLobby(int id)
  {
    for(auto player: inLobbyPlayers)
      if(player.id == id)
        return true;

    for(auto specter: lobbySpecters)
      if(specter.id == id)
        return true;

    return false;
  }

  void App::kickOutPlayerFromLobby(int id)
  {
    for(int i=0; i<inLobbyPlayers.size(); i++)
    {
      if(inLobbyPlayers[i].id == id)
      {
        inLobbyPlayers.erase(inLobbyPlayers.begin()+i);
        log.print("player found and kicked Out Player From Lobby.", FluffyMultiplayer::LogType::Information);
        return;
      }
    }

    for(int i=0; i<lobbySpecters.size(); i++)
    {
      if(lobbySpecters[i].id == id)
      {
        lobbySpecters.erase(lobbySpecters.begin()+i);
        log.print("specter found and kicked Out Player From Lobby.", FluffyMultiplayer::LogType::Information);
        return;
      }
    }

    log.print("player/specter not found to kickOutPlayerFromLobby", FluffyMultiplayer::LogType::Information);
  }

  void App::processVoice()
  {
    FluffyMultiplayer::SocketReceiveData currentItem;

    for(int i=0; i<receivedVoiceDataList.size(); i++)
    {
      currentItem = receivedVoiceDataList.front();
      log.print("[voice] sender="+currentItem.sender.getAsString()+
          "received data="+currentItem.data, FluffyMultiplayer::LogType::Information);

      log.print("process currentItem.code="
            +std::to_string(currentItem.code)+";~;",
            FluffyMultiplayer::LogType::Information);



      //check connection blocked
      if(isConnectionBlocked(currentItem.sender))
      {
        // response(sendVoiceDataList, RESPONSE_ERROR_CONNECTION_BLOCKED,currentItem.sender, false); //maybe later return blocked time to client
      }
      else if(!isConnectionExists(currentItem.sender))
      {
        response(RESPONSE_ERROR_CONNECTION_NOT_EXISTS,currentItem.sender, true);
      }
      else
      {
        //voice
        if(lobbyData.isVoiceChatForbidden)
        {
          response(RESPONSE_ERROR_SEND_VOICE_CHAT_DISABLED,currentItem.sender, true);
        }
        else
        {
          //prepare ovice chat data
          std::string responseStr = currentItem.data;


          //broadcast  new voice message.. to inLobbyPlayers
          for(auto e: inLobbyPlayers)
          {
            if(e.voiceChatEnable)
            {
              response(RESPONSE_PLAYER_SENT_VOICE_MESSAGE,responseStr,e.address,true);
            }
          }

          //broadcast new voice message.. to specters
          if(lobbySpecters.size()>=1 && SEND_VOICE_CHAT_TO_SPECTERS)
          {
            for(auto e: lobbySpecters)
            {
              if(e.voiceChatEnable)
              {
                response(RESPONSE_PLAYER_SENT_VOICE_MESSAGE,responseStr,e.address,true);
              }
            }
          }
        }
      }
    }

      //remove processed element
      receivedVoiceDataList.pop();
  }


  void App::process()
  {
    //process text requests
    // processText();

    //process voice requests
    // processVoice();
  }


  void App::run()
  {
    while(appIsRunning)
    {
      process();
    }
  }

  bool App::isConnectionExists(const FluffyMultiplayer::AnAddress& address) const
  {
    for(FluffyMultiplayer::AnAddress e : connectedPlayers)
    {
      if(e == address)
        return true;
    }
    return false;
  }


  //convert
  int App::stringToInt(const std::string& str)
  {
    const char* c = str.c_str();
    return std::atoi(c);
  }
  bool App::stringToBool(const std::string& str)
  {
    const char* c = str.c_str();
    return static_cast<bool>(std::atoi(c));
  }

  //player
  bool App::connectPlayer(FluffyMultiplayer::AnAddress& p)
  {
    connectedPlayers.push_back(p);
    log.print("ip(" + p.getAsString() + ") "
      + "connected to the lobby.", FluffyMultiplayer::LogType::Information);
    return true;
  }
  bool App::disconnectPlayer(FluffyMultiplayer::AnAddress& ad)
  {
    int currentPlayersBefore = lobbyData.currentPlayers;
    //remove from connectedPlayers
    std::vector<FluffyMultiplayer::AnAddress> _connectedPlayers;
    for(auto e: connectedPlayers)
    {
      if(e == ad)
        lobbyData.currentPlayers--;
      else
        _connectedPlayers.push_back(e);
    }
    connectedPlayers = _connectedPlayers;

    //check if that connection does not exists on connectedPlayers skip other commands
    if(currentPlayersBefore == lobbyData.currentPlayers)
    {
      log.print("disconnect player failed, Currentplayers are still same old value.", FluffyMultiplayer::LogType::Warning);
      return false; //could not remove there is no connection exists
    }


    //remove from inLobbyPlayers
    std::vector<FluffyMultiplayer::Player> _inLobbyPlayers;
    for(auto e: inLobbyPlayers)
    {
      if(e.address == ad)
        continue;
      else
        _inLobbyPlayers.push_back(e);
    }
    inLobbyPlayers = _inLobbyPlayers;


    //remove from lobbySpecters
    std::vector<FluffyMultiplayer::Player> _lobbySpecters;
    for(auto e: lobbySpecters)
    {
      if(e.address == ad)
        continue;
      else
        _lobbySpecters.push_back(e);
    }
    lobbySpecters = _lobbySpecters;

    return true;
  }

  //lobby
  bool App::startGame()
  {
    gameIsRunning=true;
    db.queryStr="UPDATE fm_lobby SET lobbyStatus='1' WHERE id='";
    db.queryStr+= std::to_string(lobbyData.id) + "';";
    if(db.query_to_db())
      return true;
    return false;
  }
  bool App::stopGame()
  {
    gameIsRunning=false;
    db.queryStr="UPDATE fm_lobby SET lobbyStatus='0' WHERE id='";
    db.queryStr+= std::to_string(lobbyData.id) + "';";
    if(db.query_to_db())
      return true;
    return false;
  }

}
