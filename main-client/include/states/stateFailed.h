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
  public:
    StateFailed(std::string, FluffyMultiplayer::AppState* ok);

    StateFailed(std::string, FluffyMultiplayer::AppState* retry,
                             FluffyMultiplayer::AppState* cancel_or_quit);

    StateFailed(std::string, FluffyMultiplayer::AppState* retry,
                             FluffyMultiplayer::AppState* cancel_or_quit,
                             FluffyMultiplayer::AppState* etc);

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
