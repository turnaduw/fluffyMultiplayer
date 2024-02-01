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
#define DEAD_POSITION 0
#define BOARD_EMPTY_VALUE 0
#define MINIMUM_VALID_BOARD_POS 1
#define MAXIMUM_VALID_BOARD_POS 56

#define HOME_TYPE_A_INDEX1 11
#define HOME_TYPE_A_INDEX2 12
#define HOME_TYPE_A_INDEX3 13
#define HOME_TYPE_A_INDEX4 14
#define SPAWN_TYPE_A_INDEX 1

#define HOME_TYPE_B_INDEX1 25
#define HOME_TYPE_B_INDEX2 26
#define HOME_TYPE_B_INDEX3 27
#define HOME_TYPE_B_INDEX4 28
#define SPAWN_TYPE_B_INDEX 15


#define HOME_TYPE_C_INDEX1 39
#define HOME_TYPE_C_INDEX2 40
#define HOME_TYPE_C_INDEX3 41
#define HOME_TYPE_C_INDEX4 42
#define SPAWN_TYPE_C_INDEX 29

#define HOME_TYPE_D_INDEX1 53
#define HOME_TYPE_D_INDEX2 54
#define HOME_TYPE_D_INDEX3 55
#define HOME_TYPE_D_INDEX4 56
#define SPAWN_TYPE_D_INDEX 43


// ------- requests 501->700
#define ROLE_DICE 501
#define MOVE_PIECE 502


