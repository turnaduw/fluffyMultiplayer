#ifndef H_MAIN_CLIENT_DATA_TYPE
#define H_MAIN_CLIENT_DATA_TYPE

#include "config.h"
#include <boost/asio.hpp>

using boost::asio::ip::udp;


namespace FluffyMultiplayer
{
  struct AnAddress
  {
    boost::asio::ip::address ip;
    unsigned short port;

    AnAddress(std::string str,unsigned short _port)
    {
      ip = boost::asio::ip::address::from_string(str);
      port = _port;
    }

    AnAddress(boost::asio::ip::address _ip ,unsigned short _port)
    {
      ip = _ip;
      port = _port;
    }

    AnAddress()
    {
      ip = boost::asio::ip::address::from_string("127.0.0.1");
      port = 6321;
    }

    bool operator ==(const FluffyMultiplayer::AnAddress& a) const
    {
      if(a.ip == ip && a.port == port)
        return true;
      return false;
    }
    std::string getAsString()
    {
      return ip.to_string() + ":" + std::to_string(port);
    }

    void setFromEndpoint(udp::endpoint& e)
    {
      ip = e.address();
      port = e.port();
    }

  };


  struct TimeAndDate
  {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    static FluffyMultiplayer::TimeAndDate now()
    {
      // Get current time
      time_t now = time(0);
      tm* ltm = localtime(&now);
      // Extract current time components
      return FluffyMultiplayer::TimeAndDate {1900 + ltm->tm_year, 1 + ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec};
    }
  };

  struct Player
  {
    int id;
    std::string name; //same username
    bool isAdmin;
    bool voiceChatEnable;

    bool operator ==(const FluffyMultiplayer::Player& p) const
    {
      if(p.id==id)
        return true;
      return false;
    }

    void set(int _id,
        std::string _name=DEFAULT_PLAYER_NAME,
        bool _isAdmin=false,
        bool _voiceChatEnable=DEFAULT_PLAYER_VOICE_ENABLE)
    {
      id=_id;
      name=_name;
      isAdmin=_isAdmin;
      voiceChatEnable=_voiceChatEnable;
    }
  };

  struct SocketReceiveData
  {
    int code;
    std::string data;
    FluffyMultiplayer::AnAddress sender;
    void set(int c, std::string d, FluffyMultiplayer::AnAddress s)
    {
      code = c;
      data = d;
      sender = s;
    }
  };


  struct SocketSendData
  {
    int code;
    std::string data;

    //receiver is server
    void set(int c, std::string d)
    {
      code = c;
      data = d;
    }
  };

  struct LobbyData
  {
     bool isLocked;
     bool isVoiceChatForbidden;
     bool isTextChatForbidden;
     bool isSpecterForbidden;
     bool lobbyStatusInGame;
     bool showLobbyInList;
     int id;
     int maxPlayers;
     int currentPlayers;
     int gameMode;
     FluffyMultiplayer::AnAddress address; //save textPort in it
     unsigned short voicePort;
     int ownerId;


     std::string getAsString()
     {
       return std::to_string(maxPlayers) + MS_DATA_DELIMITER +
              std::to_string(gameMode) + MS_DATA_DELIMITER +
              std::to_string(currentPlayers) + MS_DATA_DELIMITER +
              std::to_string(isVoiceChatForbidden) + MS_DATA_DELIMITER +
              std::to_string(isTextChatForbidden) + MS_DATA_DELIMITER +
              std::to_string(isSpecterForbidden) + MS_DATA_DELIMITER +
              std::to_string(isLocked) + MS_DATA_DELIMITER + //is lcoked
              std::to_string(ownerId) + MS_DATA_DELIMITER;
     }

     LobbyData()
     {

     }
  };


  enum LogType
  {
      Error=0,
      Warning,
      Success,
      Information,
      All
  };

  enum NotificationType
  {
    normal=0,
    error,
    success,
    warning
  };

  enum NotificationPosition
  {
    center=0,
    bottomLeft,
    bottomRight,
    bottomCenter
  };

  struct NotificationData
  {
    int code;
    std::string title;
    std::string message;
    NotificationType type;
    NotificationPosition position;
  };
}

#endif
