#ifndef H_GAMEMODE_MENSCH_CLASS
#define H_GAMEMODE_MENSCH_CLASS

#include "../gameMode.h"

namespace FluffyMultiplayer
{
  class App;
  class GameMode;
  class GM_MENSCH : public GameMode
  {
    public:
      FluffyMultiplayer::GameMode* update(FluffyMultiplayer::App& app)
      {
        return this;
      }

      void render(sf::RenderWindow& window)
      {

      }

      FluffyMultiplayer::GameMode* eventHandle(FluffyMultiplayer::App& app, sf::Event& event)
      {
        return this;
      }

  };
}

#endif
