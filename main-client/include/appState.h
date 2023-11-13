#ifndef H_APP_STATE_CLASS
#define H_APP_STATE_CLASS
#include "./config.h"
#include "./dataType.h"
#include "./app.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <queue>

namespace FluffyMultiplayer
{
  class App;
  class AppState
  {
  public:
    virtual void render(sf::RenderWindow&)=0;

    virtual FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&)=0;

    virtual FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                                        sf::Event&)=0;
  };
}
#endif