// ------- responses 701->999
#define PLAYER_MOVED_PIECE 701
#define PIECE_KICKED 701
#define PLAYER_ROLED_DICE 702
#define TURN_FOR 703
#define UPDATE_BOARD 704
#define LATEST_BOARD_DATA 705








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
      std::array<FluffyMultiplayer::GM_MENSCH_PIECE,MENSCH_PLAYERS_COUNT-1> piece;
      FluffyMultiplayer::AnAddress address;

      void set(int _id,
            FluffyMultiplayer::GM_MENSCH_PIECE_TYPE _type,
            std::array<FluffyMultiplayer::GM_MENSCH_PIECE, MENSCH_PLAYERS_COUNT-1> _piece)
      {
        id=_id;
        type=_type;
        piece = _piece;
      }

      void set(int _id,
            FluffyMultiplayer::GM_MENSCH_PIECE_TYPE _type,
            FluffyMultiplayer::AnAddress _address)
      {
        id=_id;
        type=_type;
        address = _address;
      }
  };

  class GameModeMensch : public GameMode
  {
    private:
      std::array<FluffyMultiplayer::GM_MENSCH_PIECE_MAP,MENSCH_PLAYERS_COUNT> roads;

      int turn; //hold player's id
      int diceValue; //hold roled value untill that player move piece

      std::array<FluffyMultiplayer::GM_MENSCH_PLAYER,
              MENSCH_PLAYERS_COUNT-1> players;

      std::array<int,
                (MENSCH_PLAYERS_COUNT*MENSCH_ROOM_PER_PLAYER)+(MENSCH_PLAYERS_COUNT*MENSCH_PIECE_PER_PLAYER)> board;
       /*
        MENSCH_PLAYERS_COUNT*10 for each player has 10x node,
        MENSCH_PLAYERS_COUNT*4 for each player has 4x home
      */


      int rollDice(int min=1, int max=6)
      {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int randomNumber = std::rand() % (max - min + 1) + min;
        std::cout << "GM MENSCH: dice rolled number=" << randomNumber << std::endl;
        return randomNumber;
      }

      bool isPlayerAbleToMove()
      {
        // ifplayers[turn]
        return true;
      }


      void nextTurn()
      {
        if(turn<MENSCH_PLAYERS_COUNT)
          turn++;
        else
          turn = 0;

        diceValue=0;
        std::cout << "next turn: " << turn << std::endl;
      }

      bool isTurn(int playerId)
      {
        if(turn == playerId)
          return true;
        else
          return false;
      }

      int whosTurn()
      {
        std::cout << "GM MENSCH: Turn is for:" << turn << std::endl;
        return turn;
      }

      int getIdbyAddress(const FluffyMultiplayer::AnAddress& sender)
      {
        for(int p=0; p<players.size()-1; p++)
        {
          if(players[p].address == sender)
            return players[p].id;
        }
        return -1;
      }

      bool isPlayerValid(const FluffyMultiplayer::AnAddress& _Address)
      {
        for(int i=0; i<MENSCH_PLAYERS_COUNT-1; i++)
        {
          players[i].address == _Address;
          return true;
        }
        return false;
      }

      bool isGameFinished()
      {
        if(board[HOME_TYPE_A_INDEX1]>0 && board[HOME_TYPE_A_INDEX2]>0 && board[HOME_TYPE_A_INDEX3]>0 && board[HOME_TYPE_A_INDEX4]>0
          && board[HOME_TYPE_B_INDEX1]>0 && board[HOME_TYPE_B_INDEX2]>0 && board[HOME_TYPE_B_INDEX3]>0 && board[HOME_TYPE_B_INDEX4]>0
          && board[HOME_TYPE_C_INDEX1]>0 && board[HOME_TYPE_C_INDEX2]>0 && board[HOME_TYPE_C_INDEX3]>0 && board[HOME_TYPE_C_INDEX4]>0
          && board[HOME_TYPE_D_INDEX1]>0 && board[HOME_TYPE_D_INDEX2]>0 && board[HOME_TYPE_D_INDEX3]>0 && board[HOME_TYPE_D_INDEX4]>0)
        {
          return true;
        }
        return false;
      }

      void broadCast(FluffyMultiplayer::App& app,
                int code, std::string data,bool alsoToSpecters=false)
      {
        app.response(app.sendTextDataList, code, data, &app.inLobbyPlayers,nullptr);

        if(alsoToSpecters)
        {
          app.response(app.sendTextDataList, code, data, &app.lobbySpecters,nullptr);
        }
      }

      bool isPosValid(int pos)
      {
        if(pos >= MINIMUM_VALID_BOARD_POS && pos <= MAXIMUM_VALID_BOARD_POS)
        {
          return true;
        }
        return false;
      }

      int getOwnerByPieceId(int id)
      {
        for(int i=0; i<MENSCH_PLAYERS_COUNT-1; i++)
        {
          for(int j=0; j<MENSCH_PLAYERS_COUNT-1; j++)
          {
            if(players[i].piece[j].id == id)
              return i;
          }
        }
        return -1;
      }

      void kickPiece(int id)
      {
        int owner = getOwnerByPieceId(id);
        for(int i=0; i<MENSCH_PLAYERS_COUNT-1; i++)
        {
          if(players[owner].piece[i].id == id)
            players[owner].piece[i].position = DEAD_POSITION;
        }
      }

    public:
      FluffyMultiplayer::GameMode* process(FluffyMultiplayer::App& app,
                            const FluffyMultiplayer::SocketReceiveData& currentItem,
                            const std::vector<std::string>& cData) override
      {
        if(isPlayerValid(currentItem.sender))
        {
          if(isGameFinished())
          {
            //game is finished can not request to dice or movePiece..
            return nullptr;
          }
          else
          {
            int requesterId = getIdbyAddress(currentItem.sender);
            switch (currentItem.code)
            {
              case ROLE_DICE:
              {
                //role dice
                diceValue = rollDice();

                if(isPlayerAbleToMove())
                {
                  //broadcast role result:
                  broadCast(app,PLAYER_ROLED_DICE,"player with id : .. rolled result = ..",true);
                }
                else
                {
                  //broadcast role result:
                  broadCast(app,PLAYER_ROLED_DICE,"player with id : .. rolled result = .. but he could not able to move.. ",true);

                  // that player with that role number is not able to move, next turn
                  nextTurn();

                  //broadcast turn:
                  broadCast(app,TURN_FOR,"next turn, now turn is for player with id ..",true);
                }

              }break;

              case MOVE_PIECE: //cData[0]->id that piece wants to move
              {
                if(diceValue>0)
                {
                  if(isTurn(requesterId))
                  {
                    int pieceId = app.stringToInt(cData[0]);
                    if(getOwnerByPieceId(pieceId) == requesterId)
                    {
                      //logic...
                      int lastpos = players[requesterId].piece[pieceId].position;
                      int newpos = lastpos + diceValue;

                      if(isPosValid(newpos))
                      {
                        //place piece
                        board[lastpos] = BOARD_EMPTY_VALUE;

                        if(board[newpos]!=BOARD_EMPTY_VALUE)
                        {
                          //kick out old one piece
                          kickPiece(board[newpos]);
                          broadCast(app,PIECE_KICKED,"pieceId kicked by ..", true);

                          //place new piece
                          board[newpos] = pieceId;
                        }
                        else
                        {
                          board[newpos] = pieceId;
                        }

                        //reset diceValue
                        diceValue=0;

                        //broadcast result
                        broadCast(app,PLAYER_MOVED_PIECE,"pieceId .. moved +X",true);
                      }
                      else
                      {
                        //new position is inavlid value.. something went wrong
                      }
                    }
                    else
                    {
                      //you dont own this piece..
                    }
                  }
                  else
                  {
                    //not ur turn.
                  }
                }
                else
                {
                  //need to role first.
                }
              }break;

              default:
              {
                //unknown request from gameMode..
              }
            }
          }

        }
        else
        {
          //invalid user address...
        }
        return this;
      }

      GameModeMensch(FluffyMultiplayer::App& app)
      {
        std::cout << "gameMode Mensch constructor.\n";

        gameModeId=1;
        turn=-1;
        diceValue=0;

        int totalPieceId=0;
        //add players into game
        for(int i=0; i<MENSCH_PLAYERS_COUNT-1; i++)
        {
          players[i].set(app.inLobbyPlayers[i].id, static_cast<FluffyMultiplayer::GM_MENSCH_PIECE_TYPE>(i), app.inLobbyPlayers[i].address);

          //init pieces
          for(int k=0; k<MENSCH_PLAYERS_COUNT-1;k++)
          {
            players[i].piece[k].position = DEAD_POSITION;//all dead in first game.
            if(totalPieceId< MENSCH_PLAYERS_COUNT*MENSCH_PLAYERS_COUNT) //total < max pieces
            {
              players[i].piece[k].id = k;
              totalPieceId++;
            }
          }
        }

        //fill gameBoard with zeroes
        for(int i=0; i<(MENSCH_PLAYERS_COUNT*MENSCH_ROOM_PER_PLAYER)+(MENSCH_PLAYERS_COUNT*MENSCH_PIECE_PER_PLAYER); i++)
        {
          board[i] = BOARD_EMPTY_VALUE;
        }



        //set roads, dead position set becuase maybe in future we need place 4x for each player as dead points
        //index,        dead,              spawn,                                        {homes}
        roads[0] = GM_MENSCH_PIECE_MAP{DEAD_POSITION, SPAWN_TYPE_A_INDEX, {HOME_TYPE_A_INDEX1, HOME_TYPE_A_INDEX2, HOME_TYPE_A_INDEX3, HOME_TYPE_A_INDEX4}}; //typeA
        roads[1] = GM_MENSCH_PIECE_MAP{DEAD_POSITION, SPAWN_TYPE_B_INDEX, {HOME_TYPE_B_INDEX1, HOME_TYPE_B_INDEX2, HOME_TYPE_B_INDEX3, HOME_TYPE_B_INDEX4}}; //typeB
        roads[2] = GM_MENSCH_PIECE_MAP{DEAD_POSITION, SPAWN_TYPE_C_INDEX, {HOME_TYPE_C_INDEX1, HOME_TYPE_C_INDEX2, HOME_TYPE_C_INDEX3, HOME_TYPE_C_INDEX4}}; //typeC
        roads[3] = GM_MENSCH_PIECE_MAP{DEAD_POSITION, SPAWN_TYPE_D_INDEX, {HOME_TYPE_D_INDEX1, HOME_TYPE_D_INDEX2, HOME_TYPE_D_INDEX3, HOME_TYPE_D_INDEX4}}; //typeD


        //turn
        nextTurn();
        //broadcast turn:
        broadCast(app,TURN_FOR,"now turn is for player with id ..",true);
      }

      ~GameModeMensch()
      {

      }
  };
}

#endif
