#ifndef H_GAMEMODE_CLASS
#define H_GAMEMODE_CLASS

#include <string>
#include "dataType.h"
#include "gameState.h"

namespace FluffyMultiplayer
{
  class GameMode
  {
    protected:
      int gameModeId;
      GameState* gs;

    public:
      virtual GameMode* process(FluffyMultiplayer::SocketReceiveData) = 0;
  };
}

#endif
