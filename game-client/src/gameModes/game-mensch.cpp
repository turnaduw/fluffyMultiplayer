#include "../../include/gameModes/game-mensch.h"


namespace FluffyMultiplayer
{
  //MenschPiece

  MenschPiece::MenschPiece()
  {
    id=-1;
    position.x=M_DEAD_POSITION_X;
    position.y=M_DEAD_POSITION_Y;
    pb.init("",ICON_PIECE,position.x,position.y,
            sf::Color::Black,sf::Color::White,10);
  }
  void MenschPiece::init(int _id, float x, float y, sf::Color piece_color)
  {
    id = _id;
    position.x=x;
    position.y=y;
    pb.init(MENSCH_PIECE_DEFAULT_TEXT,ICON_PIECE,position.x,position.y,piece_color,
                  MENSCH_PIECE_DEFAULT_FORGRAND_COLOR,MENSCH_PIECE_DEFAULT_FONTSIZE);
  }

  void MenschPiece::dead()
  {
    position.x=M_DEAD_POSITION_X;
    position.y=M_DEAD_POSITION_Y;
    pb.setPosition(position.x,position.y);
  }

  void MenschPiece::setPosition(float x, float y)
  {
    position.x = x;
    position.y = y;
    pb.setPosition(x,y);
    std::cout << "set poisiton for mensch piece called.\n";
  }


  //---------------------------------------
  //MapCircle
  void MapCircle::kick()
  {
    if(piece!=nullptr)
    {
      piece->dead();
      piece=nullptr;
      std::cout << "piece kicked out.\n";
    }
    else
    {
      std::cout << "failed to kick there is no1.\n";
      piece=nullptr;
    }
  }

  void MapCircle::sit(FluffyMultiplayer::MenschPiece* p)
  {
    if(piece==nullptr)
    {
      p->setPosition(position.x,position.y);
      piece = p;
      std::cout << "piece sit at posx:" << position.x << "\ty=" << position.y << std::endl;
    }
    else
    {
      //first kick
      kick();

      //then place/sit
      this->sit(p);
    }
  }

  void MapCircle::setPosition(float x, float y)
  {
    position.x = x;
    position.y = y;
    pb.setPosition(x,y);
  }

  void MapCircle::setColor(sf::Color _color)
  {
    pb.setBgColor(_color);
  }

  MapCircle::MapCircle()
  {
    piece=nullptr;
    position.x = DEFAULT_MAP_CIRCLE_X;
    position.y = DEFAULT_MAP_CIRCLE_Y;
    pb.init("",DEFAULT_MAP_CIRCLE_TEXTURE,position.x,position.y,DEFAULT_MAP_CIRCLE_COLOR);
  }


  //---------------------------------------
  //MenschDice

  MenschDice::MenschDice(float x,float y)
  {
    value=0;
    position.x = DFEAULT_DICE_X;
    position.y = DEFAULT_DICE_Y;
    texturesPath = DICE_TEXTURES;
    // pb.init("dice",texturesPath[value],position.x,position.y);
    pb.init("","gmMensch-dice2.png",position.x,position.y);
  }

  MenschDice::MenschDice()
  {
    value=0;
    position.x = DFEAULT_DICE_X;
    position.y = DEFAULT_DICE_Y;
    texturesPath = DICE_TEXTURES;
    pb.init("",texturesPath[value],position.x,position.y);
    // pb.init("dice","gmMensch-dice2.png",position.x,position.y);
  }

  void MenschDice::setPosition(float x, float y)
  {
    position.x = x;
    position.y = y;
    pb.setPosition(x,y);
  }

  void MenschDice::set(int number)
  {
    if(number>=MINIMUM_DICE_VALUE && number<=MAXIMUM_DICE_VALUE)
    {
      value=number;
      pb.init("",texturesPath[value],position.x,position.y);
    }
    else
      std::cout << "invalid dice value" << std::endl;
  }

