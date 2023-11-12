#ifndef H_STATE_LOGIN_FORM
#define H_STATE_LOGIN_FORM

#include "../appState.h"
#include "../app.h"

namespace FluffyMultiplayer
{
  class StateReadServerList : public AppState
  {
  private:
    sf::Text centerText;
    std::string message;
    FluffyMultiplayer::AnAddress getIpAndPort(std::string data,std::string delimiter,std::string endline);

  public:
    StateLoginForm();
    ~StateLoginForm();

    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::Queue<std::string>&,
                      std::Queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
