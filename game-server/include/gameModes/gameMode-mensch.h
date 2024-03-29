#ifndef GAMEMODE_MENSCH
#define GAMEMODE_MENSCH

#include "../gameMode.h"
#include "../app.h"
#include "../dataType.h"

//random number
#include <cstdlib>
#include <ctime>
#include <array>
#include <queue>
#include <iostream>


#define MENSCH_PLAYERS_COUNT 4
#define MENSCH_PIECE_PER_PLAYER 4
#define MENSCH_ROOM_PER_PLAYER 10
#define DEAD_POSITION -1
// #define BOARD_EMPTY_VALUE 0
#define MINIMUM_VALID_BOARD_POS 1
#define MAXIMUM_VALID_BOARD_POS 56

#define HOME_TYPE_A_INDEX1 11
#define HOME_TYPE_A_INDEX2 12
#define HOME_TYPE_A_INDEX3 13
#define HOME_TYPE_A_INDEX4 14
#define SPAWN_TYPE_A_INDEX 0//1

#define HOME_TYPE_B_INDEX1 25
#define HOME_TYPE_B_INDEX2 26
#define HOME_TYPE_B_INDEX3 27
#define HOME_TYPE_B_INDEX4 28
#define SPAWN_TYPE_B_INDEX 14//15


#define HOME_TYPE_C_INDEX1 39
#define HOME_TYPE_C_INDEX2 40
#define HOME_TYPE_C_INDEX3 41
#define HOME_TYPE_C_INDEX4 42
#define SPAWN_TYPE_C_INDEX 28//29

#define HOME_TYPE_D_INDEX1 53
#define HOME_TYPE_D_INDEX2 54
#define HOME_TYPE_D_INDEX3 55
#define HOME_TYPE_D_INDEX4 56
#define SPAWN_TYPE_D_INDEX 42//43


// ------- requests 501->700
#define ROLE_DICE 501
#define MOVE_PIECE 502


// ------- responses 701->999
#define PLAYER_MOVED_PIECE 701 //playerId, pieceI, roomIndex
// #define PIECE_KICKED 702
#define PLAYER_ROLED_DICE 703 //diceNumber
#define TURN_FOR 704 //playerId
#define UPDATE_BOARD 705
#define LATEST_BOARD_DATA 706







namespace FluffyMultiplayer
{
  class App; // Forward declaration
  class GameMode; // Forward declaration

  struct GM_MENSCH_PIECE
  {
      int id;
      int position; //0 for dead.
  };

  struct GM_MENSCH_PIECE_MAP
  {
    int deadPos;
    int spawnPos;
    std::array<int,MENSCH_PLAYERS_COUNT> homePos;
  };

  enum GM_MENSCH_PIECE_TYPE { TypeA=0,TypeB,TypeC,TypeD };

  struct GM_MENSCH_PLAYER
  {
      int id;
      FluffyMultiplayer::GM_MENSCH_PIECE_TYPE type;
      std::array<FluffyMultiplayer::GM_MENSCH_PIECE,
                  MENSCH_PLAYERS_COUNT> piece;
      FluffyMultiplayer::AnAddress address;
      bool finished;

      GM_MENSCH_PLAYER();

      void set(int _id,
            FluffyMultiplayer::GM_MENSCH_PIECE_TYPE _type,
            std::array<FluffyMultiplayer::GM_MENSCH_PIECE, MENSCH_PLAYERS_COUNT> _piece);

      void set(int _id,
            FluffyMultiplayer::GM_MENSCH_PIECE_TYPE _type,
            FluffyMultiplayer::AnAddress _address);
  };

  class GameModeMensch : public GameMode
  {
    private:
      std::array<FluffyMultiplayer::GM_MENSCH_PIECE_MAP,MENSCH_PLAYERS_COUNT> roads;

      FluffyMultiplayer::App* appPtr;
      int connectedPlayersCounter;
      int turn; //hold an index turn make loop for turns 0 to count of players..
      int diceValue; //hold roled value untill that player move piece
      int playerIdTurn; //hold player's id

      std::array<FluffyMultiplayer::GM_MENSCH_PLAYER,
              MENSCH_PLAYERS_COUNT> players;

      std::array<GM_MENSCH_PIECE*,
                      (MENSCH_PLAYERS_COUNT*MENSCH_ROOM_PER_PLAYER)+
                      (MENSCH_PLAYERS_COUNT*MENSCH_PIECE_PER_PLAYER)> board;
       /*
        MENSCH_PLAYERS_COUNT*10 for each player has 10x node,
        MENSCH_PLAYERS_COUNT*4 for each player has 4x home
      */
      void movePiece(int requesterId,int pieceId, int location);
      bool doesSkipHisHome(int requesterId, int pieceId);
      bool hasOnePieceInBoard(int requesterId);
      bool isThatPieceAllowedToMove(int indexRequester, int pieceId);
      int whatIsIndexRequester(int requesterId);
      void rollDice(int min, int max);
      bool isPlayerAbleToMove(int requesterId); //check for pieces are not dead if dead need dice == six also checks all pieces are not in home
      void nextTurn();
      bool isTurn(int playerId);
      int whosTurn();
      int getIdbyAddress(const FluffyMultiplayer::AnAddress& sender);
      bool isPlayerValid(const FluffyMultiplayer::AnAddress& _Address);
      bool isGameFinished();
      void broadCast(FluffyMultiplayer::App& app,
                int code, std::string data,bool alsoToSpecters);
      bool isPosValid(int pos);
      int getOwnerByPieceId(int id);
      void kickPiece(int id);
      int whatIsCorrectPos(FluffyMultiplayer::GM_MENSCH_PIECE_TYPE typePlayer,int pos); //to avoid land/sit piece other players inside others home
      FluffyMultiplayer::GM_MENSCH_PIECE_TYPE whatIsTypeRequester(int id);

    public:
      FluffyMultiplayer::GameMode* process(FluffyMultiplayer::App& app,
                            const FluffyMultiplayer::SocketReceiveData& currentItem,
                            const std::vector<std::string>& cData);

      void startGameMode();
      void addPlayerToGame(FluffyMultiplayer::App& app, int index);
      void removePlayerFromGame(FluffyMultiplayer::App& app, int playerId);
      int howManyPlayersAreInGame() const;
      GameModeMensch(FluffyMultiplayer::App& app);
      ~GameModeMensch();
  };
}

#endif
