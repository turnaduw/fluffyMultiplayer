#include <iostream>

//check file existant
#include <boost/filesystem.hpp>

//boost network
#include <boost/asio.hpp>
#include <boost/thread.hpp>
using boost::asio::ip::udp;


#include <vector>
#include <string>


#include "include/config.h" //access to MS_RECEIVE_BUFFER, MS_DATABASE_FILE , MS_DEFAULT_PORT,MS_DATA_START_AT_INDEX
#include "include/dataTypes.h" //access to struct SocketDataStack

#include "include/processData.h"


namespace FluffyMultiplayer
{

  void receiveData(udp::socket& socket,std::vector<FluffyMultiplayer::SocketDataStack>& receivedDataStack)
  {
    while (true)
    {
        char receive_data[MS_RECEIVE_BUFFER];
        udp::endpoint receive_endpoint;
        size_t receive_length = socket.receive_from(boost::asio::buffer(receive_data), receive_endpoint);


        if(receive_length >=1)
        {
          std::string data = std::string(receive_data,receive_length);
          receivedDataStack.push_back
          (
            FluffyMultiplayer::ProcessData::separateCode(data),
            receive_endpoint.address(),
            receive_endpoint.port(),
            std::string(data[MS_DATA_START_AT_INDEX],data.length())
          );
        }
    }
  }


}//namepsace closed


int main()
{
  try
  {
      //check database file existant then if needed create database tables or open database.
      FluffyMultiplayer::FluffyDatabase dB(boost::filesystem::exists(MS_DATABASE_FILE));

      //init a stack for received data from socket
      std::vector<FluffyMultiplayer::SocketDataStack> receivedDataStack;


      //socket bind
      boost::asio::io_context io_context;
      udp::socket socket(io_context, udp::endpoint(udp::v4(), MS_DEFAULT_PORT));
      boost::thread receive_thread(boost::bind(FluffyMultiplayer::receiveData, boost::ref(socket),boost::ref(receivedDataStack)));


      //process obj
      FluffyMultiplayer::ProcessData process_data;

      process_data.process(socket,receivedDataStack);



      // waits to finish
      receive_thread.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
