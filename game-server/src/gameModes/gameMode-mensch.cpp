#include "../../include/gameModes/gameMode-mensch.h"



namespace FluffyMultiplayer
{
  //GM_MENSCH_PLAYER
  void GM_MENSCH_PLAYER::set(int _id,
        FluffyMultiplayer::GM_MENSCH_PIECE_TYPE _type,
        std::array<FluffyMultiplayer::GM_MENSCH_PIECE, MENSCH_PLAYERS_COUNT> _piece)
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

  GM_MENSCH_PLAYER::GM_MENSCH_PLAYER()
  {
    id=-1;
    finished=false;
  }


  //------------------------------------------------------
  //GameModeMensch
  void GameModeMensch::rollDice(int min=1, int max=6)
  {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = std::rand() % (max - min + 1) + min;
    std::cout << "GM MENSCH: dice rolled number=" << randomNumber << std::endl;
    diceValue = randomNumber;
  }

  bool GameModeMensch::hasOnePieceInBoard(int requesterId)
  {
    int pieceCount=0;
    int indexPlayer = whatIsIndexRequester(requesterId);
    for(int i=0; i<MENSCH_PIECE_PER_PLAYER; i++)
    {
      if(players[indexPlayer].piece[i].position != DEAD_POSITION)
        pieceCount++;
    }

    if(pieceCount==0)
      return false;

    return true;
  }

  bool GameModeMensch::doesSkipHisHome(int requesterId, int pieceId)
  {
    return false;
  }

  bool GameModeMensch::isPlayerAbleToMove(int requesterId)
  {
    //check for player does need dice value six or not
    if(!hasOnePieceInBoard(requesterId))
    {
      if(diceValue!=6)
        return false;
    }

    //check for player can move a piece or not
    int possibleMoves=0;
    for(int i=0; i<MENSCH_PIECE_PER_PLAYER; i++)
    {
      if(isThatPieceAllowedToMove(requesterId,i))
      {
        possibleMoves++;
      }
    }
    if(possibleMoves==0)
    {
      //not able to move
      return false;
    }


    //do not jump from his home !!!
    possibleMoves=0;
    for(int i=0; i<MENSCH_PIECE_PER_PLAYER; i++)
    {
      if(!doesSkipHisHome(requesterId,i))
      {
        possibleMoves++;
      }
    }
    if(possibleMoves==0)
    {
      //not able to move
      return false;
    }

    // ifplayers[turn]
    return true;
  }


  void GameModeMensch::nextTurn()
  {
    //give another turn if dice were six
    if(diceValue==6)
    {
      diceValue=0;
      broadCast((*appPtr),PLAYER_ROLED_DICE,std::to_string(diceValue),true);
      std::cout << "not next turn just give him another turn for his six gift\n";
      broadCast((*appPtr),TURN_FOR,std::to_string(playerIdTurn),true);
    }
    else
    {
      std::cout << "turn value=" << turn<< std::endl;
      if(turn<MENSCH_PLAYERS_COUNT-1)
        turn++;
      else
        turn = 0;

      diceValue=0;
      playerIdTurn = players[turn].id;

      //broadcast to players dice is reseted.
      broadCast((*appPtr),PLAYER_ROLED_DICE,std::to_string(diceValue),true);

      //broadcast turn:
      broadCast((*appPtr),TURN_FOR,std::to_string(playerIdTurn),true);
      std::cout << "next turn, now turn is for player with id: " << playerIdTurn << std::endl;
    }
    whosTurn();
  }

  bool GameModeMensch::isTurn(int playerId)
  {
    if(players[turn].id == playerId)
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
    for(int p=0; p<players.size(); p++)
    {
      if(players[p].address == sender)
        return players[p].id;
    }
    return -1;
  }

  bool GameModeMensch::isPlayerValid(const FluffyMultiplayer::AnAddress& _Address)
  {
    for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
    {
      players[i].address == _Address;
      return true;
    }
    return false;
  }

