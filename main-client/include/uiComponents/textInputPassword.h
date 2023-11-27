#ifndef H_TEXT_INPUT_PASSWORD
#define H_TEXT_INPUT_PASSWORD

#include "textInput.h"
#include <array>



namespace FluffyMultiplayer
{
    class TextInputPassword  : public TextInput
    {
      private:
        char inviseChar;
        std::string passwordEntered;

        //when passwordModeStatus is true
        bool isButtonVisiblePasswordClicked;
        std::array<std::string,2> buttonVisibleTexturePathes;
        std::array<sf::Texture,2> buttonVisiblePasswordTextures; //[0]->passwordModeStatus==false, [1]->passwordModeStatus==true
        std::array<sf::Sprite,2> buttonVisiblePasswordSprites;
        sf::FloatRect buttonVisiblePasswordBound;

      public:
        void appendToText(const std::string& _text)
        {
            passwordEntered += _text;
            if(isButtonVisiblePasswordClicked)
            {
              enteredString = passwordEntered;
            }
            else
            {
              enteredString = "";
              for(int i=1; i<passwordEntered.length(); i++)
                enteredString += inviseChar;
            }
        }

        //from outside will call this and this function do bounds thing to switch sprites for bound
        void buttonVisiblePasswordClicked()
        {
          if(isButtonVisiblePasswordClicked)
          {
            isButtonVisiblePasswordClicked=false;
            buttonVisiblePasswordBound = buttonVisiblePasswordSprites[0].getGlobalBounds();
          }
          else
          {
            isButtonVisiblePasswordClicked=true;
            buttonVisiblePasswordBound = buttonVisiblePasswordSprites[1].getGlobalBounds();
          }
        }

        void initTextInputPassword()
        {
          isButtonVisiblePasswordClicked=false;
          buttonVisibleTexturePathes[0] = FE_PATH_TO_ASSETS TIP_TEXTURE_BUTTON_VISIBLE_PASSWORD_ON;
          buttonVisibleTexturePathes[1] = FE_PATH_TO_ASSETS TIP_TEXTURE_BUTTON_VISIBLE_PASSWORD_OFF;
          buttonVisiblePasswordTextures[0].loadFromFile(buttonVisibleTexturePathes[0]);
          buttonVisiblePasswordTextures[1].loadFromFile(buttonVisibleTexturePathes[1]);

          buttonVisiblePasswordSprites[0].setTexture(buttonVisiblePasswordTextures[0]);
          buttonVisiblePasswordSprites[1].setTexture(buttonVisiblePasswordTextures[1]);
          buttonVisiblePasswordBound = buttonVisiblePasswordSprites[0].getGlobalBounds();
        }

        //to avoid while loading passsword via construcotr to show whole password
        //constructor TextInput will show all charecters exact same as original
        std::string convertStringToInvisibleChars(std::string str)
        {
          std::string output;
          passwordEntered = str;
          for(int i=1; i<str.length(); i++)
            output += inviseChar;
          return output;
        }

        TextInputPassword(std::string _title,
            char c='*')
          : TextInput(_title)
          {
            inviseChar = c;
          }

        //re-fill
        TextInputPassword(std::string _title,
            std::string _text,
            std::string _error,
            char c='*')
          : TextInput(_title,convertStringToInvisibleChars(_text),_error)
          {
            inviseChar = c;
            passwordEntered = _text;
          }

        void specificRender(sf::RenderWindow& window)
        {
          if(isButtonVisiblePasswordClicked)
            window.draw(buttonVisiblePasswordSprites[0]);
          else
            window.draw(buttonVisiblePasswordSprites[1]);
        }
    };
}

#endif
