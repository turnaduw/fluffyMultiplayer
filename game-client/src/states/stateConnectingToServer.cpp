#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateConnectingToServer::StateConnectingToServer()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Sending connection request to the server\nplease wait..");
    req = std::to_string(MC_REQUEST_CONNECT) + MC_REQUEST_CLOSER;
  }

  StateConnectingToServer::~StateConnectingToServer()
  {

  }

  void StateConnectingToServer::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateConnectingToServer::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    if(app.getServerListCount()<=0)
    {
      return new FluffyMultiplayer::StateFailed("all servers tested, could not connect.",new FluffyMultiplayer::StateReadServerList, new FluffyMultiplayer::StateEnd,nullptr);
    }

    //enable status for receive and send
    socketVoice->enable();
    socketText->enable();



    //connect to text
    req = std::to_string(REQUEST_CONNECT_TO_LOBBY);
    return new FluffyMultiplayer::StateWaitForResponse
    (
      "Connecting to the server\nplease wait..",
      req,
      new FluffyMultiplayer::StateConnectedToTheServer,
      MS_RESPONSE_CONNECTION_ACCEPTED
    );
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