  //---------------------------------------
  //MenschPlayer
  MenschPlayer::MenschPlayer()
  {
    isMe=false;
    id=-1;
    name=DEFAULT_PLAYER_NAME;
    turn = false;
    color = MENSCH_PLAYER_DEFAULT_COLOR;
  }
  void MenschPlayer::init(int _id, std::string _name, bool _turn, sf::Color _color, bool me)
  {
    id=_id;
    name=_name;
    turn = _turn;
    color = _color;
    isMe=me;

    for(int i=0; i<MENSCH_PIECE_PER_PLAYER; i++)
      pieces[i].init(i,M_DEAD_POSITION_X,M_DEAD_POSITION_Y,color);

  }


  //---------------------------------------
  // GM_MENSCH

  void GM_MENSCH::initMap()
  {
    std::cout << "init map..\n";
    //init map:
    std::array<sf::Vector2f, MENSCH_MAP_COUNT> mapPositions =
    {
      sf::Vector2f(538.0, 740.0),
      sf::Vector2f(541.0, 683.0),
      sf::Vector2f(542.0, 621.0),
      sf::Vector2f(542.0, 561.0),
      sf::Vector2f(541.0, 500.0),
      sf::Vector2f(482.0, 497.0),
      sf::Vector2f(419.0, 497.0),
      sf::Vector2f(357.0, 495.0),
      sf::Vector2f(296.0, 494.0),
      sf::Vector2f(294.0, 434.0),
      sf::Vector2f(355.0, 436.0),
      sf::Vector2f(418.0, 434.0),
      sf::Vector2f(478.0, 433.0),
      sf::Vector2f(542.0, 434.0),
      sf::Vector2f(296.0, 374.0),
      sf::Vector2f(356.0, 370.0),
      sf::Vector2f(416.0, 369.0),
      sf::Vector2f(476.0, 369.0),
      sf::Vector2f(538.0, 370.0),
      sf::Vector2f(539.0, 307.0),
      sf::Vector2f(539.0, 244.0),
      sf::Vector2f(539.0, 185.0),
      sf::Vector2f(536.0, 123.0),
      sf::Vector2f(600.0, 121.0),
      sf::Vector2f(606.0, 183.0),
      sf::Vector2f(605.0, 246.0),
      sf::Vector2f(603.0, 306.0),
      sf::Vector2f(602.0, 373.0),
      sf::Vector2f(665.0, 125.0),
      sf::Vector2f(666.0, 183.0),
      sf::Vector2f(666.0, 247.0),
      sf::Vector2f(667.0, 312.0),
      sf::Vector2f(665.0, 369.0),
      sf::Vector2f(723.0, 370.0),
      sf::Vector2f(783.0, 372.0),
      sf::Vector2f(851.0, 372.0),
      sf::Vector2f(909.0, 371.0),
      sf::Vector2f(915.0, 434.0),
      sf::Vector2f(853.0, 433.0),
      sf::Vector2f(793.0, 437.0),
      sf::Vector2f(727.0, 429.0),
      sf::Vector2f(664.0, 431.0),
      sf::Vector2f(914.0, 496.0),
      sf::Vector2f(851.0, 496.0),
      sf::Vector2f(790.0, 495.0),
      sf::Vector2f(729.0, 495.0),
      sf::Vector2f(666.0, 490.0),
      sf::Vector2f(668.0, 555.0),
      sf::Vector2f(668.0, 621.0),
      sf::Vector2f(665.0, 679.0),
      sf::Vector2f(667.0, 738.0),
      sf::Vector2f(604.0, 741.0),
      sf::Vector2f(606.0, 679.0),
      sf::Vector2f(607.0, 620.0),
      sf::Vector2f(603.0, 556.0),
      sf::Vector2f(599.0, 498.0)
    };

    std::array<FluffyMultiplayer::ColorCircles,MENSCH_PLAYERS_COUNT*5> mapColored =
    {
      ColorCircles(0,players[0].color), //spawn
      ColorCircles(52,players[0].color), ColorCircles(53,players[0].color),
      ColorCircles(54,players[0].color), ColorCircles(55,players[0].color),

      ColorCircles(14,players[1].color), //spawn
      ColorCircles(13,players[1].color), ColorCircles(12,players[1].color),
      ColorCircles(11,players[1].color), ColorCircles(10,players[1].color),

      ColorCircles(28,players[2].color), //spawn
      ColorCircles(27,players[2].color), ColorCircles(26,players[2].color),
      ColorCircles(25,players[2].color), ColorCircles(24,players[2].color),

      ColorCircles(42,players[3].color), //spawn
      ColorCircles(41,players[3].color), ColorCircles(40,players[3].color),
      ColorCircles(39,players[3].color), ColorCircles(38,players[3].color)
    };

    //set pos to map circles
    for(int i=0; i<MENSCH_MAP_COUNT; i++)
    {
      menschMap[i].setPosition(mapPositions[i].x, mapPositions[i].y);
    }

    //set color to map circles for home or spawn points
    for(int i=0; i<MENSCH_PLAYERS_COUNT*5; i++)
    {
      menschMap[mapColored[i].id].setColor(mapColored[i].color);
    }

    gameStarted=true;
  }
  void GM_MENSCH::updatePlayersInGame(std::vector<std::string>& playersInfo, int myId)
  {
    std::cout << "myId=" << myId << std::endl;
    //received data or playersInfo holding data for each player : id , name , index
    // received index or same i or .. in this case we call it player color

    const int eachPlayerDataCount = 3;
    std::array<sf::Color,4> tempColors =
    {
      sf::Color::Red,
      sf::Color::Green,
      sf::Color::Blue,
      sf::Color::Yellow
    };

    bool _isme = false;
    std::vector<FluffyMultiplayer::MenschPlayer> playersReceived;
    FluffyMultiplayer::MenschPlayer tempPlayer;
    if(playersInfo.size()/eachPlayerDataCount >= MENSCH_PLAYERS_COUNT)
    {
      int pid=0;

      //seperate received players put in a temp player and push that into a list
      //because index in this loop works diffrent so we need to create another loop to assign into array players
      for(int i=0; i<MENSCH_PLAYERS_COUNT*3; i+=3)
      {
        pid = stringToInt(playersInfo[i]);
        if(myId == pid)
        {
          _isme = true;
        }
        else
        {
          _isme = false;
        }


        tempPlayer.init(pid,playersInfo[i+1],false,tempColors[stringToInt(playersInfo[i+2])],_isme);
        playersReceived.push_back(tempPlayer);
        std::cout << "+ a player collected from receivedPlayers from cData.\n";
      }

      //set received playersi with count of players we need into players array
      if(playersReceived.size()>=MENSCH_PLAYERS_COUNT)
      {
        float posX,posY;
        for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
        {
          if(i==0)
            posX=750.0;
          else if(i==1)
            posX=815.0;
          else if(i==2)
            posX=880.0;
          else
            posX=945.0;


          players[i].init(playersReceived[i].id,playersReceived[i].name,false,playersReceived[i].color,playersReceived[i].isMe); //this client
          for(int j=0; j<MENSCH_PIECE_PER_PLAYER; j++)
          {
            if(j==0)
              posY=100.0;
            else if(j==1)
              posY=165.0;
            else if(j==2)
              posY=230.0;
            else
              posY=295.0;

            players[i].pieces[j].setPosition( posX, posY );
          }
          std::cout << "player added into game players[i].init called.\n";
        }

        //print players on console
        std::cout <<"print players in game on console: \n\n\n";
        for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
        {
          std::cout << "id=" << players[i].id << "\tname=" << players[i].name << "\tisMe?" << players[i].isMe << std::endl;
        }

        initMap();
      }
      else
      {
        std::cout << "playerreceived size is small. size=" << playersReceived.size() << std::endl;
      }
    }
    else
    {
      std::cout << "updatePlayersInGame: small players data received. count=" << playersInfo.size() << std::endl;
    }


  }

