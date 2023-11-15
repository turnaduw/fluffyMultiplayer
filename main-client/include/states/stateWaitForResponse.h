#ifndef H_STATE_WAIT_FOR_RESPONSE
#define H_STATE_WAIT_FOR_RESPONSE

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateWaitForResponse : public AppState
  {
  private:
    int timeoutCounter;
    FluffyMultiplayer::AppState* state1;
    FluffyMultiplayer::AppState* state2;
    int responseCodeAcceptor;
    std::string text;
    std::string data;
    bool buttonRetryPressed;
    sf::Text timeouttxt;
    int checkResponseCode(const std::string&);
  public:
    // StateWaitForResponse();
    StateWaitForResponse(std::string text, FluffyMultiplayer::AppState* retryState,
                         FluffyMultiplayer::AppState* acceptedState,
                         int responseCodeAccepts);
    ~StateWaitForResponse();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
