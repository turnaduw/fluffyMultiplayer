#include "include/app.h"
#include "include/config.h"
#include <boost/thread.hpp>
#include <queue>
#include <iostream>
#include "include/dataType.h"


#include <boost/asio.hpp>
using boost::asio::ip::udp;

//read from file
#include <fstream>


#include "include/dataSecurity.h"


namespace FluffyMultiplayer
{
  void sendData(udp::socket& socket,std::queue<std::string>& sendDataQueue, const FluffyMultiplayer::App& app)
  {
    FluffyMultiplayer::DataSecurity dSecurity;
    std::string data;
    while(true)
    {
      FluffyMultiplayer::AnAddress server = app.getServerAddress();
      if(app.getSendDataStatus() && sendDataQueue.size()>=1)
      {
          data = sendDataQueue.front();
          dSecurity.encryptData(data);
          udp::endpoint send_endpoint(server.ip, server.port);
          socket.send_to(boost::asio::buffer(data), send_endpoint);
          sendDataQueue.pop();
      }
    }
  }

  void receiveData(udp::socket& socket,std::queue<std::string>& receivedDataQueue, const FluffyMultiplayer::App& app)
  {
    FluffyMultiplayer::DataSecurity dSecurity;
    std::string data;
    while (true)
    {
      FluffyMultiplayer::AnAddress server = app.getServerAddress();
      if(app.getReceiveDataStatus())
      {
        char receive_data[MC_RECEIVE_BUFFER];
        udp::endpoint senderEndpoint;
        size_t receive_length = socket.receive_from(boost::asio::buffer(receive_data), senderEndpoint);


        if(receive_length >=1 &&
            senderEndpoint.address() == server.ip &&
            senderEndpoint.port() == server.port)
        {
          data = std::string(receive_data,receive_length);
          dSecurity.decryptData(data);
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
        boost::ref(app)
      )
    );

    boost::thread send_thread
    (
      boost::bind
      (
        FluffyMultiplayer::sendData,
        boost::ref(socket),
        boost::ref(sendDataQueue),
        boost::ref(app)
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
