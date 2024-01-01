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

    public:
      void setTextPosition(float x, float y)
      {
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

      void initText(std::string str,float x, float y)
      {
        componentLoadAndSetFont(textText,textFont);
        setText(str);
        setTextPosition(x,y);
      }

      Text(std::string str,float x, float y)
      {
        initText(str,x,y);
      }

      Text()
      {

      }

      ~Text()
      {

      }

      virtual void render(sf::RenderWindow& window)
      {
        window.draw(textText);
      }
  };
}

#endif
