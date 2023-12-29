#ifndef H_GAMEMODE_CLASS
#define H_GAMEMODE_CLASS

#include <string>
#include <queue>
#include "dataType.h"
#include "config.h"
#include "gameState.h"
#include "log.h"
#include "dataBase.h"
#include "dataSecurity.h"


namespace FluffyMultiplayer
{
  class GameMode
  {
    protected:
      int gameModeId;
      GameState* gs;

    public:
      virtual FluffyMultiplayer::GameMode* process(FluffyMultiplayer::SocketReceiveData& currentItem,
                                                   std::queue<FluffyMultiplayer::SocketSendData>& sendTextDataList,
                                                   FluffyMultiplayer::Log& log,
                                                   FluffyMultiplayer::DataBase& db,
                                                   FluffyMultiplayer::DataSecurity& ds) = 0;
  };
}

#endif
