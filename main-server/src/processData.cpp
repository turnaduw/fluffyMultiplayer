#include "../include/processData.h"


namespace FluffyMultiplayer
{
  ProcessData::ProcessData()
  {

  }
  ProcessData::~ProcessData()
  {

  }

  int ProcessData::separateCode(const std::string& data)
  {
    //these MS_DATA_CODE_INDEX_X are from config.h
    char codes [3] = {data[MS_DATA_CODE_INDEX_A], data[MS_DATA_CODE_INDEX_B], data[MS_DATA_CODE_INDEX_C]};
    const char* temp = codes;
    return std::atoi(temp);
  }

  bool ProcessData::isConnectionExists(const boost::asio::ip::address& senderIp, const unsigned short& senderPort)
  {
    for (int i = 0; i < clientList.size(); i++)
      if(clientList[i].ip == senderIp && clientList[i].port == senderPort)
        return true;
    return false;
  }

  void ProcessData::sendData(int code, udp::socket& socket, udp::endpoint& receiver, std::string data="")
  {
    std::string message = std::to_string(code);
    if(data.length()>1)
      message+=data;

    message+=MS_DATA_DELIMITER; //add delimiter after data
    message+=MS_REQUEST_CLOSER; //add closer to endof all messages.
    dataSecurity.encryptData(message);

    std::cout << "send data =" << message << " receiver=" << receiver.address() << ":" << receiver.port() << std::endl;
    socket.send_to(boost::asio::buffer(message), receiver);
  }


  void ProcessData::connectClient(const boost::asio::ip::address& ip, const unsigned short& port)
  {
    ConnectedClients temp{ip,port};
    clientList.push_back(temp);
  }

  void ProcessData::disconnectClient(const boost::asio::ip::address& ip, const unsigned short& port)
  {
    //search then remove ip n port from client list
  }

  std::vector<int> ProcessData::dataIndexes(const std::string& data, const std::string& delimiter) const
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


  std::vector<std::string> ProcessData::dataSeparator(const std::string& data, std::string delimiter, int startIndex=0)
  {
    std::vector<std::string> result;
    std::string str = data.substr(startIndex,data.length()-1);

    std::vector<int>indexes = dataIndexes(str,delimiter);
    for(int i=0; i<indexes.size(); i++)
    {
      int index=indexes[i];

      result.push_back(str.substr(0,index)); //-delimiter.length()));
      str = str.substr(index+delimiter.length() ,str.length()-1);
    }
    return result;
  }




  bool ProcessData::isDataValidated(const FluffyMultiplayer::RegisterClientData& client) const
  {
    // if(  client.username.length() < MS_CLIENT_MINIMUM_USERNAME_LENGTH || client.username.length() > MS_CLIENT_MAXIMUM_USERNAME_LENGTH
    //   || client.password.length() < MS_CLIENT_MINIMUM_PASSWORD_LENGTH || client.password.length() > MS_CLIENT_MAXIMUM_PASSWORD_LENGTH
    //   || client.hardwareId.length() < MS_CLIENT_MINIMUM_HARDWAREID_LENGTH || client.hardwareId.length() > MS_CLIENT_MAXIMUM_HARDWAREID_LENGTH
    //   || client.email.length() < MS_CLIENT_MINIMUM_EMAIL_LENGTH || client.email.length() > MS_CLIENT_MAXIMUM_EMAIL_LENGTH)
    // {
    //   return false;
    // }
    return true;
  }
  bool ProcessData::isDataValidated(const FluffyMultiplayer::CreateLobbyData& data) const
  {
    // if(  data.identity.length() < MS_CLIENT_MINIMUM_IDENTITY_LENGTH
    //   || data.identity.length() > MS_CLIENT_MAXIMUM_IDENTITY_LENGTH)
    // {
    //   return false;
    // }
    return true;
  }

