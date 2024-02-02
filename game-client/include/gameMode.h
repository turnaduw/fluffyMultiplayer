#ifndef H_GAMEMODE_CLASS
#define H_GAMEMODE_CLASS

#include <string>
#include <queue>
#include "dataType.h"
#include "config.h"
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

    public:
      virtual FluffyMultiplayer::GameMode* update(FluffyMultiplayer::App&);
      virtual void render(sf::RenderWindow&)=0;
      virtual FluffyMultiplayer::GameMode* eventHandle(FluffyMultiplayer::App&,
                                          sf::Event&)=0;
  };
}

#endif
