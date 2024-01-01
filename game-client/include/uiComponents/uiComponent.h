#ifndef H_UI_COMPONENT
#define H_UI_COMPONENT

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "../config.h"

namespace FluffyMultiplayer
{
  class UiComponent
  {
  protected:
    std::string componentLoadAndSetFont(sf::Text& text, sf::Font& font, const std::string& path=MC_DEFAULT_FONT)
    {
      std::string finalPath = std::string(MC_PATH_TO_FONTS);
      finalPath += path;
      if(!font.loadFromFile(finalPath))
      {
        std::cout << "could not load font from path:" << finalPath << " trying to load default font for ui compnent." << std::endl;
        font.loadFromFile(UI_COMPONENT_FONT_DEFAULT);
      }
      text.setFont(font);
      return finalPath;
    }
    void componentLoadTexture(sf::Texture& texture, const std::string& path)
    {
      std::string finalPath = std::string(FE_PATH_TO_ASSETS);
      finalPath += path;
      if(!texture.loadFromFile(finalPath))
      {
        std::cout << "could not load texture from path:" << finalPath << " trying to load default texture for ui component." << std::endl;
        texture.loadFromFile(UI_COMPONENT_TEXTURE_DEFAULT);
      }
    }
  public:
      virtual void render(sf::RenderWindow& window) = 0;
  };
}

#endif