  GM_MENSCH::GM_MENSCH(sf::RenderWindow& window, FluffyMultiplayer::LobbyData* _lobby)
  {
    //set lobby details
    lobby = _lobby;

    gameStarted=false;

    //labels:
    turnLabel.initText("Turn:", 260.0 ,105.0);


    dice.setPosition(599.0, 434.0);//(window.getSize().x/5),(window.getSize().y/2));

    //background
    backgroundGameMode.initIcon(ICON_BACKGROUND_GAMEMODE_MENSCH, 251.0 ,98.0);

    //example: set pieces into center
    for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
      for(int j=0; j<MENSCH_PIECE_PER_PLAYER; j++)
      {
        players[i].pieces[j].setPosition( (window.getSize().x/2)+i*65, (window.getSize().y/2)+j*65 );
        // std::cout << "player,piece : " << i << ","<< j << "\tx:" << players[i].pieces[j].position.x << "\ty:" << players[i].pieces[j].position.y << std::endl;
      }
  }


  void GM_MENSCH::render(sf::RenderWindow& window)
  {
    backgroundGameMode.render(window);

    //render map circles
    for(int i=0; i<MENSCH_MAP_COUNT; i++)
    {
      menschMap[i].pb.render(window);
    }

    dice.pb.render(window);


    //render pieces
    for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
      for(int j=0; j<MENSCH_PIECE_PER_PLAYER; j++)
        players[i].pieces[j].pb.render(window);


    turnLabel.render(window);
  }

