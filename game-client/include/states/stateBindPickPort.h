#ifndef H_STATE_BIND_PICK_PORT
#define H_STATE_BIND_PICK_PORT

#include "../appState.h"

//random number
#include <cstdlib>
#include <ctime>

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateBindPickPort : public AppState
  {
  private:
    bool voiceBusy,textBusy;
    int maxTry;
    unsigned short genrate_random_number(int, int);
    bool isPortBusy(unsigned short);

  public:
    StateBindPickPort();
    ~StateBindPickPort();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#include "../appState.h"  // Include the full definition of AppState here

#endif
