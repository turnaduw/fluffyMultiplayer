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
#define ROLE_DICE 501 //null
#define MOVE_PIECE 502 //pieceId


// ------- responses 701->999
#define PLAYER_MOVED_PIECE 701 //playerId, pieceI, roomIndex
// #define PIECE_KICKED 702
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

#define MENSCH_MAP_COUNT 56

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

    MenschPiece();
    void init(int _id, float x, float y, sf::Color piece_color);
    void dead();
    void setPosition(float x, float y);
  };

  struct MapCircle
  {
    int id;
    sf::Vector2f position;
    FluffyMultiplayer::PictureButton pb;
    FluffyMultiplayer::MenschPiece* piece;

    MapCircle();
    void kick();
    void sit(FluffyMultiplayer::MenschPiece* p);
    void setPosition(float x, float y);
    void setColor(sf::Color _color);
  };

  struct MenschDice
  {
    int value;
    FluffyMultiplayer::PictureButton pb;
    sf::Vector2f position;
    std::vector<std::string> texturesPath;

    MenschDice(float x,float y);
    MenschDice();
    void setPosition(float x, float y);
    void set(int number);
  };


  struct MenschPlayer
  {
    int id;
    bool turn;
    std::string name;
    sf::Color color;
    std::array<FluffyMultiplayer::MenschPiece,MENSCH_PIECE_PER_PLAYER> pieces;
    bool isMe;

    MenschPlayer();
    void init(int _id, std::string _name, bool _turn, sf::Color _color, bool me);
  };

  class GM_MENSCH : public GameMode
  {
    private:
      void initMap();

    public:
      FluffyMultiplayer::Text turnLabel;
      std::array<FluffyMultiplayer::MenschPlayer,MENSCH_PLAYERS_COUNT> players;
      FluffyMultiplayer::MenschDice dice;
      int turn; //hold player turns index
      std::array<FluffyMultiplayer::MapCircle,MENSCH_MAP_COUNT> menschMap;
      FluffyMultiplayer::SocketSendData sendTemp;

      FluffyMultiplayer::Icon backgroundGameMode;
      FluffyMultiplayer::LobbyData* lobby;

      //mouse event handel variable to delecre once, not per loop delcre
      sf::Vector2f mousePosition;

      void updatePlayersInGame(std::vector<std::string>& playersInfo, int myId);

      FluffyMultiplayer::GameMode* update(int& currentItemCode, std::vector<std::string>& cData);
      int stringToInt(const std::string& str);
      void setTurn(int id);
      GM_MENSCH(sf::RenderWindow& window, FluffyMultiplayer::LobbyData* _lobby);
      void render(sf::RenderWindow& window);
      void safePushToList(std::queue<FluffyMultiplayer::SocketSendData>& list,boost::mutex& sendMutex);
      void sendRequest(std::queue<FluffyMultiplayer::SocketSendData>& list, int code,
                    FluffyMultiplayer::AnAddress receiver, boost::mutex& sendMutex);
      void sendRequest(std::queue<FluffyMultiplayer::SocketSendData>& list, int code, std::string data,
                    FluffyMultiplayer::AnAddress receiver, boost::mutex&sendMutex);
      FluffyMultiplayer::GameMode* eventHandle(sf::RenderWindow& window, sf::Event& event,
                                     std::queue<FluffyMultiplayer::SocketSendData>& sendList,
                                     boost::mutex& sendMutex);


  };
}

#endif
