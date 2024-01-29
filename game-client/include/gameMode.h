#ifndef H_GAMEMODE_CLASS
#define H_GAMEMODE_CLASS

#include <string>
#include <queue>
#include "dataType.h"
#include "config.h"
#include "gameState.h"
#include "log.h"
#include "dataSecurity.h"
#include "app.h"

namespace FluffyMultiplayer
{
  class App;
  class GameMode
  {
    protected:
      int gameModeId;
      GameState* gs;

    public:
      virtual FluffyMultiplayer::GameMode* update(FluffyMultiplayer::App&);

      virtual void render(sf::RenderWindow&)=0;
      virtual FluffyMultiplayer::GameMode* eventHandle(FluffyMultiplayer::App&,
                                          sf::Event&)=0;
      virtual FluffyMultiplayer::GameMode* process(FluffyMultiplayer::SocketReceiveData& currentItem,
                                                   std::queue<FluffyMultiplayer::SocketSendData>& sendTextDataList,
                                                   FluffyMultiplayer::Log& log,
                                                   FluffyMultiplayer::DataSecurity& ds) = 0;
  };
}

#endif
