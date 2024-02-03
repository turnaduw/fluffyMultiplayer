#ifndef H_PICTURE_BUTTON_COMPONENT
#define H_PICTURE_BUTTON_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../config.h"
#include "uiComponent.h"

namespace FluffyMultiplayer
{
  class PictureButton : public UiComponent
  {
    private:

      //checkbox
      std::string pictureButtonButtonTexturePath;
      sf::Texture pictureButtonButtonTexture;

      sf::Color backgroundColor;
      sf::Sprite pictureButtonButtonSprite;
      sf::FloatRect pictureButtonButtonBound;

      //button text
      sf::Font pictureButtonFont;
      std::string fontPath;
      std::string pictureButtonString;
      sf::Text pictureButtonText;
      sf::Color forgroundColor;

      bool isClicked;
      sf::Vector2f pictureButtonPosition;


    public:
      void clickOnButton()
      {
        isClicked=true;
      }

      template <typename T> void setPosition(T x,T y)
      {
        pictureButtonPosition.x = x;
        pictureButtonPosition.y = y;

        //apply position.
        pictureButtonButtonSprite.move(pictureButtonPosition);
        pictureButtonButtonBound = pictureButtonButtonSprite.getGlobalBounds();
      }

      sf::FloatRect getButtonBound() const
      {
        return pictureButtonButtonBound;
      }

      bool getButtonStatus() const
      {
        return isClicked;
      }


      void init(std::string btnText="Text", std::string txture=BUTTON_TEXTURE,
              float posX=BUTTON_DEFAULT_POS_X, float posY=BUTTON_DEFAULT_POS_Y,
              sf::Color bgColor=BUTTON_DEFAULT_BACKGROUND_COLOR,
              sf::Color fgColor=BUTTON_DEFAULT_FORGROUND_COLOR,
              unsigned int txtSize=BUTTON_DEFAULT_FONT_SIZE)
      {
        backgroundColor = bgColor;
        forgroundColor = fgColor;
        pictureButtonButtonTexturePath = txture;
        pictureButtonString = btnText;
        isClicked = false;

        //must first set size then set position (because of origin calculation)
        setPosition<float>(posX,posY);

        //button init
        componentLoadTexture(pictureButtonButtonTexture,pictureButtonButtonTexturePath);

        pictureButtonButtonSprite.setColor(backgroundColor);
        pictureButtonButtonSprite.setTexture(pictureButtonButtonTexture);


        //button text init
        fontPath = componentLoadAndSetFont(pictureButtonText,pictureButtonFont);
        pictureButtonText.setOutlineColor(forgroundColor);
        pictureButtonText.setString(pictureButtonString);
        pictureButtonText.setStyle(BUTTON_DEFAULT_STYLE);
        pictureButtonText.setCharacterSize(txtSize);
        // pictureButtonText.setColor(fgColor);

        //make text center of button sprite
        pictureButtonButtonSprite.setPosition(pictureButtonPosition);
        pictureButtonText.setPosition(pictureButtonPosition.x + PICTURE_BUTTON_TEXT_POS_X,
            pictureButtonPosition.y + PICTURE_BUTTON_TEXT_POS_Y);

        pictureButtonButtonBound = pictureButtonButtonSprite.getGlobalBounds();
      }
      void setBgColor(sf::Color _color)
      {
        backgroundColor = _color;
        pictureButtonButtonSprite.setColor(backgroundColor);
      }

      void render(sf::RenderWindow& window)
      {
        window.draw(pictureButtonText);
        window.draw(pictureButtonButtonSprite);
      }

      PictureButton(std::string txt, std::string txture, float posx, float posy,
              sf::Color bgcolor, sf::Color fgcolor)
      {
        init(txt, txture, posx,posy,bgcolor,fgcolor);
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

      void operator=(FluffyMultiplayer::PictureButton other)
      {
        pictureButtonButtonTexturePath = other.pictureButtonButtonTexturePath;

        backgroundColor = other.backgroundColor;

        //button text
        fontPath = other.fontPath;
        pictureButtonString = other.pictureButtonString;
        forgroundColor = other.forgroundColor;

        isClicked = other.isClicked;
        pictureButtonPosition = other.pictureButtonPosition;
      }

      ~PictureButton()
      {

      }
  };
}

#endif
