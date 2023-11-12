#include "include/app.h"
#include "include/config.h"
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <queue>
#include <iostream>
#include "include/dataType.h"

//read from file
#include <fstream>
using boost::asio::ip::udp;

namespace FluffyMultiplayer
{
  void sendData(udp::socket& socket,std::queue<std::string>& sendDataQueue, FluffyMultiplayer::AnAddress server, bool send_status=1)
  {
    while(true)
    {
      if(send_status && sendDataQueue.size()>=1)
      {
          udp::endpoint send_endpoint(server.ip, server.port);
          socket.send_to(boost::asio::buffer(sendDataQueue.front()), send_endpoint);
          sendDataQueue.pop();
      }
    }
  }

  void receiveData(udp::socket& socket,std::queue<std::string>& receivedDataQueue, FluffyMultiplayer::AnAddress server, bool receive_status=1)
  {
    while (true)
    {
      if(receive_status)
      {
        char receive_data[MC_RECEIVE_BUFFER];
        udp::endpoint senderEndpoint;
        size_t receive_length = socket.receive_from(boost::asio::buffer(receive_data), senderEndpoint);


        if(receive_length >=1 &&
            senderEndpoint.address() == server.ip &&
            senderEndpoint.port() == server.port)
        {
          std::string data = std::string(receive_data,receive_length);
          receivedDataQueue.push(data);
        }
      }
    }
  }
}


int main()
{
  try
  {
    //receive data from server
    std::queue<std::string> receivedDataQueue;
    std::queue<std::string> sendDataQueue;


    // app grapchic
    FluffyMultiplayer::App app;
    app.init();
    app.run(receivedDataQueue,sendDataQueue); //main loop is here


    //socket
    boost::asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), app.getAppPort()));



    boost::thread receive_thread
    (
      boost::bind
      (
        FluffyMultiplayer::receiveData,
        boost::ref(socket),
        boost::ref(receivedDataQueue),
        app.getServerAddress(),
        app.getReceiveDataStatus()
      )
    );

    boost::thread send_thread
    (
      boost::bind
      (
        FluffyMultiplayer::sendData,
        boost::ref(socket),
        boost::ref(sendDataQueue),
        app.getServerAddress(),
        app.getSendDataStatus()
      )
    );


    receive_thread.join();
    send_thread.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
