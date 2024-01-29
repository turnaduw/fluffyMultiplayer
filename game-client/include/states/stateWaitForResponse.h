#ifndef H_STATE_WAIT_FOR_RESPONSE
#define H_STATE_WAIT_FOR_RESPONSE

#include "../appState.h"
#include "../uiComponents/button.h"

//to get host id from computer
#include <unistd.h>

#include <vector>
#include <string>

//for notification system
#include <queue>
#include "../dataType.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateWaitForResponse : public AppState
  {
  private:
    int timeoutCounter;
    FluffyMultiplayer::AppState* retryState;
    std::vector<FluffyMultiplayer::AppState*> states;
    std::vector<int> responseCodes;

    std::string text;
    FluffyMultiplayer::SocketReceiveData receivedData;
    sf::Text timeouttxt;
    int checkResponseCode(const std::string&, std::queue<FluffyMultiplayer::NotificationData>&);
    std::string getResponseCodeMessage(const int&);

    std::string getIdentityFromResponsedData(const std::string& _data,std::string delimter,std::string closer);
    std::string getServerAddressFromResponseData(const std::string& _data,std::string delimiter,std::string closer);
    std::string getLobbyFromResponseData(const std::string& _data,std::string delimiter,std::string closer);

    FluffyMultiplayer::Button buttonRetry;

    //mouse event handel variable to delecre once, not per loop delcre
    sf::Vector2f mousePosition;

  public:
    // StateWaitForResponse(std::string text,const std::string& request);


    StateWaitForResponse(std::string text,
                        FluffyMultiplayer::AppState* retryState,
                        std::vector<FluffyMultiplayer::AppState*> states,
                        std::vector<int> responsedCodes);


    ~StateWaitForResponse();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
