#ifndef GM_MENSCH
#define GM_MENSCH

#include "../gameMode.h"

#define MENSCH_PLAYERS_COUNT 4


// ------- requests 501->700
#define PAUSE_GAME 501
#define RESUME_GAME 502
#define LEAVE_GAME 503
#define ROLE_DICE 504
#define MOEV_PIECE 505


// ------- responses 501->999
#define GAME_PAUSED 701
#define GAME_RESUMED  702
#define PLAYER_LEFT_THE_GAME 703
#define PLAYER_JOIN_THE_GAME 704
#define PLAYER_MOVED_PIECE 705
#define PLAYER_ROLED_DICE 706
#define TURN_FOR 707
#define UPDATE_BOARD 708


namespace FluffyMultiplayer
{
  enum Color { Black=0, White, Red, Green, Blue, Purple, Gray, Cyan, Yellow };

  struct Piece
  {
    int id;
    std::vector<int>position;
    // sf
  };

  struct MenschPlayer
  {
    int id;
    std::string name;
    FluffyMultiplayer::Color color;

  };

  struct MenschBoard
  {

  };

  class GameModeMensch : public GameMode
  {
    private:
      std::array<MenschPlayer,MENSCH_PLAYERS_COUNT> players;
      MenschBoard mboard;
    public:
      FluffyMultiplayer::GameMode* process(FluffyMultiplayer::SocketReceiveData& currentItem,
                                                   std::queue<FluffyMultiplayer::SocketSendData>& sendTextDataList,
                                                   FluffyMultiplayer::Log& log,
                                                   FluffyMultiplayer::DataBase& db,
                                                   FluffyMultiplayer::DataSecurity& ds) override;

      void roleDice();
      void nowTurn();
      void movePiece();

      GameModeMensch()
      {
        gameModeId = 1;
        gs = nullptr;
      }
      ~GameModeMensch();

  };
}

#endif
