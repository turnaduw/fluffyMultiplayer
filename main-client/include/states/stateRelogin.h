#ifndef H_STATE_RELOGIN
#define H_STATE_RELOGIN

#include "../appState.h"

//file existant include
#include <boost/filesystem.hpp>

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateRelogin : public AppState
  {
  private:
    std::string req;
    int findIndexOfValue(const std::string&, std::string);
    bool searchForIdentity(std::string&, const std::string&,std::string, std::string,std::string);
  public:
    StateRelogin();
    ~StateRelogin();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
