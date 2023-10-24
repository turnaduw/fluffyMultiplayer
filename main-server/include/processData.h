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


//socket
#include <boost/asio.hpp>


namespace FluffyMultiplayer
{
  class ProcessData
  {
  public:
    ProcessData();
    ~processData();

    int separateCode(const std::string&);
    void process(udp::socket&, std::vector<FluffyMultiplayer::SocketDataStack>&);
  };
}

#endif
