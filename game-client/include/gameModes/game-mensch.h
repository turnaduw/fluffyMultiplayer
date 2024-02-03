#ifndef H_GAMEMODE_MENSCH_CLASS
#define H_GAMEMODE_MENSCH_CLASS

#include <array>
#include "../gameMode.h"
#include "../config.h"
#include "../uiComponents/text.h"
#include "../uiComponents/pictureButton.h"
#include "../uiComponents/icon.h"

//random number
#include <cstdlib>
#include <ctime>

// ------- requests 501->700
#define ROLE_DICE 501
#define MOVE_PIECE 502


// ------- responses 701->999
#define PLAYER_MOVED_PIECE 701
#define PIECE_KICKED 702
#define PLAYER_ROLED_DICE 703
#define TURN_FOR 704
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

    void setPosition(float x, float y)
    {
      position.x = x;
      position.y = y;
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

    MenschDice()
    {
      value=0;
      position.x = DFEAULT_DICE_X;
      position.y = DEFAULT_DICE_Y;
      texturesPath = DICE_TEXTURES;
      pb.init("dice",texturesPath[value],position.x,position.y);
    }

    void setPosition(float x, float y)
    {
      position.x = x;
      position.y = y;
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

      FluffyMultiplayer::SocketSendData sendTemp;

      FluffyMultiplayer::Icon backgroundGameMode;

      FluffyMultiplayer::LobbyData* lobby;

      //mouse event handel variable to delecre once, not per loop delcre
      sf::Vector2f mousePosition;


      FluffyMultiplayer::GameMode* update(FluffyMultiplayer::SocketReceiveData& currentItem)
      {
        switch (currentItem.code)
        {
          case PLAYER_MOVED_PIECE:
          {
            std::cout << "PLAYER_MOVED_PIECE\n";
          }break;
          case PIECE_KICKED:
          {
            std::cout << "PIECE_KICKED\n";
          }break;
          case PLAYER_ROLED_DICE:
          {
            std::cout << "PLAYER_ROLED_DICE\n";
            int x=3;
            dice.set(x);
          }break;
          case TURN_FOR:
          {
            std::cout << "TURN_FOR\n";
          }break;
          case  UPDATE_BOARD:
          {
            std::cout << "UPDATE_BOARD\n";
          }break;
          case LATEST_BOARD_DATA:
          {
            std::cout << "LATEST_BOARD_DATA\n";
          }break;

          default:
          {
            std::cout << "unkonwn response code from gameMode Mensch..\n";
          }
        }
        return this;
      }

      GM_MENSCH(sf::RenderWindow& window, FluffyMultiplayer::LobbyData* _lobby)
      {
        //set lobby details
        lobby = _lobby;

        //labels:
        turnLabel.initText("turn:",
                  (window.getSize().y/2)-100,
                  (window.getSize().y/2)-100);


        dice.setPosition((window.getSize().x/2),(window.getSize().y/2));

        //background
        backgroundGameMode.initIcon(ICON_BACKGROUND_GAMEMODE_MENSCH,
              ((window.getSize().x/2)-GM_MENSCH_BG_SIZE_X/2)+GM_MENSCH_BACKGROUND_PADDING_X,
              ((window.getSize().y/2)-GM_MENSCH_BG_SIZE_Y/2)+GM_MENSCH_BACKGROUND_PADDING_Y);


        //example
        players[0].init(1,"alex",true,sf::Color::Red);
        players[1].init(2,"luki",false,sf::Color::Green);
        players[2].init(3,"max",false,sf::Color::Yellow);
        players[3].init(4,"peter",false,sf::Color::Blue);

        //example: set pieces into center
        for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
          for(int j=0; j<MENSCH_ROOM_PER_PLAYER; j++)
          {
            players[i].pieces[j].setPosition( (window.getSize().x/2)+i*50, (window.getSize().y/2)+j*50 );
            std::cout << "player,piece : " << i << ","<< j << "\tx:" << players[i].pieces[j].position.x << "\ty:" << players[i].pieces[j].position.y << std::endl;
          }



        //init map:
        std::array<sf::Vector2f,MENSCH_MAP_COUNT> mapPositions =
        {
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0),
          sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0), sf::Vector2f(0.0,0.0)
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

        //set color to map circles for home or spawn points
        for(int i=0; i<MENSCH_PLAYERS_COUNT*5; i++)
        {
          menschMap[mapColored[i].id].setColor(mapColored[i].color);
        }
      }

      void render(sf::RenderWindow& window)
      {
        backgroundGameMode.render(window);

        //render map circles
        for(int i=0; i<MENSCH_MAP_COUNT; i++)
          menschMap[i].pb.render(window);


        //render pieces
        for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
          for(int j=0; j<MENSCH_PIECE_PER_PLAYER; j++)
            players[i].pieces[j].pb.render(window);


        turnLabel.render(window);
        dice.pb.render(window);
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
            std::cout << "mouse clicked posx:" << mousePosition.x << "\tposy:" << mousePosition.y << std::endl;


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
                  else if(players[i].pieces[j].pb.getButtonBound().contains(mousePosition))
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
