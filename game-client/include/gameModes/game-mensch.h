#ifndef H_GAMEMODE_MENSCH_CLASS
#define H_GAMEMODE_MENSCH_CLASS

#include <array>
#include <vector>
#include "../gameMode.h"
#include "../config.h"
#include "../uiComponents/text.h"
#include "../uiComponents/pictureButton.h"
#include "../uiComponents/icon.h"

//random number
#include <cstdlib>
#include <ctime>


//convert string to int
#include <cstdlib>

// ------- requests 501->700
#define ROLE_DICE 501
#define MOVE_PIECE 502 //playerId, pieceId


// ------- responses 701->999
#define PLAYER_MOVED_PIECE 701 //playerId, pieceI, roomIndex
#define PIECE_KICKED 702
#define PLAYER_ROLED_DICE 703 //diceNumber
#define TURN_FOR 704 //playerId
#define UPDATE_BOARD 705
#define LATEST_BOARD_DATA 706



//padding and configs
#define MENSCH_PLAYERS_COUNT 4
#define MENSCH_PIECE_PER_PLAYER 4
#define MENSCH_ROOM_PER_PLAYER 10
#define MENSCH_HOME_ROOM_PER_PLAYER 4

#define MENSCH_PIECE_DEFAULT_FONTSIZE 10
#define MENSCH_PIECE_DEFAULT_FORGRAND_COLOR sf::Color::White
#define MENSCH_PIECE_DEFAULT_TEXT ""

#define M_DEAD_POSITION_X 0.0
#define M_DEAD_POSITION_Y 0.0

#define MENSCH_PLAYER_DEFAULT_COLOR sf::Color::Green

#define HOMES_COUNT MENSCH_PLAYERS_COUNT*MENSCH_PIECE_PER_PLAYER
#define MAPCIRCLES MENSCH_ROOM_PER_PLAYER*MENSCH_PLAYERS_COUNT
#define MENSCH_MAP_COUNT HOMES_COUNT+MAPCIRCLES

#define GM_MENSCH_BACKGROUND_PADDING_X 0.0
#define GM_MENSCH_BACKGROUND_PADDING_Y 0.0

#define GM_MENSCH_BG_SIZE_X 826
#define GM_MENSCH_BG_SIZE_Y 826

#define MINIMUM_DICE_VALUE 1
#define MAXIMUM_DICE_VALUE 6

#define DICE_TEXTURES {"gmMensch-dice0.png", "gmMensch-dice1.png","gmMensch-dice2.png","gmMensch-dice3.png","gmMensch-dice4.png","gmMensch-dice5.png","gmMensch-dice6.png"}

#define DFEAULT_DICE_X 0.0
#define DEFAULT_DICE_Y 0.0

#define DEFAULT_MAP_CIRCLE_X 0.0
#define DEFAULT_MAP_CIRCLE_Y 0.0
#define DEFAULT_MAP_CIRCLE_TEXTURE "gmMensch-circle.png"
#define DEFAULT_MAP_CIRCLE_COLOR sf::Color::White

namespace FluffyMultiplayer
{
  class App;
  class GameMode;

  struct ColorCircles
  {
    int id;
    sf::Color color;

    ColorCircles(int _i, sf::Color _c) : id(_i) , color(_c)
    {

    }
  };

  struct MenschPiece
  {
    int id;
    FluffyMultiplayer::PictureButton pb;
    sf::Vector2f position;

    MenschPiece()
    {
      id=-1;
      position.x=M_DEAD_POSITION_X;
      position.y=M_DEAD_POSITION_Y;
      pb.init("piece",ICON_PIECE,position.x,position.y,
              sf::Color::Black,sf::Color::White,10);
    }
    void init(int _id, float x, float y, sf::Color piece_color)
    {
      id = _id;
      position.x=x;
      position.y=y;
      pb.init(MENSCH_PIECE_DEFAULT_TEXT,ICON_PIECE,position.x,position.y,piece_color,
                    MENSCH_PIECE_DEFAULT_FORGRAND_COLOR,MENSCH_PIECE_DEFAULT_FONTSIZE);
    }

    void setPosition(float x, float y)
    {
      position.x = x;
      position.y = y;
      pb.setPosition(x,y);
    }
  };

