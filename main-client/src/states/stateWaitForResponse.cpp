#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateWaitForResponse::StateWaitForResponse(std::string _text,const std::string& request, FluffyMultiplayer::AppState* retryState,
                       FluffyMultiplayer::AppState* acceptedState,
                       int responseCodeAccepts)
  {
    requestSent=false;
    timeoutCounter=MC_REQUEST_TIMEOUT;
    state1 = retryState;
    state2 = acceptedState;
    responseCodeAcceptor = responseCodeAccepts;
    requestData = request;


    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    text = "Wait for response:\n"+ _text;
    initSimpleText(fontPath, text);

    timeouttxt.setFont(theFont);
    timeouttxt.setString("timedout press enter to retry.");
  }

  StateWaitForResponse::StateWaitForResponse(std::string text,const std::string& request, FluffyMultiplayer::AppState* retryState,
                      FluffyMultiplayer::AppState* acceptedState,
                      FluffyMultiplayer::AppState* acceptedState2,
                      int responseCodeAccepts,int responseCodeAccepts2)
  {
    StateWaitForResponse(text,request,retryState,acceptedState,responseCodeAccepts);
    responseCodeAcceptor2 = responseCodeAccepts2;
    state3 = acceptedState2;
  }


  StateWaitForResponse::~StateWaitForResponse()
  {

  }

  int StateWaitForResponse::checkResponseCode(const std::string& _data)
  {
    std::string tempStr = _data.substr(MC_RESPONSE_POSITION_MIN_INDEX,MC_RESPONSE_POSITION_MAX_INDEX);
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
    if(requestSent==false)
      sendDataQueue.push(requestData);
    //do counter minus to make timeout zero and left this state.
    if(timeoutCounter>0)
    {
      timeoutCounter--;
      theText.setString(text+"\nTimeout=("+std::to_string(timeoutCounter)+")");

      //check for received data.
      if(receiveDataQueue.size()>=1)
      {
        receivedData = receiveDataQueue.front();
        receiveDataQueue.pop();
        if(checkResponseCode(receivedData) == responseCodeAcceptor)
          return state2; //accepted
        else if(checkResponseCode(receivedData) == responseCodeAcceptor2
                && state3!=nullptr)
          return state3;
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
              {
                // if(requestData.length()>=1)
                  // return state1();
                return state1;
              }

          }
        }
        break;
    }
    return this;
  }
}
