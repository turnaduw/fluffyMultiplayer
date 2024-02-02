#ifndef H_GAMEMODE_CLASS
#define H_GAMEMODE_CLASS

#include <string>
#include <queue>
#include "dataType.h"
#include "config.h"
#include "log.h"

namespace FluffyMultiplayer
{
  class GameMode
  {
    protected:
      int gameModeId;
      // currentGameMode=nullptr;

      // if(currentGameMode!=nullptr) //draw gameMode grpahical entities (z:1)
        // currentGameMode->render(window);
      // if(currentGameMode!=nullptr)
       // currentGameMode = currentGameMode->update(app);
      // currentGameMode = currentGameMode->eventHandle(app,event);
    public:
      virtual FluffyMultiplayer::GameMode* update(FluffyMultiplayer::Log& log,
                                                  std::queue<FluffyMultiplayer::SocketSendData>& sendList,
                                                  FluffyMultiplayer::SocketReceiveData& currentItem);
      virtual void render(sf::RenderWindow&)=0;
      virtual FluffyMultiplayer::GameMode* eventHandle(FluffyMultiplayer::App&,
                                          sf::Event&)=0;
  };
}

#endif
