#ifndef H_BUTTON_COMPONENT
#define H_BUTTON_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../config.h"
#include "uiComponent.h"

namespace FluffyMultiplayer
{
  class Button : public UiComponent
  {
    private:

      //button box
      std::string buttonTexturePath;
      sf::Texture buttonTexture;
      sf::Sprite buttonSprite;
      sf::FloatRect buttonBound;
      sf::Color backgroundColor;

      //button text
      std::string fontPath;
      sf::Font buttonFont;
      std::string buttonString;
      sf::Text buttonText;
      sf::Color forgroundColor;


      bool isButtonClicked;
      sf::Vector2i buttonSize;
      sf::Vector2f buttonPosition;


    public:

      template <typename T> void setPosition(T x,T y)
      {
        buttonPosition.x = x;
        buttonPosition.y = y;
      }

      sf::FloatRect getButtonBound() const
      {
        return buttonBound;
      }

      void setForgroundColor(sf::Color color)
      {
        forgroundColor =  color;
      }

      void setBackgroundColor(sf::Color color)
      {
        backgroundColor = color;
      }


      void clickOnButton()
      {
        isButtonClicked=true;
      }

      bool getButtonStatus() const
      {
        return isButtonClicked;
      }

      void setSize(int x, int y)
      {
        buttonSize.x = x;
        buttonSize.y = y;
        // buttonSprite.setScale(x,y);
      }

      void init(std::string btnText="Text",
              float posX=BUTTON_DEFAULT_POS_X, float posY=BUTTON_DEFAULT_POS_Y,
              sf::Color bgColor=BUTTON_DEFAULT_BACKGROUND_COLOR,
              sf::Color fgColor=BUTTON_DEFAULT_FORGROUND_COLOR,
              int sizeX=BUTTON_DEFAULT_SIZE_WIDTH, int sizeY=BUTTON_DEFAULT_SIZE_HEIGHT,
              unsigned int txtSize=BUTTON_DEFAULT_FONT_SIZE)
      {
        isButtonClicked=false;

        //set color
        // setBackgroundColor(bgColor);
        setForgroundColor(fgColor);

        //must first set size then set position (because of origin calculation)
        setSize(sizeX,sizeY);
        setPosition<float>(posX,posY);

        //button init
        buttonTexturePath = FE_PATH_TO_ASSETS BUTTON_TEXTURE;
        buttonTexture.loadFromFile(buttonTexturePath);
        // buttonSprite.setColor(backgroundColor);
        buttonSprite.setTexture(buttonTexture);
        buttonSprite.setPosition(buttonPosition);
        buttonBound = buttonSprite.getGlobalBounds();


        //button text init
        buttonString = btnText;
        fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
        buttonFont.loadFromFile(fontPath);
        buttonText.setFont(buttonFont);
        buttonText.setOutlineColor(forgroundColor);
        buttonText.setString(buttonString);
        buttonText.setStyle(BUTTON_DEFAULT_STYLE);
        buttonText.setCharacterSize(txtSize);

        //make text center of button sprite
        buttonText.setPosition(buttonPosition.x + buttonSize.x/3, buttonPosition.y + buttonSize.y/3);
      }

      void render(sf::RenderWindow& window)
      {
        window.draw(buttonSprite);
        window.draw(buttonText);
      }

      Button(std::string txt,float posx, float posy,
              sf::Color bgcolor, sf::Color fgcolor,
              int sizex, int sizey)
      {
        init(txt,posx,posy,bgcolor,fgcolor,sizex,sizey);
      }

      Button(std::string txt,float posx, float posy,
              sf::Color bgcolor, sf::Color fgcolor)
      {
        init(txt,posx,posy,bgcolor,fgcolor);
      }


      Button(std::string txt,float posx, float posy)
      {
        init(txt,posx,posy);
      }

      Button(std::string txt)
      {
        init(txt);
      }

      Button()
      {
        init();
      }

      ~Button()
      {

      }
  };
}

#endif
