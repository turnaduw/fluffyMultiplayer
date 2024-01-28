// #ifndef H_STATE_FAILED
// #define H_STATE_FAILED
//
// #include "../appState.h"
// #include "../uiComponents/button.h"
// #include <array>
//
// namespace FluffyMultiplayer
// {
//   class App; // Forward declaration of App class
//   class AppState; // Forward declaration of AppState class
//
//   class StateFailed : public AppState
//   {
//   private:
//     int outputStateCount;
//     FluffyMultiplayer::AppState* state1;
//     FluffyMultiplayer::AppState* state2;
//     FluffyMultiplayer::AppState* state3;
//     std::string* requestData;
//     std::string text;
//
//     //ui
//     std::array<FluffyMultiplayer::Button,3> buttons;
//     //mouse event handel variable to delecre once, not per loop delcre
//     sf::Vector2f mousePosition;
//
//   public:
//     StateFailed(std::string, FluffyMultiplayer::AppState* ok,std::string*);
//
//     StateFailed(std::string,FluffyMultiplayer::AppState* retry,
//                              FluffyMultiplayer::AppState* cancel_or_quit,std::string*);
//
//     StateFailed(std::string,FluffyMultiplayer::AppState* retry,
//                              FluffyMultiplayer::AppState* cancel_or_quit,
//                              FluffyMultiplayer::AppState* skip,std::string*);
//
//     ~StateFailed();
//     void render(sf::RenderWindow&);
//     FluffyMultiplayer::AppState* update(FluffyMultiplayer::App);
//     FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
//                               sf::Event&);
//   };
// }
//
// #endif
