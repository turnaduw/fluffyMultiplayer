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
    setSimpleTextPosition(395.0, 90.0);
    buttons[0].init("OK",410.0,200.0, sf::Color::Black, sf::Color::White, 60,30, 22);
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
   setSimpleTextPosition(395.0, 190.0);
   buttons[0].init("Retry",340.0,200.0, sf::Color::White, sf::Color::White, 60,30, 22);
   buttons[1].init("Cancel/Quit",540.0,200.0, sf::Color::White, sf::Color::White, 60,30, 22);
 }

  StateFailed::StateFailed(std::string _text,FluffyMultiplayer::AppState* s1,
                           FluffyMultiplayer::AppState* s2,
                           FluffyMultiplayer::AppState* s3,
                           std::string* request=nullptr)
  {
    StateFailed(_text,s1,s2,request);
    outputStateCount=3;
    state3=s3;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    text = "Failed: "+_text;
    initSimpleText(fontPath, text);
    setSimpleTextPosition(395.0, 90.0);
    buttons[0].init("Retry",340.0,200.0, sf::Color::White, sf::Color::White, 60,30, 22);
    buttons[1].init("Cancel/Quit",540.0,200.0, sf::Color::White, sf::Color::White, 60,30, 22);
    buttons[2].init("Skip",440.0,300.0, sf::Color::White, sf::Color::White, 60,30, 22);
  }


  StateFailed::~StateFailed()
  {

  }

  void StateFailed::render(sf::RenderWindow& window)
  {
    window.draw(theText);
    switch (outputStateCount)
    {
      case 1:
      {
        buttons[0].render(window);
      }break;

      case 2:
      {
        buttons[0].render(window);
        buttons[1].render(window);
      }break;

      case 3:
      {
        buttons[0].render(window);
        buttons[1].render(window);
        buttons[2].render(window);
      }break;
    }
  }


  FluffyMultiplayer::AppState* StateFailed::update(FluffyMultiplayer::App& app)
  {
    return this;
  }


  FluffyMultiplayer::AppState* StateFailed::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        if(buttons[0].getButtonBound().contains(mousePosition))
        {
          return state1;
        }
        else if(buttons[1].getButtonBound().contains(mousePosition))
        {
          return state2;
        }
        else if(buttons[2].getButtonBound().contains(mousePosition))
        {
          return state3;
        }
    }


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
              {
                if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
                  return state1;
              }
            }break;
            case 2:
            {
              if(state1!=nullptr && state2!=nullptr)
              {
                if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
                  return state1;
                else if(event.key.code == sf::Keyboard::Space)
                  return state2;
              }
            }break;
            case 3:
            {
              if(state1!=nullptr && state2!=nullptr && state3!=nullptr)
              {
                if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
                  return state1;
                else if(event.key.code == sf::Keyboard::Space)
                  return state2;
                else if(event.key.code == sf::Keyboard::Tab)
                  return state3;
              }
            }break;
          }//switch end
        }break;
    }//switch end
    return this;
  }
}
