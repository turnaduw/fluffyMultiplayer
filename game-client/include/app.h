#ifndef H_APP_CLASS
#define H_APP_CLASS

#include "config.h"
#include "udpSocket.h"
#include "dataSecurity.h"
#include "dataType.h"
#include "log.h"

#include <SFML/Graphics.hpp>

#include <boost/thread.hpp>

#include <boost/asio.hpp>
using boost::asio::ip::udp;

#include <queue>
#include <array>


namespace FluffyMultiplayer
{
    class App
    {
      private:
        int myId; //player id for this client
        std::string identity;
        FluffyMultiplayer::Log log;

        FluffyMultiplayer::AnAddress serverAddress;
        std::vector<FluffyMultiplayer::Player> playersInLobby;

        FluffyMultiplayer::VoiceChat voiceChat;
        FluffyMultiplayer::AppState* currentState;
        FluffyMultiplayer::GameMode* currentGameMode;
        std::queue<FluffyMultiplayer::SocketReceiveData> receivedTextDataList;
        std::queue<FluffyMultiplayer::SocketReceiveData> receivedVoiceDataList;
        std::queue<FluffyMultiplayer::SocketSendData> sendVoiceDataList;
        std::queue<FluffyMultiplayer::SocketSendData> sendTextDataList;

        //socket things
        boost::asio::io_context ioContextVoice;
        FluffyMultiplayer::UdpSocket socketVoice;

        boost::asio::io_context ioContextText;
        FluffyMultiplayer::UdpSocket socketText;


      public:
        boost::thread receive_thread;
        boost::thread send_thread;
        sf::RenderWindow window;

        std::queue<FluffyMultiplayer::NotificationData> notificationQueue;
        FluffyMultiplayer::NotificationBox notificationBox;

        //mouse event handel variable to delecre once, not per loop delcre
        sf::Vector2f mousePosition;



        void init();
        void run();
        void close();

        App() :
            window(sf::VideoMode
                (WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_TITLE,WINDOW_STYLE))
        {

        }

        ~App()
        {
          receive_thread.join();
          send_thread.join();
        }
    };
}


#endif
