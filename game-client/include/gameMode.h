#ifndef H_GAMEMODE_CLASS
#define H_GAMEMODE_CLASS

#include <boost/thread.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <queue>
#include <vector>
#include "dataType.h"
#include "config.h"
#include "log.h"

//to define for passing
#include "./uiComponents/playerList.h"




// ------- requests 501->700


// ------- responses 701->999



namespace FluffyMultiplayer
{
  class GameMode
  {
    protected:
      int gameModeId;

      //a flag to turn on when game started,  App will render game in some case gameMode before start has bad position of elemnts
      //so this flag make game mode to avoid that render before,
      bool gameStarted;

    public:
      bool getGameStarted() const
      {
        return gameStarted;
      }
      virtual void updatePlayersInGame(std::vector<std::string>& receivedPlayersInGameInfo,int myId)=0;
      virtual FluffyMultiplayer::GameMode* update(int& currentItemCode, std::vector<std::string>& cData)=0;
      virtual void render(sf::RenderWindow& window)=0;
      virtual FluffyMultiplayer::GameMode* eventHandle(sf::RenderWindow& window,sf::Event& event,
                                        std::queue<FluffyMultiplayer::SocketSendData>& sendList,
                                        boost::mutex& sendMutex)=0;
  };
}

#endif
