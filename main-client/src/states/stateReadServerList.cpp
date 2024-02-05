#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateReadServerList::StateReadServerList()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Reading server list file\nplease wait...");
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
    boost::asio::ip::address ip = boost::asio::ip::address::from_string(MC_SERVER_DEFAULT_IP);
    unsigned short port = MC_SERVER_DEFAULT_PORT;

    //to check some invalid ip's like 0.0.0.0
    std::vector<std::string> server_ip_not_allowed = MC_SERVER_IP_NOT_ALLOWED_LIST;
    FluffyMultiplayer::AnAddress tempAddress = {ip,port};

    int indexSeparator = findIndexOfChar( line, static_cast<char>(separator[0]) );
    int indexEndline = findIndexOfChar ( line, static_cast<char>(endline[0]) );

    //convert line into ip and port but type is string
    std::string ip_str = line.substr(0,indexSeparator);
    for(auto element : server_ip_not_allowed)
    {
      if(element == ip_str)
      {
        std::cout << "from serverlist.txt server ip is not allowed so selected is default: " << ip << ":" << port << std::endl;
        return tempAddress;
      }
    }


    std::string port_str = line.substr(indexSeparator+1, indexEndline);

    //to avoid return invalid ip or port instead return a default values
    if(ip_str.length() >= 7 && port_str.length() >= 4)
    {
      //convert port into unsigned short
      const char* _port = port_str.c_str();
      port = static_cast<unsigned short>( std::atoi(_port) );

      //convert string ip into udp ip
      ip = boost::asio::ip::address::from_string(ip_str);
    }
    tempAddress = {ip,port};
    return tempAddress;
  }

  void StateReadServerList::render(sf::RenderWindow& window)
  {
    setSimpleTextPosition((window.getSize().x/2)-INITAL_TEXT_ON_SCREEN_PADDING_X,
                          (window.getSize().y/2)-INITAL_TEXT_ON_SCREEN_PADDING_Y);
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateReadServerList::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
        std::string filename = CLIENT_LOCAL_SERVER_LIST_FILE;
        if(boost::filesystem::exists(filename))
        {
          std::string line;
          std::ifstream serverListFile (filename);
          if (serverListFile.is_open())
          {
            while ( getline (serverListFile,line) )
            {
              //sperate ip and port and add it into list
              app.addServer( getIpAndPort(line,MC_IP_PORT_SEPARATOR,MC_IP_PORT_ENDLINE) );
            }
            serverListFile.close();
            if(app.getServerListCount()>=1)
            {
              return new FluffyMultiplayer::StateBindPickPort;
            }
          }
        }
      return new FluffyMultiplayer::StateFailed("Unable to open/read file: serverlist\n", this , new FluffyMultiplayer::StateEnd,nullptr);
  }


  FluffyMultiplayer::AppState* StateReadServerList::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
