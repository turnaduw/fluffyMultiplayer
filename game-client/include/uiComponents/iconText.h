#ifndef H_ICON_TEXT_COMPONENT
#define H_ICON_TEXT_COMPONENT

#include "icon.h"
#include "text.h"

namespace FluffyMultiplayer
{
  class IconText : public Icon , public Text
  {
    public:

      void initIconText(std::string text, std::string texture,
              float x, float y)
      {
        initIcon(texture,x,y);
        initText(text,x ICON_TEXT_TEXT_PADDING_X,y ICON_TEXT_TEXT_PADDING_Y);
      }

      IconText(std::string text, std::string texture,float x, float y)
              : Icon(texture,x,y) ,
                Text(text,x ICON_TEXT_TEXT_PADDING_X,y ICON_TEXT_TEXT_PADDING_Y)
      {

      }

      IconText() : Icon() , Text()
      {

      }

      ~IconText()
      {

      }

      void render(sf::RenderWindow& window)
      {
        window.draw(icon); //from paretn (Icon)
        window.draw(textText);
      }
  };
}

#endif
