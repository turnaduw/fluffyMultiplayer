#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailed::StateFailed(std::string text, FluffyMultiplayer::AppState* s)
  {
    outputStateCount=1;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Failed: "+text);
  }

  StateFailed::StateFailed(std::string text, FluffyMultiplayer::AppState* s1,
                           FluffyMultiplayer::AppState* s2)
 {
   outputStateCount=2;
   std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
   initSimpleText(fontPath, "Failed: "+text);
 }

  StateFailed::StateFailed(std::string text, FluffyMultiplayer::AppState* s1,
                           FluffyMultiplayer::AppState* s2,
                           FluffyMultiplayer::AppState* s3)
  {
    outputStateCount=3;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Failed: "+text);
  }


  StateFailed::~StateFailed()
  {

  }

  void StateFailed::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateFailed::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    // switch (outputStateCount)
    // {
    //   case 1:
    //   {
    //
    //   }break;
    //
    //   case 2:
    //   {
    //
    //   }break;
    //
    //   case 3:
    //   {
    //
    //   }break;
    // }
    return this;
  }


  FluffyMultiplayer::AppState* StateFailed::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
