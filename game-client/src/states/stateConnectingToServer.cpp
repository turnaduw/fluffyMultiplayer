#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateConnectingToServer::StateConnectingToServer()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Sending connection request to the server\nplease wait..");
  }

  StateConnectingToServer::~StateConnectingToServer()
  {

  }

  void StateConnectingToServer::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateConnectingToServer::update(FluffyMultiplayer::App& app)
  {
    app.addSendText(REQUEST_CONNECT_TO_LOBBY);

    return new FluffyMultiplayer::StateWaitForResponse
    (
      "Connecting to the server\nplease wait..",
      this,
      std::vector<FluffyMultiplayer::AppState*>
          {
            new FluffyMultiplayer::StateConnectedToTheServer
          },
      std::vector<int>
        {
          RESPONSE_CONNECTION_ACCEPTED //success
        }
    );
  }


  FluffyMultiplayer::AppState* StateConnectingToServer::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    ////////////********************* exception just for test while server is no trunnign later remove this.
    switch(event.type)
    {
      //keyboard
        case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
          {
              return new FluffyMultiplayer::StateConnectedToTheServer;
          }
        }
        break;
    }
    return this;
  }
}
