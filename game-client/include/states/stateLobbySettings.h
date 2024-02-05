// #ifndef H_STATE_LOBBY_SETTINGS_FORM
// #define H_STATE_LOBBY_SETTINGS_FORM
//
// #include "../appState.h"
// #include "../uiComponents/textInput.h"
// #include "../uiComponents/button.h"
// #include "../uiComponents/checkBox.h"
// #include "../uiComponents/spinBox.h"
//
// //convert string to int
// #include <cstdlib>
//
// namespace FluffyMultiplayer
// {
//   class App; // Forward declaration of App class
//   class AppState; // Forward declaration of AppState class
//
//   class StateLobbySettings : public AppState
//   {
//   private:
//     FluffyMultiplayer::LobbyData lobby;
//
//     //focus
//     FluffyMultiplayer::TextInput* inputFocus;
//
//     //text inputs
//     FluffyMultiplayer::TextInput passwordInput;
//
//     //spinboxes
//     FluffyMultiplayer::SpinBox gameModeSpinBox;
//     FluffyMultiplayer::SpinBox maxPlayersSpinBox;
//     FluffyMultiplayer::SpinBox ownerSpinBox;
//
//
//     //check boxes
//     FluffyMultiplayer::CheckBox specterCheckBox;
//     FluffyMultiplayer::CheckBox voiceChatCheckBox;
//     FluffyMultiplayer::CheckBox textChatCheckBox;
//
//     //buttons
//     FluffyMultiplayer::Button buttonSubmit;
//     FluffyMultiplayer::Button buttonCancel;
//     FluffyMultiplayer::Button buttonDeleteLobby;
//
//     //players list to list for owner spinbox
//     std::vector<std::string> players;
//
//     //to avoid duplicate return code while calling them from event mouse, keyboard
//     // FluffyMultiplayer::AppState* formFinishedResult(std::string clientIdentity, bool isSubmit);
//     std::vector<std::string> maxPlayersList;
//     int convertStringToInt(const std::string&);
//
//     //mouse event handel variable to delecre once, not per loop delcre
//     sf::Vector2f mousePosition;
//     std::array<sf::FloatRect,2> gameModeSpinBoxBounds;
//     std::array<sf::FloatRect,2> maxPlayersSpinBoxBounds;
//     std::array<sf::FloatRect,2> ownerSpinBoxBounds;
//
//     void init();
//
//   public:
//     StateLobbySettings(std::vector<std::string> _players);
//     StateLobbySettings();
//     ~StateLobbySettings();
//     void render(sf::RenderWindow&);
//     FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&);
//     FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
//                               sf::Event&);
//   };
// }
//
// #endif
