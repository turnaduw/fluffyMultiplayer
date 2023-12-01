#ifndef H_SPINBOX_COMPONENT
#define H_SPINBOX_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "../config.h"

namespace FluffyMultiplayer
{
  class SpinBox
  {
    private:

      //SpinBox
      std::string spinBoxButtonTexturePath;
      sf::Texture spinBoxButtonTexture;

      std::vector<std::string> items;
      sf::Color backgroundColor;
      std::array<sf::Sprite,2> spinBoxButtonSprites;
      std::array<sf::FloatRect,2> spinBoxButtonBounds;

      //button text
      sf::Font spinBoxFont;
      std::string fontPath;
      std::string spinBoxString;
      sf::Text spinBoxText;
      sf::Color forgroundColor;

      int currentItem;
      sf::Vector2f spinBoxPosition;


    public:
      template <typename T> void setPosition(T x,T y)
      {
        spinBoxPosition.x = x;
        spinBoxPosition.y = y;
      }

      std::array<sf::FloatRect,2> getBound() const
      {
        return spinBoxButtonBounds;
      }

      void setItems(std::vector<std::string> listNewItems, int index=SPINBOX_DEFAULT_ITEM)
      {
        items=listNewItems;
        currentItem=index;
        spinBoxText.setString(spinBoxString+items[currentItem]);
      }

      int getCurrentIndex() const
      {
        return currentItem;
      }

      void spinUp()
      {
        if(currentItem<items.size()-1)
        {
          currentItem++;
          spinBoxText.setString(spinBoxString+items[currentItem]);
        }
      }

      void spinDown()
      {
        if(currentItem>0)
        {
          currentItem--;
          spinBoxText.setString(spinBoxString+items[currentItem]);
        }
      }

      void init(std::string btnText=SPINBOX_DEFAULT_TEXT, std::vector<std::string> allItems=SPINBOX_DEAULT_ITEMS,
              float posX=SPINBOX_DEFAULT_POS_X, float posY=SPINBOX_DEFAULT_POS_Y,
              sf::Color bgColor=SPINBOX_DEFAULT_BACKGROUND_COLOR,
              sf::Color fgColor=SPINBOX_DEFAULT_FORGROUND_COLOR,
              unsigned int txtSize=SPINBOX_DEFAULT_FONT_SIZE,
              int current=SPINBOX_DEFAULT_ITEM)
      {

        //must first set size then set position (because of origin calculation)
        setPosition<float>(posX,posY);

        //button init
        spinBoxButtonTexturePath = FE_PATH_TO_ASSETS SPINBOX_TEXTURE;
        spinBoxButtonTexture.loadFromFile(spinBoxButtonTexturePath);


        // spinBoxButtonSprites.setColor(backgroundColor);
        spinBoxButtonSprites[0].setTexture(spinBoxButtonTexture);
        spinBoxButtonSprites[1].setTexture(spinBoxButtonTexture);

        //rotate sprite for spinDown button
        spinBoxButtonSprites[1].rotate(180.f);


        //button text init
        spinBoxString = btnText;
        currentItem = current;
        items = allItems;
        fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
        spinBoxFont.loadFromFile(fontPath);
        spinBoxText.setFont(spinBoxFont);
        spinBoxText.setOutlineColor(forgroundColor);
        spinBoxText.setString(spinBoxString);
        spinBoxText.setStyle(SPINBOX_DEFAULT_STYLE);
        spinBoxText.setCharacterSize(txtSize);

        //make text center of button sprite
        spinBoxText.setPosition(spinBoxPosition);
        spinBoxButtonSprites[0].setPosition(spinBoxPosition.x SPINBOX_SPINUP_BUTTON_PADDING_X, spinBoxPosition.y SPINBOX_SPINUP_BUTTON_PADDING_Y);
        spinBoxButtonSprites[1].setPosition(spinBoxPosition.x SPINBOX_SPINDOWN_BUTTON_PADDING_X, spinBoxPosition.y SPINBOX_SPINDOWN_BUTTON_PADDING_Y);

        spinBoxButtonBounds[0] = spinBoxButtonSprites[0].getGlobalBounds();
        spinBoxButtonBounds[1] = spinBoxButtonSprites[1].getGlobalBounds();
      }

      void render(sf::RenderWindow& window)
      {
        window.draw(spinBoxText);
        window.draw(spinBoxButtonSprites[0]);
        window.draw(spinBoxButtonSprites[1]);
      }


      SpinBox(std::string txt, std::vector<std::string> elements,
              float posx, float posy,
              sf::Color bgcolor, sf::Color fgcolor,
              unsigned int size, int curr)
      {
        init(txt,elements,posx,posy,bgcolor,fgcolor,size,curr);
      }

      SpinBox(std::string txt, std::vector<std::string> elements,
              float posx, float posy,
              sf::Color bgcolor, sf::Color fgcolor)
      {
        init(txt,elements,posx,posy,bgcolor,fgcolor);
      }

      SpinBox(std::string txt, std::vector<std::string> elements, float posx, float posy)
      {
        init(txt,elements,posx,posy);
      }

      SpinBox(std::string txt, std::vector<std::string> elements)
      {
        init(txt,elements);
      }

      SpinBox()
      {
        init();
      }

      ~SpinBox()
      {

      }
  };
}

#endif
