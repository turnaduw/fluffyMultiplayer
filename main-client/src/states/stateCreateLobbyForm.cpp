#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateCreateLobbyForm::StateCreateLobbyForm()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state createLobbyForm, press enter to submit, Escape to cancel\n");
  }

  StateCreateLobbyForm::StateCreateLobbyForm(FluffyMultiplayer::CreateLobbyFormData pastLobbyInfo)
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state createLobbyForm, press enter to submit, Escape to cancel\n");
    lobbyData = pastLobbyInfo;

    //set pastlobbyinfo into form.
  }

  StateCreateLobbyForm::~StateCreateLobbyForm()
  {

  }

  void StateCreateLobbyForm::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateCreateLobbyForm::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateCreateLobbyForm::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
          {
            //create lobby
            return new FluffyMultiplayer::StateWaitForResponse //will break loop
            (
              "waiting for response from server\nto create lobby.\nplease wait..",
              new FluffyMultiplayer::StateFailed("failed to create lobby..", this, new FluffyMultiplayer::StateEnd ,nullptr),
              lobbyData,
              new FluffyMultiplayer::StateFailed("cannot createlobby your account is limited\n", new FluffyMultiplayer::StateMainPage ,nullptr),
              MS_ERROR_FAILED_TO_LOBBY_CREATION_FORBIDDEN_FOR_YOU,
              new FluffyMultiplayer::StateJoinLobby(lobbyData.address),
              MS_RESPONSE_SUCCESS_LOBBY_CREATED
            );
          }
          else if(event.key.code == sf::Keyboard::Escape)
          {
            return new FluffyMultiplayer::StateMainPage;
          }
        }
        break;
    }
    return this;
  }
}
