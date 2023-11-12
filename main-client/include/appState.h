#ifndef H_APP_STATE_CLASS
#define H_APP_STATE_CLASS
#include "include/config.h"
#include "include/dataType.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <queue>

namespace FluffyMultiplayer
{
  typedef std::array<FluffyMultiplayer::AppState*, STATES_COUNT>  StatesList;

  class AppState
  {
  protected:
    sf::Font basic_font;
    unsigned int basic_text_size;
    sf::Color basic_text_color;
    sf::Texture bg_texture;
    sf::Sprite bg_sprite;
    std::string bg_path;
    std::string font_path;
  public:
    virtual void render(sf::RenderWindow&)=0;
    virtual FluffyMultiplayer::AppState* update(sf::RenderWindow&,
                      const FluffyMultiplayer::StatesList&,
                      std::queue<std::string>&,
                      std::queue<std::string>&)=0;

    virtual FluffyMultiplayer::AppState* eventHandle(sf::RenderWindow&,
    sf::Event&, const FluffyMultiplayer::StatesList&)=0;

    void setBasicFont(std::string);
    void setBasicTextSize(unsigned int);
    void setBasicTextColor(sf::Color);
    void setBasicBackground(std::string);

    sf::Sprite getBgSprite();
    sf::Color getBasicColor();
    sf::Font getBasicFont();
    unsigned int getBasicTextSize();
  };
}
#endif