  void GM_MENSCH::sendRequest(std::queue<FluffyMultiplayer::SocketSendData>& list, int code,
                FluffyMultiplayer::AnAddress receiver, boost::mutex& sendMutex)
  {
    sendTemp.set(code,receiver);
    safePushToList(list,sendMutex);
  }

  void GM_MENSCH::sendRequest(std::queue<FluffyMultiplayer::SocketSendData>& list, int code, std::string data,
                FluffyMultiplayer::AnAddress receiver, boost::mutex&sendMutex)
  {
    sendTemp.set(code,data,receiver);
    safePushToList(list,sendMutex);
  }

  void GM_MENSCH::safePushToList(std::queue<FluffyMultiplayer::SocketSendData>& list,boost::mutex& sendMutex)
  {
    boost::lock_guard<boost::mutex> lock(sendMutex);
    list.push(sendTemp);
  }


  FluffyMultiplayer::GameMode* GM_MENSCH::eventHandle(sf::RenderWindow& window, sf::Event& event,
                                 std::queue<FluffyMultiplayer::SocketSendData>& sendList,
                                 boost::mutex& sendMutex)
  {
    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        //check for dice
        if(dice.pb.getButtonBound().contains(mousePosition))
        {
          std::cout << "clicked on dice." << std::endl;
          sendRequest(sendList, ROLE_DICE, "", lobby->address, sendMutex);
        }
        else //check each pieces
        {
          for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
          {
            for(int j=0; j<MENSCH_PIECE_PER_PLAYER; j++)
            {
              if(players[i].pieces[j].pb.getButtonBound().contains(mousePosition))
              {
                if(players[i].isMe==true)
                {
                  std::cout << "i clicked on piece id=" << j << std::endl;
                  std::string clickResult = std::to_string(j);
                  sendRequest(sendList, MOVE_PIECE, clickResult, lobby->address,sendMutex);
                }
                else
                  std::cout << "u can not request to move this piece u are not the owner.\n";
              }
            }
          }
        }



    }

