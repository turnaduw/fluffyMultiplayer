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

  struct TimeAndDate
  {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    TimeAndDate now()
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
    std::string identity;
    std::string name;
    FluffyMultiplayer::AnAddress address;
    FluffyMultiplayer::TimeAndDate connectedTime;
    bool voiceChatEnable;

    bool operator == (const FluffyMultiplayer::Player& p)
    {
      if(p.id==id)
        return true;
      return false;
    }

    void set(int _id,
        std::string _identity,
        FluffyMultiplayer::AnAddress _address,
        std::string _name="?name?",
        bool _voiceChatEnable=false,
        FluffyMultiplayer::TimeAndDate _connectedTime=FluffyMultiplayer::TimeAndDate::now())
    {
      id=_id;
      identity=_identity;
      name=_name;
      address=_address;
      connectedTime=_connectedTime;
      voiceChatEnable=_voiceChatEnable;
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
    FluffyMultiplayer::AnAddress receiver; //if receivers == nulltpr then use this
    std::queue<FluffyMultiplayer::Player>* receivers;
    std::queue<FluffyMultiplayer::Player>* except;

    //one receiver
    void set(int c, std::string d, const FluffyMultiplayer::AnAddress& r)
    {
      receivers=nullptr;
      except=nullptr;
      code = c;
      data = d;
      receiver = r;
    }

    //broadcast
    void set(int c, std::string d,
            std::queue<FluffyMultiplayer::Player>* r,
            std::queue<FluffyMultiplayer::Player>* e)
    {
      code = c;
      data = d;
      receivers=r;
      except=e;
    }
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
}

#endif
