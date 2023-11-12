#include "../../include/states/StateReadServerList.h"

namespace FluffyMultiplayer
{
  StateReadServerList::StateReadServerList()
  {

  }

  void StateReadServerList::render(sf::RenderWindow& window)
  {
    sf::Text centerText;
    centerText.setText("reading server list from local files\nplease wait...");
    setBasicBackground("stateReadServerListBg.png");
    setBasicFont("default.ttf");

    centerText.setFont(getBasicFont);

    window.draw(getBgSprite());
    window.draw(centerText);
  }


  FluffyMultiplayer::AppState* StateReadServerList::update(FluffyMultiplayer::App& app,
                    std::Queue<std::string>& receiveDataQueue,
                    std::Queue<std::string>& sendDataQueue)

  {
        std::string line;
        std::ifstream serverListFile (CLIENT_LOCAL_SERVER_LIST_FILE);
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
            return new FluffyMultiplayer::StatePickPort();
          }
        }
        else
        {
          std::cout << "Unable to open file server list.\n";
        }
      return new FluffyMultiplayer::CouldNotReadServerList();
  }


  FluffyMultiplayer::AppState* StateReadServerList::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event&)
  {
    //..
    return this;
  }
}
