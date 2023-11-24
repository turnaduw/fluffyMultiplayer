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
    FluffyMultiplayer::AppState* state3;
    int responseCodeAcceptor;
    int responseCodeAcceptor2;
    std::string text;
    std::string receivedData;
    std::string requestData;
    sf::Text timeouttxt;
    bool requestSent;
    int checkResponseCode(const std::string&);

    //login form
    FluffyMultiplayer::LoginFormData* loginData_ptr;

    //register form
    FluffyMultiplayer::RegisterFormData* registerData_ptr;

    //get lobby info by lobby id
    FluffyMultiplayer::LobbyData* lobbyData_ptr;

    //create lobby form
    FluffyMultiplayer::CreateLobbyFormData* createLobbyData_ptr;


  public:
    // StateWaitForResponse(std::string text,const std::string& request);
    StateWaitForResponse(std::string text,const std::string& request,
                         FluffyMultiplayer::AppState* retryState,
                         FluffyMultiplayer::AppState* acceptedState,
                         int responseCodeAccepts);
    StateWaitForResponse(std::string text,const std::string& request,
                        FluffyMultiplayer::AppState* retryState,
                        FluffyMultiplayer::AppState* acceptedState,
                        FluffyMultiplayer::AppState* acceptedState2,
                        int responseCodeAccepts,int responseCodeAccepts2);


    //for loginForm
    StateWaitForResponse(std::string _text,
      FluffyMultiplayer::AppState* retry,
      FluffyMultiplayer::LoginFormData loginFormdata,
      FluffyMultiplayer::AppState* banned,
      FluffyMultiplayer::AppState* success,
      int bannedCode,int successCode);

    //for reigsterForm
    StateWaitForResponse(std::string _text,
      FluffyMultiplayer::AppState* retry,
      FluffyMultiplayer::RegisterFormData registerFormData,
      FluffyMultiplayer::AppState* success,
      int successCode);

    //for (get lobby info by lobby id)
    StateWaitForResponse(std::string _text,
      FluffyMultiplayer::AppState* retry,
      FluffyMultiplayer::LobbyData _lobbyInfo,
      FluffyMultiplayer::AppState* notfoundState,
      int notfoundCode,
      FluffyMultiplayer::AppState* successState,
      int successCode);


    //for CreateLobbyForm
    StateWaitForResponse(std::string _text,
      FluffyMultiplayer::LobbyData _lobbyInfo,
      FluffyMultiplayer::AppState* retry,
      FluffyMultiplayer::AppState* notfoundState,
      int notfoundCode,
      FluffyMultiplayer::AppState* successState,
      int successCode);



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