  struct MapCircle
  {
    int id;
    sf::Vector2f position;
    FluffyMultiplayer::PictureButton pb;
    FluffyMultiplayer::MenschPiece* piece;

    // bool placePiece(FluffyMultiplayer::MenschPiece& )
    // {
      // if(piece==nullptr)
      // {
        //place
      // }
    // }

    // void kickPiece(FluffyMultiplayer::MenschPiece& oldPiece,
                   // FluffyMultiplayer::MenschPiece& newPiece)
    // {
    // }

    void sit(FluffyMultiplayer::MenschPiece* p)
    {
      if(piece==nullptr)
      {
        p->setPosition(position.x,position.y);
        std::cout << "piece sit\n";
      }
      else
      {
        std::cout << "need to kick someone.\n";

      }
    }

    void setPosition(float x, float y)
    {
      position.x = x;
      position.y = y;
      pb.setPosition(x,y);
    }

    void setColor(sf::Color _color)
    {
      pb.setBgColor(_color);
    }

    MapCircle()
    {
      piece=nullptr;
      position.x = DEFAULT_MAP_CIRCLE_X;
      position.y = DEFAULT_MAP_CIRCLE_Y;
      pb.init("",DEFAULT_MAP_CIRCLE_TEXTURE,position.x,position.y,DEFAULT_MAP_CIRCLE_COLOR);
    }
  };

  struct MenschDice
  {
    int value;
    FluffyMultiplayer::PictureButton pb;
    sf::Vector2f position;
    std::vector<std::string> texturesPath;

    MenschDice(float x,float y)
    {
      value=0;
      position.x = DFEAULT_DICE_X;
      position.y = DEFAULT_DICE_Y;
      texturesPath = DICE_TEXTURES;
      // pb.init("dice",texturesPath[value],position.x,position.y);
      pb.init("dice","gmMensch-dice2.png",position.x,position.y);
    }

    MenschDice()
    {
      value=0;
      position.x = DFEAULT_DICE_X;
      position.y = DEFAULT_DICE_Y;
      texturesPath = DICE_TEXTURES;
      // pb.init("dice",texturesPath[value],position.x,position.y);
      pb.init("dice","gmMensch-dice2.png",position.x,position.y);
    }

    void setPosition(float x, float y)
    {
      position.x = x;
      position.y = y;
      pb.setPosition(x,y);
    }

    void set(int number)
    {
      if(number>=MINIMUM_DICE_VALUE && number<=MAXIMUM_DICE_VALUE)
      {
        value=number;
        pb.init("dice",texturesPath[value],position.x,position.y);
      }
      else
        std::cout << "invalid dice value" << std::endl;
    }
  };


  struct MenschPlayer
  {
    int id;
    bool turn;
    std::string name;
    sf::Color color;
    std::array<FluffyMultiplayer::MenschPiece,MENSCH_PIECE_PER_PLAYER> pieces;

    MenschPlayer()
    {
      id=-1;
      name=DEFAULT_PLAYER_NAME;
      turn = false;
      color = MENSCH_PLAYER_DEFAULT_COLOR;
    }
    void init(int _id, std::string _name, bool _turn, sf::Color _color)
    {
      id=_id;
      name=_name;
      turn = _turn;
      color = _color;

      for(int i=0; i<MENSCH_PIECE_PER_PLAYER; i++)
        pieces[i].init(i,M_DEAD_POSITION_X,M_DEAD_POSITION_Y,color);

    }
  };

  class GM_MENSCH : public GameMode
  {
    public:
      FluffyMultiplayer::Text turnLabel;
      std::array<FluffyMultiplayer::MenschPlayer,MENSCH_PLAYERS_COUNT> players;
      FluffyMultiplayer::MenschDice dice;
      int turn; //hold player id's turn
      std::array<FluffyMultiplayer::MapCircle,MENSCH_MAP_COUNT> menschMap;
      FluffyMultiplayer::MapCircle testmap;
      FluffyMultiplayer::SocketSendData sendTemp;

      // FluffyMultiplayer::Icon backgroundGameMode;

      FluffyMultiplayer::LobbyData* lobby;

      //mouse event handel variable to delecre once, not per loop delcre
      sf::Vector2f mousePosition;


      FluffyMultiplayer::GameMode* update(int& currentItemCode, std::vector<std::string>& cData)
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

      int stringToInt(const std::string& str)
      {
        const char* c = str.c_str();
        return std::atoi(c);
      }

