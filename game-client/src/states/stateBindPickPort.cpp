#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateBindPickPort::StateBindPickPort()
  {
    maxTry=0;
    voiceBusy = false;
    textBusy = false;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "pick and binding port\nplease wait...");
  }

  StateBindPickPort::~StateBindPickPort()
  {

  }

  unsigned short StateBindPickPort::genrate_random_number(int min=2500, int max=64000)
  {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = std::rand() % (max - min + 1) + min;
    return randomNumber;
  }

  void StateBindPickPort::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }

  bool StateBindPickPort::isPortBusy(unsigned short _port=MC_DEFAULT_PORT)
  {
    //lets check port is in use or not
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::socket socket(ioService);
    try
    {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), _port);
        socket.open(endpoint.protocol());
        socket.bind(endpoint);
        // std::cout << "Port is available port = " << _port << std::endl;
        return false;
    }
    catch (std::exception& e)
    {
        std::string errorMsg = e.what();
        if (errorMsg.find("bind: Address already in use") != std::string::npos)
        {
            // std::cerr << "Port is already in use port = " << _port << std::endl;
            return true;
        }
        else
        {
            // std::cerr << "Exception: " << errorMsg << std::endl;
            return true;
        }
    }
  }

  FluffyMultiplayer::AppState* StateBindPickPort::update(FluffyMultiplayer::App& app)
  {

    //limit tries
    //try to pick port randomly and bind into sockets
    while(maxTry<=MC_STATE_BIND_PICK_PORT_TRY_COUNT)
    {
      maxTry++;

      //set port for text socket
      app.socketText->setPort(genrate_random_number(3000,64000));
      textBusy = isPortBusy(app.socketText->getPort());

      //set port for voice socket
      app.socketVoice->setPort(genrate_random_number(3000,64000)+1);
      voiceBusy = isPortBusy(app.socketVoice->getPort());
      if(voiceBusy==false && textBusy==false)
      {
        //enable status for receive and send
        app.socketVoice->enable();
        app.socketText->enable();

        return new FluffyMultiplayer::StateConnectingToServer;
      }
    }

    return new FluffyMultiplayer::StateFailed("Bind or Pick port for client.",
                    new FluffyMultiplayer::StateBindPickPort,
                    new FluffyMultiplayer::StateEnd,nullptr);
  }


  FluffyMultiplayer::AppState* StateBindPickPort::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
