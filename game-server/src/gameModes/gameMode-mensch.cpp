#include "../../include/gameModes/gameMode-mensch.h"



namespace FluffyMultiplayer
{
  //GM_MENSCH_PLAYER
  void GM_MENSCH_PLAYER::set(int _id,
        FluffyMultiplayer::GM_MENSCH_PIECE_TYPE _type,
        std::array<FluffyMultiplayer::GM_MENSCH_PIECE, MENSCH_PLAYERS_COUNT -1> _piece)
  {
    id=_id;
    type=_type;
    piece = _piece;
  }

  void GM_MENSCH_PLAYER::set(int _id,
        FluffyMultiplayer::GM_MENSCH_PIECE_TYPE _type,
        FluffyMultiplayer::AnAddress _address)
  {
    id=_id;
    type=_type;
    address = _address;
  }


  //------------------------------------------------------
  //GameModeMensch
  int GameModeMensch::rollDice(int min=1, int max=6)
  {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = std::rand() % (max - min + 1) + min;
    std::cout << "GM MENSCH: dice rolled number=" << randomNumber << std::endl;
    return randomNumber;
  }

  bool GameModeMensch::isPlayerAbleToMove()
  {
    // ifplayers[turn]
    return true;
  }


  void GameModeMensch::nextTurn()
  {
    if(turn<MENSCH_PLAYERS_COUNT)
      turn++;
    else
      turn = 0;

    diceValue=0;
    std::cout << "next turn: " << turn << std::endl;
  }

  bool GameModeMensch::isTurn(int playerId)
  {
    if(turn == playerId)
      return true;
    else
      return false;
  }

  int GameModeMensch::whosTurn()
  {
    std::cout << "GM MENSCH: Turn is for:" << turn << std::endl;
    return turn;
  }

  int GameModeMensch::getIdbyAddress(const FluffyMultiplayer::AnAddress& sender)
  {
    for(int p=0; p<players.size()-1; p++)
    {
      if(players[p].address == sender)
        return players[p].id;
    }
    return -1;
  }

  bool GameModeMensch::isPlayerValid(const FluffyMultiplayer::AnAddress& _Address)
  {
    for(int i=0; i<MENSCH_PLAYERS_COUNT-1; i++)
    {
      players[i].address == _Address;
      return true;
    }
    return false;
  }

  bool GameModeMensch::isGameFinished()
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

  void GameModeMensch::broadCast(FluffyMultiplayer::App& app,
            int code, std::string data,bool alsoToSpecters=false)
  {
    app.response(code, data, &app.inLobbyPlayers,nullptr, false);

    if(alsoToSpecters)
    {
      app.response(code, data, &app.lobbySpecters,nullptr, false);
    }
  }

  bool GameModeMensch::isPosValid(int pos)
  {
    if(pos >= MINIMUM_VALID_BOARD_POS && pos <= MAXIMUM_VALID_BOARD_POS)
    {
      return true;
    }
    return false;
  }

  int GameModeMensch::getOwnerByPieceId(int id)
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

  void GameModeMensch::kickPiece(int id)
  {
    int owner = getOwnerByPieceId(id);
    for(int i=0; i<MENSCH_PLAYERS_COUNT-1; i++)
    {
      if(players[owner].piece[i].id == id)
        players[owner].piece[i].position = DEAD_POSITION;
    }
  }

  GameModeMensch::~GameModeMensch()
  {

  }

  GameModeMensch::GameModeMensch(FluffyMultiplayer::App& app)
  {
    std::cout << "gameMode Mensch constructor.\n";
    connectedPlayersCounter=0;
    gameModeId=1;
    turn=-1;
    diceValue=0;

    int totalPieceId=0;
    //add players into game
    for(int i=0; i<MENSCH_PLAYERS_COUNT-1; i++)
    {
      players[i].set(app.inLobbyPlayers[i].id,
            static_cast<FluffyMultiplayer::GM_MENSCH_PIECE_TYPE>(i), app.inLobbyPlayers[i].address);

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

  FluffyMultiplayer::GameMode* GameModeMensch::process(FluffyMultiplayer::App& app,
                        const FluffyMultiplayer::SocketReceiveData& currentItem,
                        const std::vector<std::string>& cData)
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


}
