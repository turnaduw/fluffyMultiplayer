#include <iostream>

//check file existant
#include <boost/filesystem.hpp>

//boost network
#include <boost/asio.hpp>
#include <boost/thread.hpp>
using boost::asio::ip::udp;


#include <queue>
#include <string>


#include "include/processData.h"


namespace FluffyMultiplayer
{

  void receiveData(udp::socket& socket,std::queue<FluffyMultiplayer::SocketDataQueue>& receivedDataQueue)
  {
    FluffyMultiplayer::ProcessData processD;
    FluffyMultiplayer::SocketDataQueue temp_queue;
    while (true)
    {
        char receive_data[MS_RECEIVE_BUFFER];
        udp::endpoint receive_endpoint;
        size_t receive_length = socket.receive_from(boost::asio::buffer(receive_data), receive_endpoint);


        if(receive_length >=1)
        {
          std::string data = std::string(receive_data,receive_length);
          temp_queue =
          {
            processD.separateCode(data),
            receive_endpoint.address(),
            receive_endpoint.port(),
            std::string(data[MS_DATA_START_AT_INDEX],data.length())
          };

          receivedDataQueue.push(temp_queue);
        }
    }
  }


}//namepsace closed


int main()
{
  try
  {
      //check database file existant then if needed create database tables or open database.
      FluffyMultiplayer::FluffyDatabase db(boost::filesystem::exists(MS_DATABASE_FILE));

      //init a Queue for received data from socket
      std::queue<FluffyMultiplayer::SocketDataQueue> receivedDataQueue;


      //socket bind
      boost::asio::io_context io_context;
      udp::socket socket(io_context, udp::endpoint(udp::v4(), MS_DEFAULT_PORT));
      boost::thread receive_thread(boost::bind(FluffyMultiplayer::receiveData, boost::ref(socket),boost::ref(receivedDataQueue)));


      //process obj
      FluffyMultiplayer::ProcessData process_data;

      while(true)
      {
        process_data.process(socket,receivedDataQueue,db);
      }



      // waits to finish
      receive_thread.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
