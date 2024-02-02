#ifndef H_GAMEMODE_CLASS
#define H_GAMEMODE_CLASS

#include <string>
#include <queue>
#include <SFML/Graphics.hpp>
#include "dataType.h"
#include "config.h"
#include "log.h"

namespace FluffyMultiplayer
{
  class GameMode
  {
    protected:
      int gameModeId;

    public:
      virtual FluffyMultiplayer::GameMode* update(std::queue<FluffyMultiplayer::SocketSendData>& sendList,
                                                  FluffyMultiplayer::SocketReceiveData& currentItem)=0;
      virtual void render(sf::RenderWindow& window)=0;
      virtual FluffyMultiplayer::GameMode* eventHandle(sf::RenderWindow& window,sf::Event& event)=0;
  };
}

#endif
