#ifndef H_PICTURE_BUTTON_COMPONENT
#define H_PICTURE_BUTTON_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../config.h"
#include "uiComponent.h"

namespace FluffyMultiplayer
{
  class PictureButton : public UiComponent
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


      void init(std::string btnText="Text", std::string txture=BUTTON_TEXTURE,
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
        setPosition<float>(posX,posY);

        //button init
        buttonTexturePath = FE_PATH_TO_ASSETS + txture;
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
        buttonText.setPosition(buttonPosition.x + PICTURE_BUTTON_TEXT_POS_X, buttonPosition.y + PICTURE_BUTTON_TEXT_POS_Y);
      }

      void render(sf::RenderWindow& window)
      {
        window.draw(buttonSprite);
        window.draw(buttonText);
      }

      PictureButton(std::string txt, std::string txture,
              float posx, float posy,
              sf::Color bgcolor, sf::Color fgcolor,
              int sizex, int sizey)
      {
        init(txt,txture,posx,posy,bgcolor,fgcolor,sizex,sizey);
      }

      PictureButton(std::string txt,std::string txture,
              float posx, float posy,
              sf::Color bgcolor, sf::Color fgcolor)
      {
        init(txt,txture,posx,posy,bgcolor,fgcolor);
      }


      PictureButton(std::string txt, std::string txture, float posx, float posy)
      {
        init(txt,txture,posx,posy);
      }

      PictureButton(std::string txt)
      {
        init(txt);
      }

      PictureButton()
      {
        init();
      }

      ~PictureButton()
      {

      }
  };
}

#endif
