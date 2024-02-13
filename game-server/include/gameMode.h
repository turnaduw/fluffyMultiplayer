#ifndef H_GAMEMODE_CLASS
#define H_GAMEMODE_CLASS

#include "dataType.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration
  class GameMode
  {
    protected:
      int gameModeId;

    public:
      virtual void startGameMode()=0;
      virtual void addPlayerToGame(FluffyMultiplayer::App& app, int index)=0;
      virtual void removePlayerFromGame(FluffyMultiplayer::App& app, int playerId)=0;
      virtual int howManyPlayersAreInGame() const =0;
      virtual FluffyMultiplayer::GameMode* process(FluffyMultiplayer::App& app,
                            const FluffyMultiplayer::SocketReceiveData& currentItem,
                            const std::vector<std::string>& cData //to avoid re-process data just pass seperated data into gameMode
                            ) = 0;
  };
}

#endif
