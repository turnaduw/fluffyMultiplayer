#ifndef H_CHECKBOX_COMPONENT
#define H_CHECKBOX_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <string>
#include "../config.h"

namespace FluffyMultiplayer
{
  class CheckBox
  {
    private:

      //checkbox
      std::array<std::string,2> checkBoxButtonTexturePaths;
      std::array<sf::Texture,2> checkBoxButtonTextures;

      sf::Color backgroundColor;
      sf::Sprite checkBoxButtonSprite;
      sf::FloatRect checkBoxButtonBound;

      //button text
      sf::Font checkBoxFont;
      std::string fontPath;
      std::string checkBoxString;
      sf::Text checkBoxText;
      sf::Color forgroundColor;

      bool isChecked;
      sf::Vector2f checkBoxPosition;


    public:
      void setStatus(bool status)
      {
        if(status)
          check();
        else
          uncheck();
      }

      void clickedOnCheckBox()
      {
        if(isChecked)
          uncheck();
        else
          check();
      }

      void check()
      {
        isChecked=true;
        checkBoxButtonSprite.setTexture(checkBoxButtonTextures[1]);
      }
      void uncheck()
      {
        isChecked=false;
        checkBoxButtonSprite.setTexture(checkBoxButtonTextures[0]);
      }

      template <typename T> void setPosition(T x,T y)
      {
        checkBoxPosition.x = x;
        checkBoxPosition.y = y;
      }

      sf::FloatRect getBound() const
      {
        return checkBoxButtonBound;
      }

      bool getStatus() const
      {
        return isChecked;
      }


      void init(std::string btnText=CHECKBOX_DEFAULT_TEXT,
              float posX=CHECKBOX_DEFAULT_POS_X, float posY=CHECKBOX_DEFAULT_POS_Y,
              sf::Color bgColor=CHECKBOX_DEFAULT_BACKGROUND_COLOR,
              sf::Color fgColor=CHECKBOX_DEFAULT_FORGROUND_COLOR,
              unsigned int txtSize=CHECKBOX_DEFAULT_FONT_SIZE,
              bool _checkStatus=CHECKBOX_DEFAULT_STATUS)
      {
        isChecked = _checkStatus;

        //must first set size then set position (because of origin calculation)
        setPosition<float>(posX,posY);

        //button init
        checkBoxButtonTexturePaths[0] = FE_PATH_TO_ASSETS CHECKBOX_UNCHECKED_TEXTURE;
        checkBoxButtonTexturePaths[1] = FE_PATH_TO_ASSETS CHECKBOX_CHECKED_TEXTURE;
        checkBoxButtonTextures[0].loadFromFile(checkBoxButtonTexturePaths[0]);
        checkBoxButtonTextures[1].loadFromFile(checkBoxButtonTexturePaths[1]);

        // checkBoxButtonSprite.setColor(backgroundColor);
        checkBoxButtonSprite.setTexture(checkBoxButtonTextures[0]);


        //button text init
        checkBoxString = btnText;
        fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
        checkBoxFont.loadFromFile(fontPath);
        checkBoxText.setFont(checkBoxFont);
        checkBoxText.setOutlineColor(forgroundColor);
        checkBoxText.setString(checkBoxString);
        checkBoxText.setStyle(CHECKBOX_DEFAULT_STYLE);
        checkBoxText.setCharacterSize(txtSize);

        //make text center of button sprite
        checkBoxText.setPosition(checkBoxPosition);
        checkBoxButtonSprite.setPosition(checkBoxPosition.x + CHECKBOX_BOX_PADDING_X,
                checkBoxPosition.y);

        checkBoxButtonBound = checkBoxButtonSprite.getGlobalBounds();
      }

      void render(sf::RenderWindow& window)
      {
        window.draw(checkBoxText);
        window.draw(checkBoxButtonSprite);
      }

      CheckBox(std::string txt,float posx, float posy,
              sf::Color bgcolor, sf::Color fgcolor)
      {
        init(txt,posx,posy,bgcolor,fgcolor);
      }

      CheckBox(std::string txt,float posx, float posy)
      {
        init(txt,posx,posy);
      }

      CheckBox(std::string txt)
      {
        init(txt);
      }

      CheckBox()
      {
        init();
      }

      ~CheckBox()
      {

      }
  };
}

#endif
