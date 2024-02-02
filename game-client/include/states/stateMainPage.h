#ifndef H_STATE_MAIN_PAGE
#define H_STATE_MAIN_PAGE

#include "../appState.h"

#include "../uiComponents/playerList.h"
#include "../uiComponents/text.h"

#include "../config.h"
#include <array>
#include <vector>
#include <string>

//random number
#include <cstdlib>
#include <ctime>

#include "../gameModes.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class
  class StateMainPage : public AppState
  {
  private:
    //userinterface
    std::array<FluffyMultiplayer::PlayerList,MAX_PLAYERS_IN_LOBBY> playerList;
    FluffyMultiplayer::Text testk;
    FluffyMultiplayer::PlayerList playerlisttest;
    FluffyMultiplayer::PlayerList* playerlistest2;
    FluffyMultiplayer::PictureButton testPictureButton;
    // FluffyMultiplayer::GameMode* currentGameMode;

    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;


  public:
    StateMainPage(FluffyMultiplayer::App&);
    ~StateMainPage();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
