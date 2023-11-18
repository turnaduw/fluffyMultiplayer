#include "../../include/states.h"

namespace FluffyMultiplayer
{
  //login form
  StateWaitForResponse::StateWaitForResponse(std::string _text,
    FluffyMultiplayer::AppState* retry,
    FluffyMultiplayer::LoginFormData _loginData,
    FluffyMultiplayer::AppState* bannedstate,
    FluffyMultiplayer::AppState* successstate,
    int bannedCode,int successCode)
    {
      //hold passed data into varaible for when need to pass into another state.
      loginData_ptr = new FluffyMultiplayer::LoginFormData;
      loginData_ptr->_inputs = _loginData._inputs;
      loginData_ptr->_errors = _loginData._errors;
      loginData_ptr->_saveLoginStatus = _loginData._saveLoginStatus;

      requestSent=false; //turn off flag, will help to run receiveDataQueue.push once
      timeoutCounter=MC_REQUEST_TIMEOUT;

      //retry button
      state1 = retry;

      //second button
      state2 = bannedstate;
      responseCodeAcceptor = bannedCode;

      //third button
      state3 = successstate;
      responseCodeAcceptor2 = successCode;

      //split data from LoginFormData into a string req
      std::string temp = std::to_string(MC_REQUEST_LOGIN) +  _loginData._inputs[0]+ MC_REQUEST_DELIMITER;
      temp += _loginData._inputs[1] +MC_REQUEST_DELIMITER;
      temp += "" MC_REQUEST_DELIMITER; //empty identity
      temp += MC_REQUEST_CLOSER;
      requestData = temp;


      std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
      text = "Wait for response:\n"+ _text;
      initSimpleText(fontPath, text);

      timeouttxt.setFont(theFont);
      timeouttxt.setString("timedout press enter to retry.");
    }


  StateWaitForResponse::StateWaitForResponse(std::string _text,
                       const std::string& request,
                       FluffyMultiplayer::AppState* retryState,
                       FluffyMultiplayer::AppState* acceptedState,
                       int responseCodeAccepts)
  {
    loginData_ptr=nullptr;
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

  StateWaitForResponse::StateWaitForResponse(std::string text,
                      const std::string& request,
                      FluffyMultiplayer::AppState* retryState,
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
        int resultRC = checkResponseCode(receivedData);
        if(resultRC == responseCodeAcceptor)
          return state2; //accepted (first state passed) successfully
        else if(resultRC == responseCodeAcceptor2 && state3!=nullptr)
          return state3; //second state passed successfully
        else if(state1==nullptr && loginData_ptr!=nullptr && timeoutCounter<=0)
          return new FluffyMultiplayer::StateLoginForm(*loginData_ptr);
        //else if() //register form
        //else if() //create lobby form
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
                if(state1!=nullptr)
                  return state1;
              }

          }
        }
        break;
    }
    return this;
  }
}
