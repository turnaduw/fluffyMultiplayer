#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailed::StateFailed(std::string text,FluffyMultiplayer::AppState* s,std::string* request=nullptr)
  {
    outputStateCount=1;
    requestData = request;
    state1=s;
    state2=nullptr;
    state3=nullptr;
    requestData=request;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Failed: "+text);
  }

  StateFailed::StateFailed(std::string text,FluffyMultiplayer::AppState* s1,
                           FluffyMultiplayer::AppState* s2,std::string* request=nullptr)
 {
   StateFailed(text,s1,request);
   outputStateCount=2;
   state2=s2;
   state3=nullptr;
 }

  StateFailed::StateFailed(std::string text,FluffyMultiplayer::AppState* s1,
                           FluffyMultiplayer::AppState* s2,
                           FluffyMultiplayer::AppState* s3,std::string* request=nullptr)
  {
    StateFailed(text,s1,s2,request);
    outputStateCount=3;
    state3=s3;
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
    switch (outputStateCount)
    {
      case 1:
      {

      }break;

      case 2:
      {

      }break;

      case 3:
      {

      }break;
    }
    return this;
  }


  FluffyMultiplayer::AppState* StateFailed::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
