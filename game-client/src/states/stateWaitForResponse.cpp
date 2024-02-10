#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateWaitForResponse::StateWaitForResponse(std::string _text,
                      FluffyMultiplayer::AppState* _retryState,
                      std::vector<FluffyMultiplayer::AppState*> _states,
                      std::vector<int> _responseCodes)
  {
    timeoutCounter=MC_REQUEST_TIMEOUT;
    retryState=_retryState;
    states = _states;
    responseCodes = _responseCodes;

    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    text = "Wait for response:\n"+ _text;
    initSimpleText(fontPath, text);

    timeouttxt.setFont(theFont);
    timeouttxt.setString("Timedout press enter to retry.");
    timeouttxt.setPosition(340.0, 190.0);
    buttonRetry.init("  Retry", 420.0,300.0, sf::Color::Black,sf::Color::White, 60,30, 22);
  }


  StateWaitForResponse::~StateWaitForResponse()
  {

  }

  std::string StateWaitForResponse::getResponseCodeMessage(const int& code)
  {
    switch (code)
    {
      // ------------------------- responses, range: 201 -> 500
      case RESPONSE_CONNECTION_ACCEPTED: return "connection accepted"; //to sender (connection accepted not mean joint lobby)
      case RESPONSE_PLAYER_RECONNECTED_INTO_LOBBY: return "player reconnected into lobby"; //to all
      case RESPONSE_PLAYER_DISCONNECTED: return "player disconnected";//to all
      case RESPONSE_PLAYER_JOINT_INTO_LOBBY: return "player joint into lobby";//to all (correct password)
      case RESPONSE_YOU_ARE_JOINT_INTO_LOBBY: return "you are joint into lobby";
      case RESPONSE_PLAYER_KICKED_FROM_LOBBY: return "player kicked from lobby"; //to all
      case RESPONSE_PLAYER_BANNED_FROM_LOBBY: return "player banned from lobby"; //to all
      case RESPONSE_GAME_STOPPED: return "game stopped"; //to all
      case RESPONSE_GAME_STARTED: return "game started"; //to all
      case RESPONSE_PLAYER_VOICE_CHAT_ENABLED: return "voice chat enabled"; // to all
      case RESPONSE_PLAYER_VOICE_CHAT_DISABLED: return "voice chat disabled"; // to all
      case RESPONSE_PLAYER_SENT_VOICE_MESSAGE: return "voice message sent/received"; // to all
      case RESPONSE_PLAYER_SENT_TEXT_MESSAGE: return "text message sent/received";  // to all
      case RESPONSE_PLAYER_CONNECTION_LOST: return "player connection lost"; // to all
      case RESPONSE_LOBBY_DELETED: return "lobby has been deleted"; //to all
      case RESPONSE_LOBBY_SETTINGS_UPDATED: return "lobby settings updated"; //to all
      case RESPONSE_LOBBY_SETTINGS_IS: return "lobby setting received from server";

      case RESPONSE_UNKNOWN_REQUEST_GAME_PAUSED_OR_NOT_STARTED: return "game is paused or not started";
      case RESPONSE_UNKNOWN_REQUEST_GAME_IS_NOT_STARTED: return "game is not started";

      // = = = errors 301 (to sender)
      case RESPONSE_ERROR_CONNECTION_EXISTS: return "connection exists";
      case RESPONSE_ERROR_CONNECTION_BLOCKED: return "connection blocked";//maybe because of spam
      case RESPONSE_ERROR_CONNECTION_REJECTED: return "connection rejected";
      case RESPONSE_ERROR_CONNECTION_NOT_EXISTS: return "connection not exists";
      // case RESPONSE_ERROR_CONNECTION_USING_VPN_FORBIDDEN: return "using vpn is forbidden";
      case RESPONSE_ERROR_RECONNECT_INVALID_IDENTITY: return "failed to reconnect invalid identity";
      case RESPONSE_ERROR_DISCONNECT_YOU_ARE_NOT_CONNECTED: return "you are not connected";
      case RESPONSE_ERROR_JOIN_LOBBY_PASSWORD_INCORRECT: return "incorrect lobby password";
      case RESPONSE_ERROR_JOIN_LOBBY_INVALID_IDENTITY: return "invalid identity"; //identity not found
      case RESPONSE_ERROR_JOIN_LOBBY_YOU_ARE_BANNED: return "you are banned";
      case RESPONSE_ERROR_JOIN_LOBBY_YOU_ARE_ALREADY_JOINT: return "you are already in lobby";
      case RESPONSE_ERROR_GET_LOBBY_SETTINGS_NO_PERMISSION: return "no permission to get lobby settings";
      case RESPONSE_ERROR_UPDATE_LOBBY_SETTINGS_NO_PERMISSION: return "no permission to update lobby settings";
      case RESPONSE_ERROR_START_GAME_NO_PERMISSION: return "no permission to start game";
      case RESPONSE_ERROR_START_GAME_ALREADY_RUN: return "game is running";
      case RESPONSE_ERROR_STOP_GAME_NO_PERMISSION: return "no permission to stop game";
      case RESPONSE_ERROR_STOP_GAME_NOT_STARTED: return "game is not running";
      case RESPONSE_ERROR_DELETE_LOBBY_NO_PERMISSION: return "no permission to delete lobby";
      case RESPONSE_ERROR_KICK_PLAYER_NO_PERMISSION: return "no permission to kick player";
      case RESPONSE_ERROR_KICK_PLAYER_INVALID_TARGET: return "target not found to kick from lobby";
      case RESPONSE_ERROR_BAN_PLAYER_NO_PERMISSION: return "no permission to ban player from lobby";
      case RESPONSE_ERROR_BAN_PLAYER_INVALID_TARGET: return "target not found to ban from lobby";
      case RESPONSE_ERROR_TRANSFER_OWNERSHIP_NO_PERMISSION: return "no permission to change lobby ownership";
      case RESPONSE_ERROR_TRANSFER_OWNERSHIP_INVALID_TARGET: return "target not found to give him ownership";
      case RESPONSE_ERROR_SEND_TEXT_CHAT_DISABLED: return "text chat is disabled on this lobby";
      case RESPONSE_ERROR_SEND_VOICE_CHAT_DISABLED: return "voice chat is disabled on this lobby";
      case RESPONSE_ERROR_INVALID_DATA_SYNTAX: return "invalid data syntax";
      case RESPONSE_ERROR_YOUR_GAME_CLIENT_VERSION_IS_OUT_OF_DATE: return "your game client version is out of date";

      // = = = internal errors 401 (to sender)
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_CONNECT: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_DISCONNECT: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_RECONNECT: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_JOIN_INTO_LOBBY: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_GET_LOBBY_SETTINGS: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_UPDATE_LOBBY_SETTINGS: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_START_GAME: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_STOP_GAME: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_DELETE_LOBBY: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_KICK_PLAYER: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_BAN_PLAYER: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_TRANSFER_LOBBY_OWNERSHIP: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_TEXT_CHAT: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_VOICE_CHAT: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_ENABLE_VOICE_CHAT: return "internal error...";
      case RESPONSE_INTERNAL_ERROR_FAILED_TO_DISABLE_VOICE_CHAT: return "internal error...";
      //---------------------------------------------------------------
      default: return "unknown error code [1].";
    }
    return "unkonwn error code [2].";
  }

  void StateWaitForResponse::render(sf::RenderWindow& window)
  {
    if(timeoutCounter<=0)
    {
      window.draw(timeouttxt);
      buttonRetry.render(window);
    }
    else
    {
      window.draw(theText);
    }
  }


  FluffyMultiplayer::AppState* StateWaitForResponse::update(FluffyMultiplayer::App& app)
  {
    //do counter minus to make timeout zero and left this state.
    if(timeoutCounter>0)
    {
      timeoutCounter--;
      theText.setString(text+"\nTimeout=("+std::to_string(timeoutCounter)+")");

      //check for received data.
      if(app.receivedTextDataList.size()>=1)
      {
          receivedData = app.receivedTextDataList.front();
          app.receivedTextDataList.pop();

          for(int i = 0; i < responseCodes.size(); i++)
              if(receivedData.code == responseCodes[i])
              {
                if(!app.inLobby && receivedData.code == RESPONSE_YOU_ARE_JOINT_INTO_LOBBY) //to avoid render gameMode when not joint in lobby
                  app.inLobby=true;
                return states[i];
              }


          //PUSH INTO Notification BOX. THOSE RESPONSE DONT HAVE ACTION LIKE RETRY OR .. JUST WANT TO SHOW TO CLIENT WILL PUSH AS Notification
          if(receivedData.code>=MC_MINUMUM_RESPONSE_CODE)
          {
            if(MC_SHOW_ERROR_NOTIFICATIONS &&
                  receivedData.code >= MC_ERROR_RESPONSE_CODE_MIN &&
                  receivedData.code <= MC_ERROR_RESPONSE_CODE_MAX)
            {
              app.notificationQueue.push
              (
                FluffyMultiplayer::NotificationData
                {
                  receivedData.code,"error",getResponseCodeMessage(receivedData.code),
                  FluffyMultiplayer::NotificationType::error,
                  FluffyMultiplayer::NotificationPosition::center
                }
              );
            }

            if(MC_SHOW_SUCCESS_NOTIFICATIONS &&
                  receivedData.code >= MC_SUCCESS_RESPONSE_CODE_MIN &&
                  receivedData.code <= MC_SUCCESS_RESPONSE_CODE_MAX)
            {
              app.notificationQueue.push
              (
                FluffyMultiplayer::NotificationData
                {
                  receivedData.code,"success",getResponseCodeMessage(receivedData.code),
                  FluffyMultiplayer::NotificationType::success,
                  FluffyMultiplayer::NotificationPosition::bottomRight
                }
              );
            }
          }

      }
    }
    return this; //keep this state
  }


  FluffyMultiplayer::AppState* StateWaitForResponse::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        if(buttonRetry.getButtonBound().contains(mousePosition))
          return retryState;
    }

    switch(event.type)
    {
        //keyboard
        case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
          {
              if(timeoutCounter<=0)
                return retryState;
          }
        }
        break;
    }
    return this;
  }
}
