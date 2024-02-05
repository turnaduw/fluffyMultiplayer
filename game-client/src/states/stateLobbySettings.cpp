// #include "../../include/states.h"
//
// namespace FluffyMultiplayer
// {
//   void StateLobbySettings::init()
//   {
//     inputFocus = &passwordInput;
//     maxPlayersList = MAX_PLAYER_LIST;
//     std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
//     initSimpleText(fontPath, "Lobby settings");
//     setSimpleTextPosition(150.0, 5.0);
//
//     passwordInput.init("","","Password:","enter password..",100.0, 100.0);
//
//     gameModeSpinBox.init("game mode:", GAME_MODE_LIST, 100.0, 200.0, sf::Color::Black, sf::Color::White, 22);
//     maxPlayersSpinBox.init("max players:", maxPlayersList, 100.0, 300.0, sf::Color::Black, sf::Color::White, 22);
//
//     ownerSpinBox.init("owner: ", players, 100.0, 200.0, sf::Color::Black, sf::Color::White, 22);
//
//     specterCheckBox.init("specter:", 100.0, 400.0, sf::Color::Black, sf::Color::White, 22);
//     voiceChatCheckBox.init("voice chat:", 100.0, 500.0, sf::Color::Black, sf::Color::White, 22);
//     textChatCheckBox.init("text chat:", 100.0, 600.0, sf::Color::Black, sf::Color::White, 22);
//
//     buttonSubmit.init("submit", 300.0,700.0, sf::Color::Black,sf::Color::Green, 60,30, 22);
//     buttonCancel.init("cancel", 100.0,700.0, sf::Color::Black,sf::Color::White, 60,30, 22);
//     buttonDeleteLobby.init("delete lobby", 600.0,700.0, sf::Color::Black,sf::Color::White, 60,30, 22);
//   }
//
//   int StateLobbySettings::convertStringToInt(const std::string& str)
//   {
//     const char* c = str.c_str();
//     return std::atoi(c);
//   }
//
//   // FluffyMultiplayer::AppState* StateLobbySettings::formFinishedResult(std::string cIdentity, bool isSubmit)
//   // {
//     // if(isSubmit)
//     // {
//       //get data from form and set into lobby data.
//       // lobbyData.clientIdentity = cIdentity;
//       // lobbyData.gameMode = gameModeSpinBox.getCurrentIndex();
//       // lobbyData.maxPlayers = convertStringToInt(maxPlayersList[maxPlayersSpinBox.getCurrentIndex()]);
//       // lobbyData.isTextChatAllowed = textChatCheckBox.getStatus();
//       // lobbyData.isVoiceChatAllowed = voiceChatCheckBox.getStatus();
//       // lobbyData.isSpecterAllowed = specterCheckBox.getStatus();
//       // lobbyData.password = passwordInput.getEnteredText();
//
//
//       // return new FluffyMultiplayer::StateWaitForResponse
//       // (
//         // "waiting for response from server\nto create lobby.\nplease wait..",
//         // this,
//         // lobbyData,
//         // new FluffyMultiplayer::StateFailed("cannot createlobby your account is limited\n", new FluffyMultiplayer::StateMainPage ,nullptr),
//         // MS_ERROR_FAILED_TO_LOBBY_CREATION_FORBIDDEN_FOR_YOU,
//         // new FluffyMultiplayer::StateJoinLobby(),
//         // MS_RESPONSE_SUCCESS_LOBBY_CREATED
//       // );
//     // }
//     //else
//     // return new FluffyMultiplayer::StateMainPage;
//   // }
//
//
//   StateLobbySettings::StateLobbySettings(std::vector<std::string> _players)
//   {
//     players=_players;
//     init();
//   }
//
//   StateLobbySettings::StateLobbySettings()
//   {
//     // init();
//
//     //set pastlobbyinfo into form.
//     // lobbyData = pastLobbyInfo;
//
//     // //apply past lobby info into form elements
//     // passwordInput.setText(lobbyData.password);
//     // passwordInput.setError(lobbyData.globalErrors);
//     // gameModeSpinBox.setItems(GAME_MODE_LIST,lobbyData.gameMode);
//     // maxPlayersSpinBox.setItems(maxPlayersList,lobbyData.maxPlayers);
//     // ownerSpinBox.setItems(players,0);
//     // specterCheckBox.setStatus(lobbyData.isSpecterAllowed);
//     // voiceChatCheckBox.setStatus(lobbyData.isVoiceChatAllowed);
//     // textChatCheckBox.setStatus(lobbyData.isTextChatAllowed);
//   }
//
//   StateLobbySettings::~StateLobbySettings()
//   {
//
//   }
//
//   void StateLobbySettings::render(sf::RenderWindow& window)
//   {
//     window.draw(theText);
//     passwordInput.render(window);
//     gameModeSpinBox.render(window);
//     maxPlayersSpinBox.render(window);
//     ownerSpinBox.render(window);
//     specterCheckBox.render(window);
//     voiceChatCheckBox.render(window);
//     textChatCheckBox.render(window);
//     buttonSubmit.render(window);
//     buttonCancel.render(window);
//     buttonDeleteLobby.render(window);
//   }
//
//
//   FluffyMultiplayer::AppState* StateLobbySettings::update(FluffyMultiplayer::App& app,
//                     std::queue<std::string>& receiveDataQueue,
//                     std::queue<std::string>& sendDataQueue)
//
//   {
//     return this;
//   }
//
//
//   FluffyMultiplayer::AppState* StateLobbySettings::eventHandle(FluffyMultiplayer::App& app,
//                             sf::Event& event)
//   {
//     //mouse realtime
//     if(event.type == sf::Event::MouseButtonPressed)
//     {
//         mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));
//
//         //this focus only works for passwordInput, when cliecked somewhere will be nowhere
//         inputFocus = nullptr;
//
//
//         /*
//           deceide delcre array in header to avoid clear each time
//           then call getter for bounds and assing then here.
//           can not assing anywhere else due to here we're using continues if elses
//         */
//         gameModeSpinBoxBounds = gameModeSpinBox.getBound();
//         maxPlayersSpinBoxBounds = maxPlayersSpinBox.getBound();
//         ownerSpinBoxBounds = ownerSpinBox.getBound();
//
//         //buttons
//         if(buttonSubmit.getButtonBound().contains(mousePosition))
//         {
//           // return formFinishedResult(app.getIdentity(),true);
//         }
//         else if(buttonCancel.getButtonBound().contains(mousePosition))
//         {
//           // return formFinishedResult(app.getIdentity(),false);
//         }
//         else if(buttonDeleteLobby.getButtonBound().contains(mousePosition))
//         {
//           // return formFinishedResult(app.getIdentity(),false);
//         }
//
//         //text fields
//         else if(passwordInput.getInputBoxBound().contains(mousePosition))
//         {
//           inputFocus = &passwordInput;
//         }
//
//         // SPIN BOXES
//         else if(gameModeSpinBoxBounds[0].contains(mousePosition)) //spin box game mode
//         {
//           gameModeSpinBox.spinUp();
//         }
//         else if(gameModeSpinBoxBounds[1].contains(mousePosition)) //spin box game mode
//         {
//           gameModeSpinBox.spinDown();
//         }
//         else if(maxPlayersSpinBoxBounds[0].contains(mousePosition)) //spin box max players
//         {
//           maxPlayersSpinBox.spinUp();
//         }
//         else if(maxPlayersSpinBoxBounds[1].contains(mousePosition)) //spin box max players
//         {
//           maxPlayersSpinBox.spinDown();
//         }
//         else if(ownerSpinBoxBounds[0].contains(mousePosition)) //spin box max players
//         {
//           ownerSpinBox.spinUp();
//         }
//         else if(ownerSpinBoxBounds[1].contains(mousePosition)) //spin box max players
//         {
//           ownerSpinBox.spinDown();
//         }
//
//         //check boxes
//         else if(specterCheckBox.getBound().contains(mousePosition))
//         {
//           specterCheckBox.clickedOnCheckBox();
//         }
//         else if(voiceChatCheckBox.getBound().contains(mousePosition))
//         {
//           voiceChatCheckBox.clickedOnCheckBox();
//         }
//         else if(textChatCheckBox.getBound().contains(mousePosition))
//         {
//           textChatCheckBox.clickedOnCheckBox();
//         }
//     }
//
//
//
//     switch(event.type)
//     {
//       //keyboard
//         case sf::Event::KeyPressed:
//         {
//           if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
//           {
//             // return formFinishedResult(app.getIdentity(),true);
//           }
//
//           if(event.key.code == sf::Keyboard::Backspace)
//           {
//             if(inputFocus!=nullptr)
//               inputFocus->removeFromText();
//           }
//         }break;
//
//         case sf::Event::TextEntered:
//         {
//           if (event.text.unicode < 128)
//           {
//             if(inputFocus != nullptr)
//               inputFocus->update(static_cast<char>(event.text.unicode));
//           }
//         }break;
//     }
//     return this;
//   }
// }
