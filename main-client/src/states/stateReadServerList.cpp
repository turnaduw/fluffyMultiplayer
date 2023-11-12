#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateReadServerList::StateReadServerList()
  {

  }

  StateReadServerList::~StateReadServerList()
  {

  }

  int StateReadServerList::findIndexOfChar(const std::string& str, const char& c)
  {
    int index = str.find(c);
    if (index != std::string::npos)
      return index;
    else
      return -1;
  }

  FluffyMultiplayer::AnAddress StateReadServerList::getIpAndPort(const std::string& line, std::string separator, std::string endline)
  {
    int indexSeparator = findIndexOfChar( line, static_cast<char>(separator[0]) );
    int indexEndline = findIndexOfChar ( line, static_cast<char>(endline[0]) );

    //convert line into ip and port but type is string
    std::string ip_str = line.substr(0,indexSeparator); //-1 because of separator charecter
    std::string port_str = line.substr(indexSeparator+1, indexEndline); //-2 is for endline charecter

    //convert port into unsigned short
    const char* _port = port_str.c_str();
    unsigned short port = static_cast<unsigned short>( std::atoi(_port) );

    //convert string ip into udp ip
    boost::asio::ip::address ip = boost::asio::ip::address::from_string(ip_str);
    FluffyMultiplayer::AnAddress tempAddress = {ip,port};
    return tempAddress;
  }

  void StateReadServerList::render(sf::RenderWindow& window)
  {
    // sf::Text centerText;
    // centerText.setText("reading server list from local files\nplease wait...");
    // setBasicBackground("bgState.png");
    // setBasicFont("default.ttf");
    sf::Sprite bgsp;
    sf::Texture bgtexture;
    bgtexture.loadFromFile("./assets/states/bgState.png");
    bgsp.setTexture(bgtexture);

    // centerText.setFont(getBasicFont);
    window.draw(bgsp);
    // window.draw(getBgSprite());
    // window.draw(centerText);
  }


  FluffyMultiplayer::AppState* StateReadServerList::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
        std::string line;
        std::string filename = CLIENT_LOCAL_SERVER_LIST_FILE;
        std::ifstream serverListFile (filename);
        if (serverListFile.is_open())
        {
          while ( getline (serverListFile,line) )
          {
            std::cout << line << '\n';

            //sperate ip and port and add it into list
            app.addServer( getIpAndPort(line,MC_IP_PORT_SEPARATOR,MC_IP_PORT_ENDLINE) );
          }
          serverListFile.close();
          if(app.getServerListCount()>=1)
          {
            return new FluffyMultiplayer::StateConnectToServer;
          }
        }
        else
        {
          std::cout << "Unable to open file server list.\n";
        }
      return this;
  }


  FluffyMultiplayer::AppState* StateReadServerList::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
          {
              return new FluffyMultiplayer::StateLoginForm;
          }
        }
        break;
    }
    return this;
  }
}
