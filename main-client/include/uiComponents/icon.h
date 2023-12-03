#ifndef H_ICON_COMPONENT
#define H_ICON_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../config.h"
#include "uiComponent.h"

namespace FluffyMultiplayer
{
  class Icon : public UiComponent
  {
    protected:
      sf::Sprite icon;
      sf::Texture iconTexture;
      sf::Vector2f iconPosition;

    public:
      void changeIconTexture(std::string path)
      {
        initIcon(path);
      }

      void setIconPosition(float x, float y)
      {
        iconPosition.x = x;
        iconPosition.y = y;
        icon.setPosition(iconPosition);
      }

      void initIcon(std::string path)
      {
        componentLoadTexture(iconTexture,path);
        icon.setTexture(iconTexture);
      }

      void initIcon(std::string path, float posx, float posy)
      {
        componentLoadTexture(iconTexture,path);
        icon.setTexture(iconTexture);
        setIconPosition(posx,posy);
      }

      Icon(std::string texture,float posx, float posy)
      {
        initIcon(texture,posx,posy);
      }

      Icon()
      {

      }

      ~Icon()
      {

      }

      virtual void render(sf::RenderWindow& window)
      {
        window.draw(icon);
      }
  };
}

#endif
