// #ifndef H_STATE_WAIT_FOR_RESPONSE
// #define H_STATE_WAIT_FOR_RESPONSE
//
// #include "../appState.h"
// #include "../uiComponents/button.h"
//
// //to get host id from computer
// #include <unistd.h>
//
// #include <vector>
// #include <string>
//
// //for notification system
// #include <queue>
// #include "../dataType.h"
//
// namespace FluffyMultiplayer
// {
//   class App; // Forward declaration of App class
//   class AppState; // Forward declaration of AppState class
//
//   class StateWaitForResponse : public AppState
//   {
//   private:
//     int timeoutCounter;
//     FluffyMultiplayer::AppState* state1;
//     std::vector<FluffyMultiplayer::AppState*> state2;
//     FluffyMultiplayer::AppState* state3;
//     std::vector<int> responseCodeAcceptor;
//     int responseCodeAcceptor2;
//     std::string text;
//     std::string receivedData;
//     std::string requestData;
//     sf::Text timeouttxt;
//     bool requestSent;
//     int checkResponseCode(const std::string&, std::queue<FluffyMultiplayer::NotificationData>&);
//     std::string getResponseCodeMessage(const int&);
//
//     std::string getIdentityFromResponsedData(const std::string& _data,std::string delimter,std::string closer);
//     std::string getServerAddressFromResponseData(const std::string& _data,std::string delimiter,std::string closer);
//     std::string getLobbyFromResponseData(const std::string& _data,std::string delimiter,std::string closer);
//
//     //get lobby info by lobby id
//     FluffyMultiplayer::LobbyData* lobbyData_ptr;
//
//     FluffyMultiplayer::Button buttonRetry;
//
//     //mouse event handel variable to delecre once, not per loop delcre
//     sf::Vector2f mousePosition;
//
//   public:
//     // StateWaitForResponse(std::string text,const std::string& request);
//     StateWaitForResponse(std::string text,const std::string& request,
//                          FluffyMultiplayer::AppState* retryState,
//                          FluffyMultiplayer::AppState* acceptedState,
//                          int responseCodeAccepts);
//     StateWaitForResponse(std::string text,const std::string& request,
//                         FluffyMultiplayer::AppState* retryState,
//                         FluffyMultiplayer::AppState* acceptedState,
//                         FluffyMultiplayer::AppState* acceptedState2,
//                         int responseCodeAccepts,int responseCodeAccepts2);
//
//
//     ~StateWaitForResponse();
//     void render(sf::RenderWindow&);
//     FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
//     FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
//                               sf::Event&);
//   };
// }
//
// #endif
