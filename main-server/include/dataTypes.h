#ifndef H_MAIN_SERVER_DATATYPE_FILE
#define H_MAIN_SERVER_DATATYPE_FILE

#include <iostream>
#include <string>
#include <boost/asio.hpp>

namespace FluffyMultiplayer
{
  struct SocketDataQueue
  {
    int code;
    boost::asio::ip::address ip;
    unsigned short port;
    std::string data;
  };

  struct ConnectedClients
  {
    boost::asio::ip::address ip;
    unsigned short port;
  };

  struct CreateLobbyData
  {
    std::string identity;
    int gameMode;
    int maxPlayers;
    bool voiceChatForbidden;
    bool textChatForbidden;
    bool specterForbidden;
    std::string password;
  };

  struct TimeAndDate
  {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    bool isExpired(TimeAndDate date, const TimeAndDate& expireDate)
    {
      date += expireDate;
      if(this >= date)
        return true;
      return false;
    }

    void oprator += (const TimeAndDate& date)
    {
      year += date.year;
      month += date.month;
      day += date.day;
      hour += date.hour;
      minute += date.minute;
      second += date.second;
    }

    bool operator >= (const TimeAndDate &date) const
    {
      TimeAndDate diff
      {
        year - date.year,
        month - date.month,
        day - date.day,
        hour - date.hour,
        minute - date.minute,
        second - date.second
      };

      // Compare with static values
      if (diff.year > 0 ||
          (diff.year == 0 && diff.month > 0) ||
          (diff.year == 0 && diff.month == 0 && diff.day > 0) ||
          (diff.year == 0 && diff.month == 0 && diff.day == 0 && diff.hour > 0) ||
          (diff.year == 0 && diff.month == 0 && diff.day == 0 && diff.hour == 0 && diff.minute > 0) ||
          (diff.year == 0 && diff.month == 0 && diff.day == 0 && diff.hour == 0 && diff.minute == 0 && diff.second > 0))
      {
          return true;
      }
      return false;
    }


  };

  struct LoginClientData
  {
    std::string username;
    std::string password;
    std::string hardwareId;
    std::string oldIdentity;
  };

  struct RegisterClientData
  {
    std::string email;
    std::string username;
    std::string password;
    std::string hardwareId;
  };

  int convertStringToInt(const std::string&);
}

#endif
