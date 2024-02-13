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
    }
  }

  void MapCircle::sit(FluffyMultiplayer::MenschPiece* p)
  {
    if(piece==nullptr)
    {
      p->setPosition(position.x,position.y);
      std::cout << "piece sit\n";
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

  int GM_MENSCH::howManyPlayersAreInGame() const
  {
    return playersInGameCounter;
  }

  void GM_MENSCH::addPlayerToGame(FluffyMultiplayer::PlayerList& thatplayer)
  {
    std::array<sf::Color,MENSCH_PLAYERS_COUNT> tempColors =
    {
      sf::Color::Red,
      sf::Color::Green,
      sf::Color::Blue,
      sf::Color::Yellow
    };

    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      if(players[i].id == -1)
      {
        players[i].init(thatplayer.getId(),thatplayer.getName(),false,tempColors[i],thatplayer.isMe); //this client
        playersInGameCounter++;
        break;
      }
    }
  }

  GM_MENSCH::GM_MENSCH(sf::RenderWindow& window, FluffyMultiplayer::LobbyData* _lobby)
  {
    //set lobby details
    lobby = _lobby;
    playersInGameCounter=0;

    //labels:
    turnLabel.initText("turn:",
              (window.getSize().y/2)-100,
              (window.getSize().y/2)-100);


    dice.setPosition(200.0,100.0);//(window.getSize().x/5),(window.getSize().y/2));

    //background
    // backgroundGameMode.initIcon(ICON_BACKGROUND_GAMEMODE_MENSCH, ((window.getSize().x/2)-GM_MENSCH_BG_SIZE_X/2)+GM_MENSCH_BACKGROUND_PADDING_X, ((window.getSize().y/2)-GM_MENSCH_BG_SIZE_Y/2)+GM_MENSCH_BACKGROUND_PADDING_Y);


    //example
    players[0].init(1,"alex",true,sf::Color::Red,true); //this client
    players[1].init(2,"luki",false,sf::Color::Green,false);
    players[2].init(3,"max",false,sf::Color::Yellow,false);
    players[3].init(4,"peter",false,sf::Color::Blue,false);

    //example: set pieces into center
    for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
      for(int j=0; j<MENSCH_PIECE_PER_PLAYER; j++)
      {
        players[i].pieces[j].setPosition( (window.getSize().x/2)+i*65, (window.getSize().y/2)+j*65 );
        // std::cout << "player,piece : " << i << ","<< j << "\tx:" << players[i].pieces[j].position.x << "\ty:" << players[i].pieces[j].position.y << std::endl;
      }



    //init map:
    std::array<sf::Vector2f,MENSCH_MAP_COUNT> mapPositions =
    {
      sf::Vector2f(738.0 ,840.0), sf::Vector2f(741.0 ,783.0), sf::Vector2f(742.0 ,721.0), sf::Vector2f(742.0 ,661.0),
      sf::Vector2f(741.0 ,600.0), sf::Vector2f(682.0 ,597.0), sf::Vector2f(619.0 ,597.0), sf::Vector2f(557.0 ,595.0),
      sf::Vector2f(496.0 ,594.0), sf::Vector2f(494.0 ,534.0), sf::Vector2f(555.0 ,536.0), sf::Vector2f(618.0 ,534.0),
      sf::Vector2f(678.0 ,533.0), sf::Vector2f(742.0 ,534.0), sf::Vector2f(496.0 ,474.0), sf::Vector2f(556.0 ,470.0),
      sf::Vector2f(616.0 ,469.0), sf::Vector2f(676.0 ,469.0), sf::Vector2f(738.0 ,470.0), sf::Vector2f(739.0 ,407.0),
      sf::Vector2f(739.0 ,344.0), sf::Vector2f(739.0 ,285.0), sf::Vector2f(736.0 ,223.0), sf::Vector2f(800.0 ,221.0),
      sf::Vector2f(806.0 ,283.0), sf::Vector2f(805.0 ,346.0), sf::Vector2f(803.0 ,406.0), sf::Vector2f(802.0 ,473.0),
      sf::Vector2f(865.0 ,225.0), sf::Vector2f(866.0 ,283.0), sf::Vector2f(866.0 ,347.0), sf::Vector2f(867.0 ,412.0),
      sf::Vector2f(865.0 ,469.0), sf::Vector2f(923.0 ,470.0), sf::Vector2f(983.0 ,472.0), sf::Vector2f(1051.0 ,472.0),
      sf::Vector2f(1109.0 ,471.0), sf::Vector2f(1115.0 ,534.0), sf::Vector2f(1053.0 ,533.0), sf::Vector2f(993.0 ,537.0),
      sf::Vector2f(927.0 ,529.0), sf::Vector2f(864.0 ,531.0), sf::Vector2f(1114.0 ,596.0), sf::Vector2f(1051.0 ,596.0),
      sf::Vector2f(990.0 ,595.0), sf::Vector2f(929.0 ,595.0), sf::Vector2f(866.0 ,590.0), sf::Vector2f(868.0 ,655.0),
      sf::Vector2f(868.0 ,721.0), sf::Vector2f(865.0 ,779.0), sf::Vector2f(867.0 ,838.0), sf::Vector2f(804.0 ,841.0),
      sf::Vector2f(806.0 ,779.0), sf::Vector2f(807.0 ,720.0), sf::Vector2f(803.0 ,656.0), sf::Vector2f(799.0 ,598.0)
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
  }


  void GM_MENSCH::render(sf::RenderWindow& window)
  {
    // backgroundGameMode.render(window);
    std::cout << "MENSCH_MAP_COUNT: " << MENSCH_MAP_COUNT << std::endl;
    //render map circles
    for(int i=0; i<MENSCH_MAP_COUNT; i++)
    {
      std::cout << "i = " << i << " and MENSCH_MAP_COUNT=" << MENSCH_MAP_COUNT << std::endl;
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
    for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
    {
      if(id == players[i].id) //turnon
      {
        players[i].turn=true;
        turnLabel.setText("Turn: "+players[i].name + " ("+std::to_string(id)+")");
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
        menschMap[roomIndex].sit(&players[playerId].pieces[pieceId]);

        std::cout << "moved piece details: player " <<playerId << " piece " << pieceId << " into room" << roomIndex << std::endl;
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