      void setTurn(int id)
      {
        turn = id;
        for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
        {
          if(id == i) //turnon
            players[i].turn=true;
          else //turnoff
            players[i].turn=false;
        }
      }

      GM_MENSCH(sf::RenderWindow& window, FluffyMultiplayer::LobbyData* _lobby)
      {
        //set lobby details
        lobby = _lobby;

        //labels:
        turnLabel.initText("turn:",
                  (window.getSize().y/2)-100,
                  (window.getSize().y/2)-100);


        dice.setPosition((window.getSize().x/5),(window.getSize().y/2));

        //background
        // backgroundGameMode.initIcon(ICON_BACKGROUND_GAMEMODE_MENSCH,
        //       ((window.getSize().x/2)-GM_MENSCH_BG_SIZE_X/2)+GM_MENSCH_BACKGROUND_PADDING_X,
        //       ((window.getSize().y/2)-GM_MENSCH_BG_SIZE_Y/2)+GM_MENSCH_BACKGROUND_PADDING_Y);


        //example
        players[0].init(1,"alex",true,sf::Color::Red);
        players[1].init(2,"luki",false,sf::Color::Green);
        players[2].init(3,"max",false,sf::Color::Yellow);
        players[3].init(4,"peter",false,sf::Color::Blue);

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
          sf::Vector2f(888.0,840.0),
          // sf::Vector2f(915.0,680.0),
          // sf::Vector2f(918.0,742.0),
          sf::Vector2f(891.0 ,783.0),
          sf::Vector2f(892.0 ,721.0),
          sf::Vector2f(892.0 ,661.0),
          sf::Vector2f(891.0 ,600.0),
          sf::Vector2f(832.0 ,597.0),
          sf::Vector2f(769.0 ,597.0),
          sf::Vector2f(707.0 ,595.0),
          sf::Vector2f(646.0 ,594.0),
          sf::Vector2f(644.0 ,534.0),
          sf::Vector2f(705.0 ,536.0),
          sf::Vector2f(768.0 ,534.0),
          sf::Vector2f(828.0 ,533.0),
          sf::Vector2f(892.0 ,534.0),
          sf::Vector2f(646.0 ,474.0),
          sf::Vector2f(706.0 ,470.0),
          sf::Vector2f(766.0 ,469.0),
          sf::Vector2f(826.0 ,469.0),
          sf::Vector2f(888.0 ,470.0),
          sf::Vector2f(889.0 ,407.0),
          sf::Vector2f(889.0 ,344.0),
          sf::Vector2f(889.0 ,285.0),
          sf::Vector2f(886.0 ,223.0),
          sf::Vector2f(950.0 ,221.0),
          sf::Vector2f(956.0 ,283.0),
          sf::Vector2f(955.0 ,346.0),
          sf::Vector2f(953.0 ,406.0),
          sf::Vector2f(952.0 ,473.0),
          sf::Vector2f(1015.0 ,225.0),
          sf::Vector2f(1016.0 ,283.0),
          sf::Vector2f(1016.0 ,347.0),
          sf::Vector2f(1017.0 ,412.0),
          sf::Vector2f(1015.0 ,469.0),
          sf::Vector2f(1073.0 ,470.0),
          sf::Vector2f(1133.0 ,472.0),
          sf::Vector2f(1201.0 ,472.0),
          sf::Vector2f(1259.0 ,471.0),
          sf::Vector2f(1265.0 ,534.0),
          sf::Vector2f(1203.0 ,533.0),
          sf::Vector2f(1143.0 ,537.0),
          sf::Vector2f(1077.0 ,529.0),
          sf::Vector2f(1014.0 ,531.0),
          sf::Vector2f(1264.0 ,596.0),
          sf::Vector2f(1201.0 ,596.0),
          sf::Vector2f(1140.0 ,595.0),
          sf::Vector2f(1079.0 ,595.0),
          sf::Vector2f(1016.0 ,590.0),
          sf::Vector2f(1018.0 ,655.0),
          sf::Vector2f(1018.0 ,721.0),
          sf::Vector2f(1015.0 ,779.0),
          sf::Vector2f(1017.0 ,838.0),
          sf::Vector2f(954.0 ,841.0),
          sf::Vector2f(956.0 ,779.0),
          sf::Vector2f(957.0 ,720.0),
          sf::Vector2f(953.0 ,656.0),
          sf::Vector2f(949.0 ,598.0)
        };