  bool ProcessData::isDataValidated(const FluffyMultiplayer::LoginClientData& client, bool isRelogin=false) const
  {
    if(isRelogin)
    {
      // if(  client.hardwareId.length() < MS_CLIENT_MINIMUM_HARDWAREID_LENGTH || client.hardwareId.length() > MS_CLIENT_MAXIMUM_HARDWAREID_LENGTH
      //   || client.oldIdentity.length() < MS_CLIENT_MINIMUM_IDENTITY_LENGTH || client.oldIdentity.length() > MS_CLIENT_MAXIMUM_IDENTITY_LENGTH)
      // {
        //   return false;
        // }
    }
    else
    {
      // if(  client.username.length() < MS_CLIENT_MINIMUM_USERNAME_LENGTH || client.username.length() > MS_CLIENT_MAXIMUM_USERNAME_LENGTH
      //   || client.password.length() < MS_CLIENT_MINIMUM_PASSWORD_LENGTH || client.password.length() > MS_CLIENT_MAXIMUM_PASSWORD_LENGTH
      //   || client.hardwareId.length() < MS_CLIENT_MINIMUM_HARDWAREID_LENGTH || client.hardwareId.length() > MS_CLIENT_MAXIMUM_HARDWAREID_LENGTH
      //   || client.oldIdentity.length() < MS_CLIENT_MINIMUM_IDENTITY_LENGTH || client.oldIdentity.length() > MS_CLIENT_MAXIMUM_IDENTITY_LENGTH)
      // {
        //   return false;
        // }
    }
    return true;
  }

