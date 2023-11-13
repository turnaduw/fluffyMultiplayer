#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateConnectingToServer::StateConnectingToServer()
  {

  }

  StateConnectingToServer::~StateConnectingToServer()
  {

  }

  int StateConnectingToServer::generateRandomNumber(int min=2500,int max=64000)
  {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = std::rand() % (max - min + 1) + min;
    return randomNumber;
  }

  bool StateConnectingToServer::isPortBusy(int port)
  {
    //lets check port is in use or not
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::socket socket(ioService);
    try
    {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        socket.open(endpoint.protocol());
        socket.bind(endpoint);
        // std::cout << "Port is available port = " << port << std::endl;
        return false;
    }
    catch (std::exception& e)
    {
        std::string errorMsg = e.what();
        if (errorMsg.find("bind: Address already in use") != std::string::npos)
        {
            // std::cerr << "Port is already in use port = " << port << std::endl;
            return true;
        }
        else
        {
            // std::cerr << "Exception: " << errorMsg << std::endl;
            return true;
        }
    }
  }


  void StateConnectingToServer::render(sf::RenderWindow& window)
  {
    // sf::Text centerText;
    // centerText.setText("reading server list from local files\nplease wait...");
    // setBasicBackground("bgState.png");
    // setBasicFont("default.ttf");
    sf::Sprite bgsp;
    sf::Texture bgtexture;
    bgtexture.loadFromFile("./assets/states/bgStateConnectToServer.png");
    bgsp.setTexture(bgtexture);

    // centerText.setFont(getBasicFont);
    window.draw(bgsp);
    // window.draw(getBgSprite());
    // window.draw(centerText);
  }


  FluffyMultiplayer::AppState* StateConnectingToServer::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
      int port = generateRandomNumber();
      bool portBusyResult = isPortBusy(port);
      if(portBusyResult)
      {
        // return new FluffyMultiplayer::StateFailedToBindPort;
      }
      else
      {
        app.setAppPort(static_cast<unsigned short>(port));
        sendDataQueue.push();....................................................
        return new FluffyMultiplayer::StateLoginForm;
      }
      return this;
  }


  FluffyMultiplayer::AppState* StateConnectingToServer::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
          {
              // return new FluffyMultiplayer::StateLoginForm;
          }
        }
        break;
    }
    return this;
  }
}
