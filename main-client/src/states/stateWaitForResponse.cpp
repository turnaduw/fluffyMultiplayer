#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateWaitForResponse::StateWaitForResponse(std::string _text, FluffyMultiplayer::AppState* retryState,
                       FluffyMultiplayer::AppState* acceptedState,
                       int responseCodeAccepts)
  {
    timeoutCounter=MC_REQUEST_TIMEOUT;
    state1 = retryState;
    state2 = acceptedState;
    responseCodeAcceptor = responseCodeAccepts;
    buttonRetryPressed=false;


    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    text = "Wait for response:\n"+ _text;
    initSimpleText(fontPath, text);

    timeouttxt.setFont(theFont);
    timeouttxt.setString("timedout press enter to retry.");
  }

  StateWaitForResponse::~StateWaitForResponse()
  {

  }

  int StateWaitForResponse::checkResponseCode(const std::string& data)
  {
    std::string tempStr = data.substr(MC_RESPONSE_POSITION_MIN_INDEX,MC_RESPONSE_POSITION_MAX_INDEX);
    const char* temp = tempStr.c_str();
    int code = std::atoi(temp);
    if(code>=MC_MINUMUM_RESPONSE_CODE)
      return code;
    return -1;
  }

  void StateWaitForResponse::render(sf::RenderWindow& window)
  {
    if(timeoutCounter<=0)
    {
      window.draw(timeouttxt);
    }
    else
    {
      window.draw(theText);
    }
  }


  FluffyMultiplayer::AppState* StateWaitForResponse::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    //do counter minus to make timeout zero and left this state.
    if(timeoutCounter>0)
    {
      timeoutCounter--;
      theText.setString(text+"\nTimeout=("+std::to_string(timeoutCounter)+")");

      //check for received data.
      if(receiveDataQueue.size()>=1)
      {
        data = receiveDataQueue.front();
        receiveDataQueue.pop();
        if(checkResponseCode(data) == responseCodeAcceptor)
          return state2; //accepted
      }
    }
    return this; //keep this state
  }


  FluffyMultiplayer::AppState* StateWaitForResponse::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
          {
              if(timeoutCounter<=0)
                return state1;
          }
        }
        break;
    }
    return this;
  }
}
