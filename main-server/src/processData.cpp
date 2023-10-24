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

  void ProcessData::process(udp::socket& socket, std::vector<FluffyMultiplayer::SocketDataStack>& stack)
  {
    while(1)
    {
      if(stack.size()>=1)
      {
        switch (stack.code)
        {
          case MS_REQUEST_CONNECT:
          {

          }break;
          case MS_REQUEST_DISCONNECT:
          {

          }break;
          case MS_REQUEST_LOGIN:
          {

          }break;
          case MS_REQUEST_REGISTER:
          {

          }break;
          case MS_REQUEST_CREATE_LOBBY:
          {

          }break;
          case MS_REQUEST_GET_LOBBY_LIST:
          {

          }break;
          case MS_REQUEST_GET_LOBBY_INFO:
          {

          }break;
          case MS_REQUEST_LATEST_VERSION:
          {

          }break;
          default:
          {
            std::cout << "Unknown request code is: " << stack.code << std::endl;
          }break;
        }

        //remove processed element
        stack.pop_back();
      }
    }

  }


}//end of namespace
