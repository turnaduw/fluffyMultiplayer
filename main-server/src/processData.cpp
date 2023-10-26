#include "../include/processData.h"


namespace FluffyMultiplayer
{
  int ProcessData::separateCode(const std::string& data)
  {
    //these MS_DATA_CODE_INDEX_X are from config.h
    std::string code_str = ( data[MS_DATA_CODE_INDEX_A] + data[MS_DATA_CODE_INDEX_B] + data[MS_DATA_CODE_INDEX_C] );
    const char* temp = _data.c_str();
    return std::atoi(temp);
  }

  bool ProcessData::isConnectionExists(const boost::asio::ip::address& senderIp, const unsigned short& senderPort);
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

    socket.send_to(boost::asio::buffer(message), receiver);
  }


  void ProcessData::connectClient(const boost::asio::ip::address& ip, const unsigned short& port)
  {
    FluffyMultiplayer::ConnectedClients temp(ip,port);
    clientList.push_back(temp);
  }

  void ProcessData::disconnectClient(const boost::asio::ip::address& ip, const unsigned short& port)
  {
    //remove ip n port from client list
  }

  std::vector<int> dataIndexes(const std::string& data, const std::string& delimiter);
  {
    std::vector<int> result;
    for(int i=0; i<=data.length()-1; i++)
    {
      int index = data.find(delimiter);
      if (index != std::string::npos)
        result.push_back(index);
    }
    return result;
  }


  std::vector<std::string> ProcessData::dataSeparator(const std::string& data, std::string delimiter, int startIndex=0, int endIndex=0)
  {
    std::vector<std::string> result;
    if(endIndex==0)
      endIndex = data.length()-1;

    std::vector<int>indexes = dataIndexes(data,delimiter);
    for(int i=0; i<=indexes.size(); i++)
    {
      int index=indexes[i];
      if(index<startIndex) //skip, because startIndex is not not included.
        continue;

      result.push_back(data.substr(index,endIndex));
    }
    return result;
  }

  int ProcessData::convertStringToInt(const std::string& data)
  {
    const char* c = data.c_str();
    return std::atoi(c);
  }

  bool ProcessData::isSQLCodeIncluded(const std::string& data)
  {
    //...
  }


  void ProcessData::process(udp::socket& socket, std::vector<FluffyMultiplayer::SocketDataStack>& stack, FluffyMultiplayer::FluffyDatabase& db)
  {
      for(int i=0; i<=stack.size(); i++)
      {
        udp::endpoint receiver(stack[i].ip, stack[i].port);


        //a function to call and check connection existant.
        auto checkConnection = [&] () -> bool
        {
          if(!isConnectionExists(stack[i].ip,stack[i].port))
          {
            sendData(MS_ERROR_CONNECTION_NOT_EXISTS,socket,receiver);
            stack.pop_back(); //remove processed request (current) from stack
            return false;
          }
          return true;
        };



        switch (stack[i].code)
        {
          case MS_REQUEST_CONNECT:
          {
            if(isConnectionExists(stack[i].ip,stack[i].port))
              sendData(MS_ERROR_CONNECTION_EXISTS,socket,receiver);
            else
            {
              connectClient(stack[i].ip,stack[i].port);
              sendData(MS_RESPONSE_CONNECTION_ACCEPTED,socket,receiver);
            }
          }break;

          case MS_REQUEST_DISCONNECT:
          {
            if(checkConnection())
            {
              disconnectClient(stack[i].ip,stack[i].port);
              sendData(MS_RESPONSE_DISCONNECTED,socket,receiver);
            }
          }break;

          case MS_REQUEST_LOGIN:
          {

          }break;

          case MS_REQUEST_REGISTER:
          {

          }break;

          case MS_REQUEST_CREATE_LOBBY:
          {
            if(checkConnection())
            {
              std::vector<std::string>data = dataSeparator(stack[i].data, MS_DATA_DELIMITER, MS_DATA_START_AT_INDEX);
              FluffyMultiplayer::CreateLobbyData createLobbyInfo =
              {
                data[0],
                data[1],
                convertStringToInt(data[2]),
                static_cast<bool>(convertStringToInt(data[3])),
                static_cast<bool>(convertStringToInt(data[4])),
                static_cast<bool>(convertStringToInt(data[5]))
              };


              //data check
              if(createLobbyInfo.identity.length() < MS_CLIENT_MINIMUM_IDENTITY_LENGTH
                || createLobbyInfo.identity.length() > MS_CLIENT_MAXIMUM_IDENTITY_LENGTH
                || isSQLCodeIncluded(data)
              {
                sendData(MS_ERROR_FAILED_TO_LOBBY_CREATION_BAD_DATA_SYNTAX,socket,receiver);
                break;
              }
              else
              {
                if(db.isIdentityExists(createLobbyInfo.identity))
                {
                  std::string resultServerInfo;
                  int result = db.createLobby(createLobbyInfo,resultServerInfo);
                  switch (result)
                  {
                    case 0:
                    {
                      sendData(MS_RESPONSE_SUCCESS_LOBBY_CREATED,socket,receiver,resultServerInfo);
                    }break;
                    case 1:
                    {
                      sendData(MS_ERROR_FAILED_TO_LOBBY_CREATION_FORBIDDEN_FOR_YOU,socket,receiver);
                    }break;
                    case 2:
                    {
                      sendData(MS_ERROR_FAILED_TO_LOBBY_CREATION_CANT_OWN_TWO_LOBBY,socket,receiver);
                    }break;
                    default: //interanl error or unexcepted error
                    {
                      sendData(MS_ERROR_FAILED_TO_CREATE_LOBBY,socket,receiver);
                    }
                  }
                }
                else
                {
                  sendData(MS_ERROR_FAILED_TO_LOBBY_CREATION_INVALID_IDENTITY,socket,receiver);
                }
              }

            }
          }break;

          case MS_REQUEST_GET_LOBBY_LIST:
          {
            if(checkConnection())
            {
              std::string lobbies = db.getLobbyList(MS_GET_LOBBY_LIST_COUNT_OF_RESULTS);
              if(lobbies.length()>=1)
                sendData(MS_RESPONSE_SUCCESS_GET_LOBBY_LIST,socket,receiver,lobbies);
              else
                sendData(MS_ERROR_FAILED_TO_GET_LOBBY_LIST_NO_LOBBY_AVAIABLE,socket,receiver);
            }
          }break;

          case MS_REQUEST_GET_LOBBY_INFO:
          {
            if(checkConnection())
            {
              std::vector<std::string>data = dataSeparator(stack[i].data, MS_DATA_DELIMITER, MS_DATA_START_AT_INDEX);
              int lobbyId = convertStringToInt(data[0]);
              if(lobbyId==0)
                sendData(MS_ERROR_FAILED_TO_GET_LOBBY_INFO_BAD_DATA_SYNTAX,socket,receiver);
              else
              {
                std::string lobbyData = db.getLobbyInfo(lobbyId);
                if(lobbyData.length()>=1)
                  sendData(MS_RESPONSE_SUCCESS_GET_LOBBY_INFO,socket,receiver,lobbyData);
                else
                  sendData(MS_ERROR_FAILED_TO_GET_LOBBY_INFO_LOBBY_NOT_FOUND,socket,receiver);
              }
            }
          }break;

          case MS_REQUEST_LATEST_VERSION:
          {
            if(checkConnection())
            {
              sendData(MS_RESPONSE_SUCCESS_LATEST_VERSION,socket,receiver,MS_VERSION);
            }
          }break;

          default:
          {
            std::cout << "Unknown request code is: " << stack[i].code << std::endl;
          }break;
        }

        //remove processed element
        stack.pop_back();
      }

    }//end of function

}//end of namespace
