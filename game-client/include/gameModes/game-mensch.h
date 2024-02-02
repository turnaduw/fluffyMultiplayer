#ifndef H_GAMEMODE_MENSCH_CLASS
#define H_GAMEMODE_MENSCH_CLASS

#include "../gameMode.h"
#include <array>
#include "../uiComponents/pictureButton.h"
#include "../config.h"

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

#define MENSCH_TOTAL_ROOMS MENSCH_PLAYERS_COUNT*MENSCH_PIECE_PER_PLAYER+ (MENSCH_HOME_ROOM_PER_PLAYER*MENSCH_PLAYERS_COUNT)

namespace FluffyMultiplayer
{
  class App;
  class GameMode;


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
      pb.init(MENSCH_PIECE_DEFAULT_TEXT,ICON_PIECE,position.x,position.y,piece_color,MENSCH_PIECE_DEFAULT_FORGRAND_COLOR,MENSCH_PIECE_DEFAULT_FONTSIZE);
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
      {
        pieces[i].init(i,M_DEAD_POSITION_X,M_DEAD_POSITION_Y,color);
      }
    }
  };

  class GM_MENSCH : public GameMode
  {
    public:
      FluffyMultiplayer::Text exampleText;
      std::array<FluffyMultiplayer::MenschPlayer,MENSCH_PLAYERS_COUNT> players;
      std::array<FluffyMultiplayer::MenschPlayer,MENSCH_TOTAL_ROOMS> rooms;
      FluffyMultiplayer::MenschPlayer emptyRoom;
      FluffyMultiplayer::Icon backgroundGameMode;

      FluffyMultiplayer::GameMode* update(FluffyMultiplayer::App& app)
      {
        return this;
      }

      GM_MENSCH()
      {
        exampleText.initText("exampleText",150.0,200.0);
        backgroundGameMode.initIcon(ICON_BACKGROUND_GAMEMODE_MENSCH,0.0,0.0);


        //example
        players[0].init(1,"alex",true,sf::Color::Red);
        players[1].init(2,"luki",false,sf::Color::Green);
        players[2].init(3,"max",false,sf::Color::Yellow);
        players[3].init(4,"peter",false,sf::Color::Blue);
      }

      void render(sf::RenderWindow* window)
      {
        backgroundGameMode.render((*window));

        //render pieces
        for(int i=0; i<MENSCH_PLAYERS_COUNT; i++)
        {
          for(int j=0; j<MENSCH_PIECE_PER_PLAYER; j++)
          {
            players[i].pieces[j].pb.render((*window));
          }
        }
        exampleText.render((*window));
      }

      FluffyMultiplayer::GameMode* eventHandle(FluffyMultiplayer::App& app, sf::Event& event)
      {
        return this;
      }

  };
}

#endif