  void ProcessData::process(udp::socket& socket, std::queue<FluffyMultiplayer::SocketDataQueue>& queue, FluffyMultiplayer::FluffyDatabase& db)
  {
      FluffyMultiplayer::SocketDataQueue currentItem;


      bool elementProcessed = false; //a flag to avoid pop un-processed element
      std::string receivedData;
      boost::asio::ip::address senderIp;
      unsigned short senderPort;

      for(int i=0; i<queue.size(); i++)
      {
        currentItem = queue.front();
        elementProcessed = false; //a flag to avoid pop un-processed element
        receivedData = currentItem.data;
        senderIp = currentItem.ip;
        senderPort = currentItem.port;
        std::cout << "senderIp="<<senderIp << " senderPort=" << senderPort << " received data=" << receivedData << std::endl;
        udp::endpoint receiverEndpoint(senderIp,senderPort);

        if(receivedData.length()>MS_RECEIVED_DATA_MINIMUM_LENGTH)
          dataSecurity.decryptData(receivedData);

        if(dataSecurity.isSQLCodeIncluded(receivedData))
          dataSecurity.removeSQLCodeFromData(receivedData);

        //a function to call and check connection existant.
        auto checkConnection = [&] () -> bool
        {
          if(!isConnectionExists(senderIp,senderPort))
          {
            sendData(MS_ERROR_CONNECTION_NOT_EXISTS,socket,receiverEndpoint);
            elementProcessed=true;
            queue.pop(); //remove processed request (current) from queue
            return false;
          }
          return true;
        };


        std::cout << "process currentItem.code=" << currentItem.code << ";~;" << std::endl;
        switch (currentItem.code)
        {
          case MS_REQUEST_CONNECT:
          {
            if(isConnectionExists(senderIp,senderPort))
            {
              sendData(MS_ERROR_CONNECTION_EXISTS,socket,receiverEndpoint);
            }
            else
            {
              connectClient(senderIp,senderPort);
              sendData(MS_RESPONSE_CONNECTION_ACCEPTED,socket,receiverEndpoint);
            }
          }break;

          case MS_REQUEST_DISCONNECT:
          {
            if(checkConnection())
            {
              disconnectClient(senderIp,senderPort);
              sendData(MS_RESPONSE_DISCONNECTED,socket,receiverEndpoint);
            }
          }break;

          case MS_REQUEST_RELOGIN:
          {
            if(checkConnection())
            {
              std::vector<std::string>data = dataSeparator(receivedData, MS_DATA_DELIMITER, MS_DATA_START_AT_INDEX);
              FluffyMultiplayer::LoginClientData client;
              switch (data.size())
              {
                case 2: //username and password is first of struct musst be filled so fill with empty
                  client = { "", "", data[0], data[1]};
                  break;
                default: //to handle broken requests
                  client = {"", "" , "" , ""};
              }
              std::cout << "relogin client:\nusername=" << client.username << "\npassword=" << client.password << "\nhardwareid=" << client.hardwareId << "\nidentity=" << client.oldIdentity << std::endl;

              //data check
              if(isDataValidated(client,true)) //trues is a flag to tell its relogin do not check username and password
              {
                std::string identityResult;
                int resultCode = db.reloginClient(client,identityResult);

                if(resultCode == MS_RESPONSE_SUCCESS_LOGIN)
                  sendData(resultCode,socket,receiverEndpoint,identityResult);
                else
                  sendData(resultCode,socket,receiverEndpoint);
              }
              else
                sendData(MS_ERROR_FAILED_TO_LOGIN_BAD_DATA_SYNTAX,socket,receiverEndpoint);
            }
          }break;

          case MS_REQUEST_LOGIN:
          {
            if(checkConnection())
            {
              std::vector<std::string>data = dataSeparator(receivedData, MS_DATA_DELIMITER, MS_DATA_START_AT_INDEX);
              FluffyMultiplayer::LoginClientData client;
              switch (data.size())
              {
                case 1:
                  client = { data[0] , "" , "" , "" };
                    break;

                case 2:
                  client = { data[0], data[1] , "" , "" };
                  break;

                case 3:
                  client = { data[0], data[1], data[2] , ""};
                  break;

                case 4:
                  client = { data[0], data[1], data[2], data[3] };
                  break;
              }

              //data check
              if(isDataValidated(client))
              {
                std::string identityResult;
                int resultCode = db.loginClient(client,identityResult);

                if(resultCode == MS_RESPONSE_SUCCESS_LOGIN)
                  sendData(resultCode,socket,receiverEndpoint,identityResult);
                else
                  sendData(resultCode,socket,receiverEndpoint);
              }
              else
                sendData(MS_ERROR_FAILED_TO_LOGIN_BAD_DATA_SYNTAX,socket,receiverEndpoint);
            }
          }break;

          case MS_REQUEST_REGISTER:
          {
            if(checkConnection())
            {
              std::vector<std::string>data = dataSeparator(receivedData, MS_DATA_DELIMITER, MS_DATA_START_AT_INDEX);
              FluffyMultiplayer::RegisterClientData client;
              switch(data.size())
              {
                case 1:
                  client = { data[0], "" , "" , "" };
                    break;

                case 2:
                  client = { data[0], data[1] , "" , "" };
                  break;

                case 3:
                  client = { data[0], data[1], data[2] , ""};
                  break;

                case 4:
                  client = { data[0], data[1], data[2], data[3] };
                  break;
              }
              // FluffyMultiplayer::RegisterClientData client = { data[0], data[1], data[2], data[3] };

              if(isDataValidated(client))
              {
                std::string identityResult;
                int resultCode = db.registerClient(client,identityResult);

                if(resultCode == MS_RESPONSE_SUCCESS_REGISTER)
                  sendData(resultCode,socket,receiverEndpoint,identityResult);
                else
                  sendData(resultCode,socket,receiverEndpoint);
              }
              else
                sendData(MS_ERROR_FAILED_TO_REGISTER_BAD_DATA_SYNTAX,socket,receiverEndpoint);

            }
          }break;

          case MS_REQUEST_CREATE_LOBBY:
          {
            if(checkConnection())
            {
              std::vector<std::string>data = dataSeparator(receivedData, MS_DATA_DELIMITER, MS_DATA_START_AT_INDEX);
              FluffyMultiplayer::CreateLobbyData createLobbyInfo;
              switch (data.size())
              {
                case 1:
                {
                  createLobbyInfo =
                            {data[0], 0, 0, false, false, false, ""};
                }break;

                case 2:
                {
                  createLobbyInfo =
                            {data[0], FluffyMultiplayer::convertStringToInt(data[1]), 0, false, false, false, ""};
                }break;

                case 3:
                {
                  createLobbyInfo =
                            {data[0], FluffyMultiplayer::convertStringToInt(data[1]),
                                      FluffyMultiplayer::convertStringToInt(data[2]), false, false, false, ""};
                }break;

                case 4:
                {
                  createLobbyInfo =
                            {data[0], FluffyMultiplayer::convertStringToInt(data[1]),
                                      FluffyMultiplayer::convertStringToInt(data[2]),
                                      !static_cast<bool>(FluffyMultiplayer::convertStringToInt(data[3])),
                                      false, false, ""};
                }break;

                case 5:
                {
                  createLobbyInfo =
                            {data[0], FluffyMultiplayer::convertStringToInt(data[1]),
                                      FluffyMultiplayer::convertStringToInt(data[2]),
                                      !static_cast<bool>(FluffyMultiplayer::convertStringToInt(data[3])),
                                      !static_cast<bool>(FluffyMultiplayer::convertStringToInt(data[4])),
                                      false, ""};
                }break;

                case 6:
                {
                  createLobbyInfo =
                            {data[0], FluffyMultiplayer::convertStringToInt(data[1]),
                                      FluffyMultiplayer::convertStringToInt(data[2]),
                                      !static_cast<bool>(FluffyMultiplayer::convertStringToInt(data[3])),
                                      !static_cast<bool>(FluffyMultiplayer::convertStringToInt(data[4])),
                                      !static_cast<bool>(FluffyMultiplayer::convertStringToInt(data[5])), ""};
                }break;

                case 7:
                {
                  createLobbyInfo =
                  {
                    data[0],
                    FluffyMultiplayer::convertStringToInt(data[1]),
                    FluffyMultiplayer::convertStringToInt(data[2]),
                    !static_cast<bool>(FluffyMultiplayer::convertStringToInt(data[3])),
                    !static_cast<bool>(FluffyMultiplayer::convertStringToInt(data[4])),
                    !static_cast<bool>(FluffyMultiplayer::convertStringToInt(data[5])),
                    data[6]
                  };
                }break;

                default:
                  createLobbyInfo = {"", 0, 0, false, false, false, ""};

              }

              std::cout << "createLobbyData data: \nidentity=" << createLobbyInfo.identity
                  << "\ngamemode=" << createLobbyInfo.gameMode
                  << "\nMaxplayers=" << createLobbyInfo.maxPlayers
                  << "\nvoiceChatForbidden=" << createLobbyInfo.voiceChatForbidden
                  << "\ntextChatForbidden=" << createLobbyInfo.textChatForbidden
                  << "\nspecterForbidden=" << createLobbyInfo.specterForbidden
                  << "\npassword=" << createLobbyInfo.password
                  << std::endl;

              if(isDataValidated(createLobbyInfo))
              {
                    std::string resultServerInfo;
                    int resultCode = db.createLobby(createLobbyInfo,resultServerInfo);
                    if(resultCode == MS_RESPONSE_SUCCESS_LOBBY_CREATED)
                      sendData(resultCode,socket,receiverEndpoint,resultServerInfo);
                    else
                      sendData(resultCode,socket,receiverEndpoint);
              }
              else
                sendData(MS_ERROR_FAILED_TO_LOBBY_CREATION_BAD_DATA_SYNTAX,socket,receiverEndpoint);

            }
          }break;

          case MS_REQUEST_GET_LOBBY_LIST:
          {
            if(checkConnection())
            {
              std::string lobbies = db.getLobbyList(MS_GET_LOBBY_LIST_COUNT_OF_RESULTS);
              if(lobbies.length()>=MS_MINIMUM_RETURNED_DATA_BY_SQL_SEARCH)
                sendData(MS_RESPONSE_SUCCESS_GET_LOBBY_LIST,socket,receiverEndpoint,lobbies);
              else
                sendData(MS_ERROR_FAILED_TO_GET_LOBBY_LIST_NO_LOBBY_AVAIABLE,socket,receiverEndpoint);
            }
          }break;

          case MS_REQUEST_GET_LOBBY_INFO:
          {
            if(checkConnection())
            {
              std::vector<std::string>data = dataSeparator(receivedData, MS_DATA_DELIMITER, MS_DATA_START_AT_INDEX);
              int lobbyId = FluffyMultiplayer::convertStringToInt(data[0]);
              if(lobbyId==MS_INVALID_LOBBY_ID_IS)
                sendData(MS_ERROR_FAILED_TO_GET_LOBBY_INFO_BAD_DATA_SYNTAX,socket,receiverEndpoint);
              else
              {
                std::string lobbyData = db.getLobbyInfo(lobbyId);
                if(lobbyData.length()>=MS_GET_LOBBY_BY_ID_MINIMUM_LENGTH)
                  sendData(MS_RESPONSE_SUCCESS_GET_LOBBY_INFO,socket,receiverEndpoint,lobbyData);
                else
                  sendData(MS_ERROR_FAILED_TO_GET_LOBBY_INFO_LOBBY_NOT_FOUND,socket,receiverEndpoint);
              }
            }
          }break;

          case MS_REQUEST_LATEST_VERSION:
          {
            if(checkConnection())
            {
              sendData(MS_RESPONSE_SUCCESS_LATEST_VERSION,socket,receiverEndpoint,MS_VERSION);
            }
          }break;

          default:
          {
            std::cout << "Unknown request code is: " << currentItem.code << std::endl;
          }break;
        }

        //remove processed element
        if(!elementProcessed)
          queue.pop();
      }

    }//end of function

}//end of namespace
