#ifndef H_STATE_READ_SERVER_LIST
#define H_STATE_READ_SERVER_LIST

#include "../appState.h"

//convert string to int
#include <cstdlib>

//read file
#include <fstream>

//file existant include
#include <boost/filesystem.hpp>

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateReadServerList : public AppState
  {
  private:
    int findIndexOfChar(const std::string&, const char&);
    FluffyMultiplayer::AnAddress getIpAndPort(const std::string&, std::string, std::string);
  public:
    StateReadServerList();
    ~StateReadServerList();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
