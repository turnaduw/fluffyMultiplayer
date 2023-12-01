#ifndef H_UI_COMPONENT
#define H_UI_COMPONENT

#include <SFML/Graphics.hpp>

namespace FluffyMultiplayer
{
  class UiComponent
  {
  public:
      virtual void render(sf::RenderWindow& window) = 0;
  };
}

#endif
