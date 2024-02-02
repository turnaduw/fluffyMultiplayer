#ifndef H_TEXT_COMPONENT
#define H_TEXT_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../config.h"
#include "uiComponent.h"

namespace FluffyMultiplayer
{
  class Text : public UiComponent
  {
    protected:
      sf::Font textFont;
      sf::Text textText;
      float x,y;
    public:
      void setTextPosition(float _x, float _y)
      {
        x = _x;
        y = _y;
        textText.setPosition(x,y);
      }

      void setText(std::string str)
      {
        textText.setString(str);
      }

      void setFontSize(unsigned int size)
      {
        textText.setCharacterSize(size);
      }

      void initText(std::string str,float _x, float _y)
      {
        x = _x;
        y = _y;
        componentLoadAndSetFont(textText,textFont);
        setText(str);
        setTextPosition(x,y);
      }

      Text(std::string str,float _x, float _y)
      {
        initText(str,_x,_y);
      }

      Text()
      {

      }

      ~Text()
      {

      }

      void operator=(FluffyMultiplayer::Text other)
      {
          textText = other.textText;
          x = other.x;
          y = other.y;
      }

      virtual void render(sf::RenderWindow& window)
      {
        window.draw(textText);
      }
  };
}

#endif
