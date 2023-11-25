#ifndef H_TEXT_INPUT
#define H_TEXT_INPUT
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include "../config.h"


namespace FluffyMultiplayer
{
  class TextInput
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
      bool isFocus;
      sf::FloatRect getInputBoxBound() const
      {
        return inputBoxBound;
      }

      void setPosition(int x,int y)
      {
        position.x = x;
        position.y = y;
      }

      void setSize(int width, int height)
      {
        boxSize.x = width;
        boxSize.y = height;
      }

      void init()
      {
        isPlaceHolderEnabled=true;

        //init static elements
        enteredString = "";
        errorString = "";
        placeHolderString = "place holder";
        titleString = "Title:";

        //font
        fontPath = TI_DEFAULT_FONT_PATH;
        textInputFont.loadFromFile(fontPath);
        if(!hideTitleAndError)
        {
          titleText.setFont(textInputFont);
          errorText.setFont(textInputFont);
        }
        mainText.setFont(textInputFont);


        titleText.setString(titleString);
        errorText.setString(errorString);

        if(isPlaceHolderEnabled && enteredString.empty())
          mainText.setString(placeHolderString);
        else
          mainText.setString(enteredString);


          inputBoxTexturePath = TI_TEXTURE_INPUT_BOX;
          inputBoxTexture.loadFromFile(inputBoxTexturePath);
          inputBoxSprite.setTexture(inputBoxTexture);
          inputBoxBound = inputBoxSprite.getGlobalBounds();
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

      ~TextInput();

      void removeFromText()
      {
        enteredString = enteredString.substr(0,enteredString.length()-2);
        if(isPlaceHolderEnabled==false && enteredString.empty())
          enablePlaceholder();
      }

      virtual void appendToText(const std::string& _text)
      {
        if(isFocus)
          enteredString += _text;
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

      void update()
      {
        if(!_text.empty())
        {
          if(isPlaceHolderEnabled)
            disablePlaceholder();
          appendToText(_text);
        }

        mainText.setString(enteredString);
      }

      void render(std::string& _text, sf::RenderWindow& window)
      {
        update();

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
        return enteredText;
      }
  };
}

#endif