        std::array<FluffyMultiplayer::ColorCircles,MENSCH_PLAYERS_COUNT*5> mapColored =
        {
          ColorCircles(0,players[0].color), //spawn
          ColorCircles(52,players[0].color),
          ColorCircles(53,players[0].color),
          ColorCircles(54,players[0].color),
          ColorCircles(55,players[0].color),

          ColorCircles(14,players[1].color), //spawn
          ColorCircles(13,players[1].color),
          ColorCircles(12,players[1].color),
          ColorCircles(11,players[1].color),
          ColorCircles(10,players[1].color),

          ColorCircles(28,players[2].color), //spawn
          ColorCircles(27,players[2].color),
          ColorCircles(26,players[2].color),
          ColorCircles(25,players[2].color),
          ColorCircles(24,players[2].color),

          ColorCircles(42,players[3].color), //spawn
          ColorCircles(41,players[3].color),
          ColorCircles(40,players[3].color),
          ColorCircles(39,players[3].color),
          ColorCircles(38,players[3].color)
        };

        //set pos to map circles
        for(int i=0; i<MENSCH_MAP_COUNT; i++)
        {
          menschMap[i].setPosition(mapPositions[i].x, mapPositions[i].y);
        }

        testmap.setPosition(100.0,50.0);
        testmap.setColor(sf::Color::Black);
        //set color to map circles for home or spawn points
        for(int i=0; i<MENSCH_PLAYERS_COUNT*5; i++)
        {
          menschMap[mapColored[i].id].setColor(mapColored[i].color);
        }
      }

      void render(sf::RenderWindow& window)
      {
        // backgroundGameMode.render(window);
        testmap.pb.render(window);
        //render map circles
        for(int i=0; i<MENSCH_MAP_COUNT; i++)
          menschMap[i].pb.render(window);

        dice.pb.render(window);


        //render pieces
        for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
          for(int j=0; j<MENSCH_PIECE_PER_PLAYER; j++)
            players[i].pieces[j].pb.render(window);


        turnLabel.render(window);
      }


      void safePushToList(std::queue<FluffyMultiplayer::SocketSendData>& list,boost::mutex& sendMutex)
      {
        boost::lock_guard<boost::mutex> lock(sendMutex);
        list.push(sendTemp);
      }


      void sendRequest(std::queue<FluffyMultiplayer::SocketSendData>& list, int code,
                    FluffyMultiplayer::AnAddress receiver, boost::mutex& sendMutex)
      {
        sendTemp.set(code,receiver);
        safePushToList(list,sendMutex);
      }


      void sendRequest(std::queue<FluffyMultiplayer::SocketSendData>& list, int code, std::string data,
                    FluffyMultiplayer::AnAddress receiver, boost::mutex&sendMutex)
      {
        sendTemp.set(code,data,receiver);
        safePushToList(list,sendMutex);
      }


      FluffyMultiplayer::GameMode* eventHandle(sf::RenderWindow& window, sf::Event& event,
                                     std::queue<FluffyMultiplayer::SocketSendData>& sendList,
                                     boost::mutex& sendMutex)
      {
        //mouse realtime
        if(event.type == sf::Event::MouseButtonPressed)
        {
            mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            std::cout << "posx:" << mousePosition.x << "\tposy:" << mousePosition.y << std::endl;


            //check for dice
            if(dice.pb.getButtonBound().contains(mousePosition))
            {
              std::cout << "clicked on dice." << std::endl;
              sendRequest(sendList, ROLE_DICE, "clicked on dice.", lobby->address, sendMutex);
            }
            else //check each pieces
            {
              for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
              {
                for(int j=0; j<MENSCH_PIECE_PER_PLAYER; j++)
                {
                  if(players[i].pieces[j].pb.getButtonBound().contains(mousePosition))
                  {
                    std::cout << "clicked on piece, piece owner id= " << i << "\tpiece id=" << j << std::endl;
                    std::string clickResult =  "clicked on piece, details: piece owner id= " + std::to_string(i) + "\tpiece id=" + std::to_string(j);
                    sendRequest(sendList, PLAYER_MOVED_PIECE, clickResult, lobby->address,sendMutex);
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

  };
}

#endif
