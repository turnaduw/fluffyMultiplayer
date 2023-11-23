#ifndef H_STATE_FAILED
#define H_STATE_FAILED

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateFailed : public AppState
  {
  private:
    int outputStateCount;
    FluffyMultiplayer::AppState* state1;
    FluffyMultiplayer::AppState* state2;
    FluffyMultiplayer::AppState* state3;
    std::string* requestData;
    std::string text;
  public:
    StateFailed(std::string, FluffyMultiplayer::AppState* ok,std::string*);

    StateFailed(std::string,FluffyMultiplayer::AppState* retry,
                             FluffyMultiplayer::AppState* cancel_or_quit,std::string*);

    StateFailed(std::string,FluffyMultiplayer::AppState* retry,
                             FluffyMultiplayer::AppState* cancel_or_quit,
                             FluffyMultiplayer::AppState* skip,std::string*);

    ~StateFailed();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
