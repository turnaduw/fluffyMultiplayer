#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateFailed::StateFailed(std::string _text,FluffyMultiplayer::AppState* s,std::string* request=nullptr)
  {
    outputStateCount=1;
    requestData = request;
    state1=s;
    state2=nullptr;
    state3=nullptr;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    text = "Failed: "+_text;
    initSimpleText(fontPath, text);
  }

  StateFailed::StateFailed(std::string _text,FluffyMultiplayer::AppState* s1,
                           FluffyMultiplayer::AppState* s2,std::string* request=nullptr)
 {
   StateFailed(_text,s1,request);
   outputStateCount=2;
   state2=s2;
   state3=nullptr;
   std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
   text = "Failed: "+_text;
   initSimpleText(fontPath, text);
 }

  StateFailed::StateFailed(std::string _text,FluffyMultiplayer::AppState* s1,
                           FluffyMultiplayer::AppState* s2,
                           FluffyMultiplayer::AppState* s3,std::string* request=nullptr)
  {
    StateFailed(_text,s1,s2,request);
    outputStateCount=3;
    state3=s3;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    text = "Failed: "+_text;
    initSimpleText(fontPath, text);
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
    return this;
  }


  FluffyMultiplayer::AppState* StateFailed::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    switch(event.type)
    {
      //keyboard
        case sf::Event::KeyPressed:
        {
          switch (outputStateCount)
          {
            case 1:
            {
              if(state1!=nullptr)
                return state1;
            }break;
            case 2:
            {
              if(state1!=nullptr && state2!=nullptr)
              {
                if(event.key.code == sf::Keyboard::Enter)
                  return state1;
                else
                  return state2;
              }
            }break;
            case 3:
            {
              if(state1!=nullptr && state2!=nullptr && state3!=nullptr)
              {
                if(event.key.code == sf::Keyboard::Enter)
                  return state1;
                else if(event.key.code == sf::Keyboard::Space)
                  return state2;
                else
                  return state3;
              }
            }break;
          }//switch end
        }break;
    }//switch end
    return this;
  }
}
