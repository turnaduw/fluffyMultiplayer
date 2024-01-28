// #include "../../include/states.h"
//
// namespace FluffyMultiplayer
// {
//   StateConnectingToServer::StateConnectingToServer()
//   {
//     std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
//     initSimpleText(fontPath, "Sending connection request to the server\nplease wait..");
//     request_sent=false;
//   }
//
//   StateConnectingToServer::~StateConnectingToServer()
//   {
//
//   }
//
//   void StateConnectingToServer::render(sf::RenderWindow& window)
//   {
//     window.draw(theText);
//   }
//
//
//   FluffyMultiplayer::AppState* StateConnectingToServer::update(FluffyMultiplayer::App& app)
//   {
//     if(!request_sent)
//     {
//         app.addSendText(REQUEST_CONNECT_TO_LOBBY);
//         request_sent=true;
//     }
//
//     return new FluffyMultiplayer::StateWaitForResponse
//     (
//       true, //means by socket text
//       "Connecting to the server\nplease wait..",
//       req,
//       new FluffyMultiplayer::StateConnectedToTheServer,
//       MS_RESPONSE_CONNECTION_ACCEPTED
//     );
//   }
//
//
//   FluffyMultiplayer::AppState* StateConnectingToServer::eventHandle(FluffyMultiplayer::App& app,
//                             sf::Event& event)
//   {
//     switch(event.type)
//     {
//       //keyboard
//         case sf::Event::KeyPressed:
//         {
//           if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
//           {
//               // return new FluffyMultiplayer::StateLoginForm;
//           }
//         }
//         break;
//     }
//     return this;
//   }
// }
