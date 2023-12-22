#ifndef H_DATA_TYPES
#define H_DATA_TYPES

#include <boost/asio.hpp>
#include <string>

namespace FluffyMultiplayer
{
  struct AnAddress
  {
    boost::asio::ip::address ip;
    unsigned short port;

    bool operator ==(const FluffyMultiplayer::AnAddress a)
    {
      if(a.ip == ip && a.port == port)
        return true;
      return false;
    }
    std::string getAsString()
    {
      return address.ip.to_string() + ":" + std::to_string(address.port);
    }

  };

  struct Player
  {
    int id;
    std::string identity;
    std::string name;
    FluffyMultiplayer::AnAddress address;
    FluffyMultiplayer::TimeAndDate connectedTime;

    bool operator == (const FluffyMultiplayer::Player& p)
    {
      if(p.id==id)
        return true;
      return false;
    }
  };

  struct BanList
  {
    std::string id;
    FluffyMultiplayer::AnAddress address;
    FluffyMultiplayer::TimeAndDate bannedTime;
    FluffyMultiplayer::TimeAndDate banDuration;
  };

  struct SocketReceiveData
  {
    int code;
    std::string data;
    FluffyMultiplayer::AnAddress sender;
  };

  struct SocketSendData
  {
    int code;
    std::string data;
    std::queue<FluffyMultiplayer::Player>* receivers;
    std::queue<FluffyMultiplayer::Player>* except;
  };

  struct LobbyData
  {
    int id;
    int maxPlayers;
    int gameMode;
    int currentPlayers;
    bool isVoiceChatForbidden;
    bool isTextChatForbidden;
    bool isSpecterForbidden;
    bool lobbyStatusInGame;
    std::string password;
    unsigned short textPort;
    unsigned short voicePort;
    int ownerId;
  };



  struct TimeAndDate
  {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
  };

}

#endif
