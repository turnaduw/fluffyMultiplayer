#include "../../include/states/stateReadServerList.h"

namespace FluffyMultiplayer
{
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
      //   std::string line;
      //   std::ifstream serverListFile (CLIENT_LOCAL_SERVER_LIST_FILE);
      //   if (serverListFile.is_open())
      //   {
      //     while ( getline (serverListFile,line) )
      //     {
      //       std::cout << line << '\n';
      //
      //       //sperate ip and port and add it into list
      //       app.addServer( getIpAndPort(line,MC_IP_PORT_SEPARATOR,MC_IP_PORT_ENDLINE) );
      //     }
      //     serverListFile.close();
      //     if(app.getServerListCount()>=1)
      //     {
      //       return new FluffyMultiplayer::StatePickPort();
      //     }
      //   }
      //   else
      //   {
      //     std::cout << "Unable to open file server list.\n";
      //   }
      // return new FluffyMultiplayer::CouldNotReadServerList();
      return this;
  }


  FluffyMultiplayer::AppState* StateReadServerList::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event&)
  {
    //..
    return this;
  }
}
