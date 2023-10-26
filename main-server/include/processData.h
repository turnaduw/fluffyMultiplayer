#ifndef H_PROCESS_DATA_CLASS
#define H_PROCESS_DATA_CLASS

#include "error-list.h"
#include "internal-error-list.h"
#include "request-list.h"
#include "response-list.h"

#include "config.h" //acess to MS_DATA_CODE_INDEX_A & ...B & ...C

#include <iostream>
#include <string>
#include <vector>

//convert string to int
#include <cstdlib>
using boost::asio::ip::udp;

#include "dataTypes.h" //access to struct SocketDataStack

#include "database.h" //access to type FluffyMultiplayer::FluffyDatabase
//socket
#include <boost/asio.hpp>


namespace FluffyMultiplayer
{
  class ProcessData
  {
  private:
    std::vector<FluffyMultiplayer::ConnectedClients> clientList;
  public:
    ProcessData();
    ~processData();

    void sendData(int ,udp::socket&, udp::endpoint&,std::string);
    bool isConnectionExists(const boost::asio::ip::address&, const unsigned short&);

    //manage the clientList
    void connectClient(const boost::asio::ip::address&, const unsigned short&);
    void disconnectClient(const boost::asio::ip::address&, const unsigned short&);

    std::vector<int> dataIndexes(const std::string&, const std::string&);
    std::vector<std::string> dataSeparator(const std::string&, std::string, int=0,int=0);
    int convertStringToInt(const std::string&);

    int separateCode(const std::string&); //means requesst code


    bool isSQLCodeIncluded(const std::string&); //write code..
    void decryptData(std::string&); //write code..
    void encryptData(std::string&); //write code..

    bool isDataValidated(FluffyMultiplayer::RegisterClientData&);
    bool isDataValidated(FluffyMultiplayer::CreateLobbyData&);
    bool isDataValidated(FluffyMultiplayer::LoginClientData&);

    void process(udp::socket&, std::vector<FluffyMultiplayer::SocketDataStack>&, FluffyMultiplayer::FluffyDatabase&);
  };
}

#endif
