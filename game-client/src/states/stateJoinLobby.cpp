// #include "../../include/states.h"
//
// namespace FluffyMultiplayer
// {
//
//   int StateJoinLobby::findIndexOfDelimiter(const std::string& str, std::string c)
//   {
//     int index = str.find(c);
//     if (index != std::string::npos)
//       return index;
//     else
//       return -1;
//   }
//   int StateJoinLobby::convertToInt(const std::string& str)
//   {
//     const char* val = str.c_str();
//     return std::atoi(val);
//   }
//
//   FluffyMultiplayer::AnAddress StateJoinLobby::convertStringToAddress(std::string str)
//   {
//
//     int posEndIp = findIndexOfDelimiter(str,MC_IP_PORT_SEPARATOR);
//
//     FluffyMultiplayer::AnAddress tempAddress
//     {
//       boost::asio::ip::address::from_string( str.substr(0,posEndIp) ),
//       static_cast<unsigned short>( convertToInt( str.substr(posEndIp+1, str.length()-1) ) )
//     };
//
//     return tempAddress;
//   }
//
//   StateJoinLobby::StateJoinLobby(FluffyMultiplayer::AnAddress target_address)
//   {
//     closeButton.init("quit",200.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
//     backButton.init("back to home",400.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
//     gameServerAddress = target_address;
//     std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
//     initSimpleText(fontPath, "state joinLobby\n game has been launched.");
//     isGameLaunched=false;
//   }
//
//   StateJoinLobby::StateJoinLobby(std::string target_address)
//   {
//     closeButton.init("quit",200.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
//     backButton.init("back to home",400.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
//     //convert address from string to FluffyMultiplayer::AnAddress
//     gameServerAddress = convertStringToAddress(target_address);
//     std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
//     initSimpleText(fontPath, "state joinLobby\n game has been launched.");
//     isGameLaunched=false;
//   }
//
//   StateJoinLobby::StateJoinLobby()
//   {
//     closeButton.init("quit",200.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
//     backButton.init("back to home",400.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
//
//     isGameLaunched=false;
//   }
//
//   StateJoinLobby::~StateJoinLobby()
//   {
//
//   }
//
//   void StateJoinLobby::render(sf::RenderWindow& window)
//   {
//     window.draw(theText);
//     backButton.render(window);
//     closeButton.render(window);
//   }
//
//
//   FluffyMultiplayer::AppState* StateJoinLobby::update(FluffyMultiplayer::App& app,
//                     std::queue<std::string>& receiveDataQueue,
//                     std::queue<std::string>& sendDataQueue)
//
//   {
//     if(!isGameLaunched)
//     {
//       app.openGame(gameServerAddress);
//       isGameLaunched=true;
//     }
//     return this;
//   }
//
//
//   FluffyMultiplayer::AppState* StateJoinLobby::eventHandle(FluffyMultiplayer::App& app,
//                             sf::Event& event)
//   {
//     //mouse realtime
//     if(event.type == sf::Event::MouseButtonPressed)
//     {
//         mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));
//
//         if(backButton.getButtonBound().contains(mousePosition))
//         {
//           return new FluffyMultiplayer::StateMainPage;
//         }
//         else if(closeButton.getButtonBound().contains(mousePosition))
//         {
//           app.close();
//         }
//     }
//     return this;
//   }
// }
