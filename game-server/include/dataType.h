#ifndef H_DATA_TYPES
#define H_DATA_TYPES

#include <boost/asio.hpp>

#include <string>
#include <queue>
#include <vector>
#include "config.h"


using boost::asio::ip::udp;


namespace FluffyMultiplayer
{
  struct AnAddress
  {
    AnAddress() //somewhere trying to create AnAddress object
    {

    }

    boost::asio::ip::address ip;
    unsigned short port;

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
    std::string identity;
    std::string name; //same username
    bool isAdmin;
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
        std::string _name=DEFAULT_PLAYER_NAME,
        bool _isAdmin=false,
        bool _voiceChatEnable=DEFAULT_PLAYER_VOICE_ENABLE,
        FluffyMultiplayer::TimeAndDate _connectedTime=FluffyMultiplayer::TimeAndDate::now())
    {
      id=_id;
      identity=_identity;
      name=_name;
      isAdmin=_isAdmin;
      address=_address;
      connectedTime=_connectedTime;
      voiceChatEnable=_voiceChatEnable;
    }
  };

  struct BanList
  {
    int id;
    FluffyMultiplayer::AnAddress address;
    FluffyMultiplayer::TimeAndDate bannedTime;
    int banDuration;
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
    const std::vector<FluffyMultiplayer::Player>* receivers;
    const std::vector<FluffyMultiplayer::Player>* except;

    //one receiver
    void set(int c, std::string d, const FluffyMultiplayer::AnAddress& r)
    {
      receivers=nullptr;
      except=nullptr;
      code = c;
      data = d;
      receiver = r;
    }
    void set(int c, const FluffyMultiplayer::AnAddress& r)
    {
      receivers=nullptr;
      except=nullptr;
      code = c;
      data = "";
      receiver = r;
    }

    //broadcast
    void set(int c, std::string d,
            const std::vector<FluffyMultiplayer::Player>* r,
            const std::vector<FluffyMultiplayer::Player>* e)
    {
      code = c;
      data = d;
      receivers=r;
      except=e;
    }
    void set(int c,
            const std::vector<FluffyMultiplayer::Player>* r,
            const std::vector<FluffyMultiplayer::Player>* e)
    {
      code = c;
      data = "";
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

    std::string getAsStringForOwner(const std::string& ownerUsername)
    {
      return std::to_string(id) + MS_DATA_DELIMITER +
             std::to_string(maxPlayers) + MS_DATA_DELIMITER +
             std::to_string(gameMode) + MS_DATA_DELIMITER +
             std::to_string(currentPlayers) + MS_DATA_DELIMITER +
             std::to_string(isVoiceChatForbidden) + MS_DATA_DELIMITER +
             std::to_string(isTextChatForbidden) + MS_DATA_DELIMITER +
             std::to_string(isSpecterForbidden) + MS_DATA_DELIMITER +
             password + MS_DATA_DELIMITER +

             std::to_string(ownerId) + MS_DATA_DELIMITER+
             ownerUsername+ MS_DATA_DELIMITER;
    }
    std::string getAsStringForPlayers()
    {
      return std::to_string(maxPlayers) + MS_DATA_DELIMITER +
             std::to_string(gameMode) + MS_DATA_DELIMITER +
             std::to_string(currentPlayers) + MS_DATA_DELIMITER +
             std::to_string(isVoiceChatForbidden) + MS_DATA_DELIMITER +
             std::to_string(isTextChatForbidden) + MS_DATA_DELIMITER +
             std::to_string(isSpecterForbidden) + MS_DATA_DELIMITER +
             (password.length()>LOBBY_MINIMUM_PASSWORD_LENGTH? "1":"0") + MS_DATA_DELIMITER + //is lcoked
             std::to_string(ownerId) + MS_DATA_DELIMITER;
    }
  };
}

#endif