    //keyboard
    switch(event.type)
    {
      case sf::Event::KeyPressed:
      {
        // if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
        // {
        //   if(!passwordInput.getEnteredText().empty())
        //   {
        //     return formFinishedResult(app);
        //   }
        //   else
        //     std::cout << "one or more of the inputs are empty, can not submit\n";
        // }
        // if(event.key.code == sf::Keyboard::Backspace)
        // {
        //   if(inputFocus!=nullptr)
        //     inputFocus->removeFromText();
        // }
      }break;

      case sf::Event::TextEntered:
      {
        // if (event.text.unicode < 128)
        // {
        //   if(inputFocus != nullptr)
        //     inputFocus->update(static_cast<char>(event.text.unicode));
        // }
      }break;

    }
    return this;
  }


  void GM_MENSCH::setTurn(int id)
  {
    //find id by searching indexes
    std::array<sf::Color,4> colorList =
    {
      sf::Color::Red,
      sf::Color::Green,
      sf::Color::Blue,
      sf::Color::Yellow
    };


    for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
    {
      if(id == players[i].id) //turnon
      {
        players[i].turn=true;
        turnLabel.setText("Turn: "+players[i].name + " ("+std::to_string(id)+")");
        turnLabel.setColor(colorList[i]);
      }
      else //turnoff
      {
        players[i].turn=false;
      }
    }
  }

  int GM_MENSCH::stringToInt(const std::string& str)
  {
    const char* c = str.c_str();
    return std::atoi(c);
  }


  FluffyMultiplayer::GameMode* GM_MENSCH::update(int& currentItemCode, std::vector<std::string>& cData)
  {
    switch (currentItemCode)
    {
      case PLAYER_MOVED_PIECE: //playerId, pieceId, roomIndex
      {
        int playerId = stringToInt(cData[0]);
        int pieceId = stringToInt(cData[1]);
        int roomIndex = stringToInt(cData[2]);
        std::cout << "moved piece details: player " <<playerId << " piece " << pieceId << " into room " << roomIndex << std::endl;
        if(roomIndex<=MENSCH_MAP_COUNT)
        {
          if(pieceId<=3 && pieceId>-1)
          {
            for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
            {
              if(players[i].id == playerId)
              {
                std::cout << "move piece players[i].id=" << players[i].id << " playerid="<< playerId << " pieceId=" << pieceId << std::endl;
                menschMap[roomIndex].sit(&players[i].pieces[pieceId]);

                //temp print menschboard
                std::cout << "menschMap prints all pieces positions:\n";
                for(int i=0; i<MENSCH_MAP_COUNT; i++)
                {
                  std::cout << "map pos = " << menschMap[i].position.x << ", " << menschMap[i].position.y;
                  if(menschMap[i].piece==nullptr)
                  {
                    std::cout << "\t" << i << "nullptr\n";
                  }
                  else
                  {
                    std::cout << "\t" <<  i << " x:"<<menschMap[i].piece->position.x << "y:" << menschMap[i].piece->position.y << std::endl;
                  }
                }
                break;
              }
            }
          }
          else
          {
            std::cout << "player moved piece: piece id invalid pieceId:" << pieceId << std::endl;
          }
        }
        else
        {
          std::cout << "player moved piece: invalid room index.\n";
          std::cout << "room index = " << roomIndex << "\tMENSCH_MAP_COUNT=" << MENSCH_MAP_COUNT << std::endl;
        }

      }break;

      case PLAYER_ROLED_DICE: //diceNumber
      {
        int diceNumber= stringToInt(cData[0]);
        std::cout << "dice rolled set dice to " << diceNumber << std::endl;
        dice.set(diceNumber);
      }break;

      case TURN_FOR: //playerId
      {
        int playerId = stringToInt(cData[0]);
        setTurn(playerId);
        std::cout << "turn set for" << playerId << std::endl;
      }break;

      default:
      {
        std::cout << "unkonwn response code from gameMode Mensch..\n";
      }
    }
    return this;
  }



}
