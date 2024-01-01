#ifndef H_TEXT_INPUT
#define H_TEXT_INPUT
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include "../config.h"
#include "uiComponent.h"

namespace FluffyMultiplayer
{
  class TextInput : public UiComponent
  {
    protected:
      std::string fontPath;
      sf::Font textInputFont;
      unsigned int textInputCharecterSize;

      //size and position TextInput
      sf::Vector2i boxSize;
      sf::Vector2f position;

      // variables
      std::string enteredString;
      std::string errorString;
      std::string placeHolderString;
      std::string titleString;

      bool hideTitleAndError;
      bool isPlaceHolderEnabled;

      //ui elements
      sf::Text titleText;
      sf::Text errorText;
      sf::Text mainText; //also placeHolder will use this

      sf::Color placeHolderColor;
      sf::Color mainTextColor;
      sf::Color titleTextColor;
      sf::Color errorTextColor;
      sf::Color inputBoxBackgroundColor;
      sf::Color inputBoxBorderColor;

      std::string inputBoxTexturePath;
      sf::Texture inputBoxTexture;
      sf::Sprite inputBoxSprite;
      sf::FloatRect inputBoxBound;

      virtual void specificRender(sf::RenderWindow& window)
      {
        /*
          other childs maybe need draw thier own item/elemnts to window
          like password button to invisble or visible charecters
        */
      }


    public:
      sf::FloatRect getInputBoxBound() const
      {
        return inputBoxBound;
      }

      void setPosition(int x,int y)
      {
        position.x = x;
        position.y = y;

        //re-position elements
        titleText.setPosition(position.x+TI_TITLE_PADDING_X, position.y-TI_TITLE_PADDING_Y);
        errorText.setPosition(position.x+TI_ERROR_PADDING_X, position.y-TI_ERROR_PADDING_Y); //(origin.x + TI_ERROR_PADDING_X, origin.y - TI_ERROR_PADDING_Y);
        inputBoxSprite.setPosition(position.x, position.y); //(origin.x - TI_INPUTBOX_PADDING_X, origin.y + TI_INPUTBOX_PADDING_Y);
        mainText.setPosition(inputBoxSprite.getPosition().x+boxSize.y/3, inputBoxSprite.getPosition().y+boxSize.y/6);
      }

      void setSize(int width, int height)
      {
        boxSize.x = width;
        boxSize.y = height;
      }

      void init(std::string strEntered="", std::string strError="",
            std::string strTitle="",
            std::string strPlaceholder="",
            float posx=TI_DEFAULT_POSITION_X, float posy=TI_DEFAULT_POSITION_Y)
      {
        isPlaceHolderEnabled=true;

        //init static elements
        enteredString = strEntered;
        errorString = strError;
        placeHolderString = strPlaceholder;
        titleString = strTitle;

        //set font
        fontPath = TI_DEFAULT_FONT_PATH;
        textInputFont.loadFromFile(fontPath);
        if(!hideTitleAndError)
        {
          titleText.setFont(textInputFont);
          errorText.setFont(textInputFont);
        }
        mainText.setFont(textInputFont);

        //set fontsize
        titleText.setCharacterSize(TI_DEFAULT_FONT_SIZE);
        errorText.setCharacterSize(TI_DEFAULT_FONT_SIZE);
        mainText.setCharacterSize(TI_DEFAULT_FONT_SIZE);


        //set style
        titleText.setStyle(TI_DEFAULT_STYLE);
        errorText.setStyle(TI_DEFAULT_STYLE);
        mainText.setStyle(TI_DEFAULT_STYLE);


        //set color
        titleText.setFillColor(TI_DEFAULT_FORGROUND_COLOR);
        errorText.setFillColor(TI_DEFAULT_FORGROUND_COLOR);
        mainText.setFillColor(TI_DEFAULT_FORGROUND_COLOR);
        inputBoxSprite.setColor(TI_DEFAULT_BACKGROUND_COLOR);

        setStrings();

        //init inputBox
        inputBoxTexturePath = FE_PATH_TO_ASSETS TI_TEXTURE_INPUT_BOX;
        inputBoxTexture.loadFromFile(inputBoxTexturePath);
        inputBoxSprite.setTexture(inputBoxTexture);


        //init default size and postion
        setSize(TI_DEFAULT_SIZE);
        setPosition(posx,posy);

        //get bound must placed after setPosition to works fine
        inputBoxBound = inputBoxSprite.getGlobalBounds();
      }

      void setTitles(std::string _title, std::string _error)
      {
        errorString = _error;
        titleString = _title;
        setStrings();
      }

      void setError(std::string err)
      {
        errorString = err;
        setStrings();
      }

      void setText(std::string str)
      {
        enteredString = str;
        setStrings();
      }

      void setPlaceholder(std::string str)
      {
        isPlaceHolderEnabled=true;
        placeHolderString = str;
      }

      TextInput()
      {
        init();
      }

      TextInput(std::string _text)
      {
        init();
        enteredString = _text;
      }


      TextInput(std::string title, std::string _error)
      {
        init();
        titleString = title;
        errorString = _error;
      }

      //re-fill
      TextInput(std::string title, std::string _error,
            std::string _text)
      {
        init();
        titleString = title;
        enteredString = _text;
        errorString = _error;
      }

      ~TextInput()
      {

      }

      void removeFromText()
      {
        //remove last char from string
        enteredString = enteredString.substr(0, enteredString.length()-1);
        setStrings();//update strings will display..
        if(isPlaceHolderEnabled==false && enteredString.empty())
          enablePlaceholder();
      }

      void appendToText(const char& _text)
      {
          enteredString += _text;

          //remove control charecters from received string, source: https://en.wikipedia.org/wiki/Control_character
          enteredString.erase(std::remove(enteredString.begin(), enteredString.end(), '\b'), enteredString.cend()); //backspace
          enteredString.erase(std::remove(enteredString.begin(), enteredString.end(), '\n'), enteredString.cend()); //enter (feed line)
          enteredString.erase(std::remove(enteredString.begin(), enteredString.end(), '\t'), enteredString.cend()); //tab
          enteredString.erase(std::remove(enteredString.begin(), enteredString.end(), '\e'), enteredString.cend()); //escape
          enteredString.erase(std::remove(enteredString.begin(), enteredString.end(), ' '), enteredString.cend()); //space
      }

      void enablePlaceholder()
      {
        isPlaceHolderEnabled=true;
        enteredString = placeHolderString;
      }

      void disablePlaceholder()
      {
        enteredString = "";
        isPlaceHolderEnabled=false;
      }
      void setStrings()
      {
        //set strings
        titleText.setString(titleString);
        errorText.setString(errorString);
        if(isPlaceHolderEnabled && enteredString.empty())
          mainText.setString(placeHolderString);
        else
          mainText.setString(enteredString);
      }

      void update(char _text)
      {
        if(_text!='\0')
        {
          if(isPlaceHolderEnabled)
            disablePlaceholder();
          appendToText(_text);
        }

        setStrings();
      }

      void render(sf::RenderWindow& window)
      {
        window.draw(inputBoxSprite);

        if(!hideTitleAndError)
        {
          window.draw(titleText);
          window.draw(errorText);
        }

        window.draw(mainText);

        specificRender(window);
      }

      std::string getEnteredText() const
      {
        return enteredString;
      }
  };
}

#endif