  bool GameModeMensch::isGameFinished()
  {
    if(board[HOME_TYPE_A_INDEX1]!=nullptr && board[HOME_TYPE_A_INDEX2]!=nullptr && board[HOME_TYPE_A_INDEX3]!=nullptr && board[HOME_TYPE_A_INDEX4]!=nullptr
      && board[HOME_TYPE_B_INDEX1]!=nullptr && board[HOME_TYPE_B_INDEX2]!=nullptr && board[HOME_TYPE_B_INDEX3]!=nullptr && board[HOME_TYPE_B_INDEX4]!=nullptr
      && board[HOME_TYPE_C_INDEX1]!=nullptr && board[HOME_TYPE_C_INDEX2]!=nullptr && board[HOME_TYPE_C_INDEX3]!=nullptr && board[HOME_TYPE_C_INDEX4]!=nullptr
      && board[HOME_TYPE_D_INDEX1]!=nullptr && board[HOME_TYPE_D_INDEX2]!=nullptr && board[HOME_TYPE_D_INDEX3]!=nullptr && board[HOME_TYPE_D_INDEX4]!=nullptr)
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

  // int GameModeMensch::getOwnerByPieceId(int id)
  // {
  //   for(int i=0; i<MENSCH_PLAYERS_COUNT-1; i++)
  //   {
  //     for(int j=0; j<MENSCH_PLAYERS_COUNT-1; j++)
  //     {
  //       if(players[i].piece[j].id == id)
  //         return i;
  //     }
  //   }
  //   return -1;
  // }

  void GameModeMensch::kickPiece(int id)
  {
    // int owner = getOwnerByPieceId(id);
    // for(int i=0; i<MENSCH_PLAYERS_COUNT-1; i++)
    // {
    //   if(players[owner].piece[i].id == id)
    //     players[owner].piece[i].position = DEAD_POSITION;
    // }
  }

  GameModeMensch::~GameModeMensch()
  {

  }

  GameModeMensch::GameModeMensch(FluffyMultiplayer::App& app)
  {
    gameModeId=1;
    appPtr=&app;

    std::cout << "gameMode Mensch constructor.\n";
    connectedPlayersCounter=0;
    turn=-1;
    diceValue=0;

    //fill gameBoard with zeroes
    for(int i=0; i<(MENSCH_PLAYERS_COUNT*MENSCH_ROOM_PER_PLAYER)+(MENSCH_PLAYERS_COUNT*MENSCH_PIECE_PER_PLAYER); i++)
    {
      board[i] = nullptr;
    }

    //set roads, dead position set becuase maybe in future we need place 4x for each player as dead points
    //index,        dead,              spawn,                                        {homes}
    roads[0] = GM_MENSCH_PIECE_MAP{DEAD_POSITION, SPAWN_TYPE_A_INDEX, {HOME_TYPE_A_INDEX1, HOME_TYPE_A_INDEX2, HOME_TYPE_A_INDEX3, HOME_TYPE_A_INDEX4}}; //typeA
    roads[1] = GM_MENSCH_PIECE_MAP{DEAD_POSITION, SPAWN_TYPE_B_INDEX, {HOME_TYPE_B_INDEX1, HOME_TYPE_B_INDEX2, HOME_TYPE_B_INDEX3, HOME_TYPE_B_INDEX4}}; //typeB
    roads[2] = GM_MENSCH_PIECE_MAP{DEAD_POSITION, SPAWN_TYPE_C_INDEX, {HOME_TYPE_C_INDEX1, HOME_TYPE_C_INDEX2, HOME_TYPE_C_INDEX3, HOME_TYPE_C_INDEX4}}; //typeC
    roads[3] = GM_MENSCH_PIECE_MAP{DEAD_POSITION, SPAWN_TYPE_D_INDEX, {HOME_TYPE_D_INDEX1, HOME_TYPE_D_INDEX2, HOME_TYPE_D_INDEX3, HOME_TYPE_D_INDEX4}}; //typeD



  }

  void GameModeMensch::removePlayerFromGame(FluffyMultiplayer::App& app, int playerId)
  {
    connectedPlayersCounter--;
    //remove that from if id == playerId
  }
  void GameModeMensch::startGameMode()
  {
    nextTurn();
  }

  void GameModeMensch::addPlayerToGame(FluffyMultiplayer::App& app, int playerIndexInLobbyPlayers)
  {
    if(connectedPlayersCounter<=3)
    {
      // add players into game
      for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
      {
        if(players[i].id == -1)
        {
          connectedPlayersCounter++;

          //set that receievd as player
          players[i].set(app.inLobbyPlayers[playerIndexInLobbyPlayers].id,
            static_cast<FluffyMultiplayer::GM_MENSCH_PIECE_TYPE>(i), app.inLobbyPlayers[playerIndexInLobbyPlayers].address);

          //init pieces for that player
          for(int k=0; k<MENSCH_PIECE_PER_PLAYER;k++)
          {
            players[i].piece[k].position = DEAD_POSITION;//all dead in first game.
            players[i].piece[k].id = k;
          }

          break;
        }
        else
        {
          continue;
        }
      }
    }
    else
    {
      std::cout << "game-mode mensch: game players are full can not add\n";
    }
  }
  int GameModeMensch::howManyPlayersAreInGame() const
  {
    return connectedPlayersCounter;
  }

  FluffyMultiplayer::GM_MENSCH_PIECE_TYPE GameModeMensch::whatIsTypeRequester(int id)
  {
    return players[whatIsIndexRequester(id)].type;
  }

  int GameModeMensch::whatIsCorrectPos(FluffyMultiplayer::GM_MENSCH_PIECE_TYPE typePlayer,int pos)
  {
    //find type of requester

    switch (typePlayer)
    {
      case TypeA:
      {
        switch (pos)
        {
          case HOME_TYPE_B_INDEX1: case HOME_TYPE_B_INDEX2: case HOME_TYPE_B_INDEX3:
          case HOME_TYPE_B_INDEX4: return HOME_TYPE_B_INDEX4+1;

          case HOME_TYPE_C_INDEX1: case HOME_TYPE_C_INDEX2: case HOME_TYPE_C_INDEX3:
          case HOME_TYPE_C_INDEX4: return HOME_TYPE_C_INDEX4+1;

          case HOME_TYPE_D_INDEX1: case HOME_TYPE_D_INDEX2: case HOME_TYPE_D_INDEX3:
          case HOME_TYPE_D_INDEX4: return HOME_TYPE_D_INDEX4+1;
          default: return pos;
        }
      }

      case TypeB:
      {
        switch (pos)
        {
          case HOME_TYPE_A_INDEX1: case HOME_TYPE_A_INDEX2: case HOME_TYPE_A_INDEX3:
          case HOME_TYPE_A_INDEX4: return HOME_TYPE_A_INDEX4+1;

          case HOME_TYPE_C_INDEX1: case HOME_TYPE_C_INDEX2: case HOME_TYPE_C_INDEX3:
          case HOME_TYPE_C_INDEX4: return HOME_TYPE_C_INDEX4+1;

          case HOME_TYPE_D_INDEX1: case HOME_TYPE_D_INDEX2: case HOME_TYPE_D_INDEX3:
          case HOME_TYPE_D_INDEX4: return HOME_TYPE_D_INDEX4+1;
          default: return pos;
        }
      }

      case TypeC:
      {
        switch (pos)
        {
          case HOME_TYPE_A_INDEX1: case HOME_TYPE_A_INDEX2: case HOME_TYPE_A_INDEX3:
          case HOME_TYPE_A_INDEX4: return HOME_TYPE_A_INDEX4+1;

          case HOME_TYPE_B_INDEX1: case HOME_TYPE_B_INDEX2: case HOME_TYPE_B_INDEX3:
          case HOME_TYPE_B_INDEX4: return HOME_TYPE_B_INDEX4+1;

          case HOME_TYPE_D_INDEX1: case HOME_TYPE_D_INDEX2: case HOME_TYPE_D_INDEX3:
          case HOME_TYPE_D_INDEX4: return HOME_TYPE_D_INDEX4+1;
          default: return pos;
        }
      }

      case TypeD:
      {
        switch (pos)
        {
          case HOME_TYPE_A_INDEX1: case HOME_TYPE_A_INDEX2: case HOME_TYPE_A_INDEX3:
          case HOME_TYPE_A_INDEX4: return HOME_TYPE_A_INDEX4+1;

          case HOME_TYPE_B_INDEX1: case HOME_TYPE_B_INDEX2: case HOME_TYPE_B_INDEX3:
          case HOME_TYPE_B_INDEX4: return HOME_TYPE_B_INDEX4+1;

          case HOME_TYPE_C_INDEX1: case HOME_TYPE_C_INDEX2: case HOME_TYPE_C_INDEX3:
          case HOME_TYPE_C_INDEX4: return HOME_TYPE_C_INDEX4+1;
          default: return pos;
        }
      }

      default:
      {
        std::cout << "unkown type of player in isOthersHome function\n";
        return pos;
      }
    }
    return pos;
  }

  int GameModeMensch::whatIsIndexRequester(int id)
  {
    for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
    {
      if(players[i].id == id)
      {
        return i;
      }
    }
    std::cout << "there is some problem to find index requester.\n";
    return 0;
  }

  bool GameModeMensch::isThatPieceAllowedToMove(int indexRequester, int pieceId)
  {
    if(players[indexRequester].piece[pieceId].position==DEAD_POSITION && diceValue!=6)
    {
      return false;
    }

    switch (players[indexRequester].type)
    {
      case TypeA:
      {
        switch (players[indexRequester].piece[pieceId].position)
        {
          case HOME_TYPE_A_INDEX4: return false;
        }
        return true;
      }
      case TypeB:
      {
        switch (players[indexRequester].piece[pieceId].position)
        {
          case HOME_TYPE_B_INDEX4: return false;
        }
        return true;
      }
      case TypeC:
      {
        switch (players[indexRequester].piece[pieceId].position)
        {
          case HOME_TYPE_C_INDEX4: return false;
        }
        return true;
      }
      case TypeD:
      {
        switch (players[indexRequester].piece[pieceId].position)
        {
          case HOME_TYPE_D_INDEX4: return false;
        }
        return true;
      }
    }
    return true;
  }

  void GameModeMensch::movePiece(int requesterId,int pieceId, int location)
  {
    if(isTurn(requesterId))
    {
      if(isPosValid(location))
      {
        int indexRequester = whatIsIndexRequester(requesterId);

        location = whatIsCorrectPos(whatIsTypeRequester(requesterId),location);


        if(isThatPieceAllowedToMove(indexRequester,pieceId))
        {
          //make old room empty
          int lastpos = players[requesterId].piece[pieceId].position;
          if(board[lastpos] != nullptr)
          {
            board[lastpos]->position = DEAD_POSITION;
            board[lastpos] = nullptr;
            std::cout << "piece located at " <<  lastpos << " kicked out from board. \n";
          }

          //place piece
          board[location] = &players[indexRequester].piece[pieceId];
          players[indexRequester].piece[pieceId].position = location;

          std::cout << "player " << requesterId << " moved piece " << pieceId <<
                       " from " << lastpos << " to " << location << std::endl;

          //broadcast result (playerid, piece id, new location)
          std::string res = std::to_string(requesterId);
          res += MS_DATA_DELIMITER;
          res += std::to_string(pieceId);
          res += MS_DATA_DELIMITER;
          res += std::to_string(location);
          res += MS_DATA_DELIMITER;

          broadCast((*appPtr),PLAYER_MOVED_PIECE,res,true);
          nextTurn();
        }
        else
        {
          std::cout << "piece can not move forward chose another one.\n";
          //this piece can not move forward chose another one.
        }
      }
      else
      {
        //new position is inavlid value.. something went wrong
        std::cout << "new poisition is invalid value ..\n";
      }
    }
    else
    {
      //not ur turn.
      std::cout << "not ur turn to move piece\n";
    }
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
            std::cout << "process roll dice request from players. requesterId:" << requesterId << std::endl;
            if(isTurn(requesterId))
            {
              if(diceValue!=0)
              {
                std::cout << "player can role once.. just can move now.\n";
              }
              else
              {
                //role dice
                rollDice();

                //broadcast role result:
                broadCast(app,PLAYER_ROLED_DICE,std::to_string(diceValue),true);


                //to avoid move six room in first wave of six, that six is only for join a piece
                //check for dice value if that is Six and player has no piece
                if(diceValue==6 && !hasOnePieceInBoard(requesterId))
                {
                  switch (whatIsTypeRequester(requesterId))
                  {
                    case TypeA:
                    {
                      movePiece(requesterId,0,SPAWN_TYPE_A_INDEX); //move his piece id 0 to spawn point
                    }break;
                    case TypeB:
                    {
                      movePiece(requesterId,0,SPAWN_TYPE_B_INDEX); //move his piece id 0 to spawn point
                    }break;
                    case TypeC:
                    {
                      movePiece(requesterId,0,SPAWN_TYPE_C_INDEX); //move his piece id 0 to spawn point
                    }break;
                    case TypeD:
                    {
                      movePiece(requesterId,0,SPAWN_TYPE_D_INDEX); //move his piece id 0 to spawn point
                    }break;
                    default:
                    {
                      std::cout << "unable to figureout type requester.\n";
                      movePiece(requesterId,0,0); //move his piece id 0 to 0?!
                    }
                  }

                  //call next turn but next turn will pass into this player
                  //because of his dice value is six for first time
                  //call next turn not needed, nextTurn method will call after movePiece automatically
                }
                else
                {
                  if(!isPlayerAbleToMove(requesterId))
                  {
                    std::cout << "player with id : .. rolled result = .. but he could not able to move.. " << std::endl;

                    // that player with that role number is not able to move, next turn
                    nextTurn();
                  }
                }
              }
            }
            else
            {
              //not ur turn
              std::cout << "is not his turn to dice\n";
              whosTurn();
            }
          }break;

          case MOVE_PIECE: //cData[0]->id that piece wants to move
          {
            if(diceValue>0)
            {
              int pieceId = app.stringToInt(cData[0]);

              //logic...
              int lastpos = players[requesterId].piece[pieceId].position;
              int newpos = lastpos + diceValue;

              movePiece(requesterId,pieceId,newpos);
            }
            else
            {
              //need to role first.
              std::cout << "before move piece need to role dice.\n";
            }
          }break;

          default:
          {
            //unknown request from gameMode..
            std::cout << "unknown request from gameMode\n";
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
