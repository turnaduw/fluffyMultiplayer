#ifndef H_APP_STATE_CLASS
#define H_APP_STATE_CLASS
#include "./config.h"
#include "./dataType.h"
#include "./app.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <queue>

namespace FluffyMultiplayer
{
  class App;
  class AppState
  {
  protected:
    sf::Font theFont;
    sf::Text theText;
    void initSimpleText(std::string fontPath, std::string text,
                        unsigned int fontSize=22,
                        sf::Color color=sf::Color::White,
                        bool isBold=true)
    {
      theFont.loadFromFile(fontPath);
      theText.setFont(theFont);
      theText.setString(text);
      theText.setCharacterSize(fontSize);
      theText.setFillColor(color);
      if(isBold)
        theText.setStyle(sf::Text::Bold);
    }
    void setSimpleTextPosition(float x, float y)
    {
      theText.setPosition(x,y);
    }

  public:
    virtual void render(sf::RenderWindow&)=0;

    virtual FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&)=0;

    virtual FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                                        sf::Event&)=0;
  };
}
#endif
