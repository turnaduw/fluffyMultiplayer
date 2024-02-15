#ifndef H_TEXT_COMPONENT
#define H_TEXT_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../config.h"
#include "uiComponent.h"
#include <string>

namespace FluffyMultiplayer
{
  class Text : public UiComponent
  {
    protected:
      sf::Font textFont;
      sf::Text textText;
      float x,y;
      std::string textValue;
    public:
      void setTextPosition(float _x, float _y)
      {
        x = _x;
        y = _y;
        textText.setPosition(x,y);
      }

      int getLength() const
      {
        return textValue.length();
      }

      void appendToText(std::string str)
      {
        textValue+=str;
        textText.setString(textValue);
      }

      void setText(std::string str)
      {
        textValue=str;
        textText.setString(str);
      }

      void setColor(sf::Color color)
      {
        textText.setFillColor(color);
      }

      void setFontSize(unsigned int size)
      {
        textText.setCharacterSize(size);
      }

      void initText(std::string str,float _x, float _y, unsigned int _fontSize)
      {
        x = _x;
        y = _y;
        componentLoadAndSetFont(textText,textFont);
        setText(str);
        setTextPosition(x,y);
        setFontSize(_fontSize);
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
