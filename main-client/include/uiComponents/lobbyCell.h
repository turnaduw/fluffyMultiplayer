#ifndef H_LOBBY_CELL_COMPONENT
#define H_LOBBY_CELL_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../config.h"
#include "uiComponent.h"
#include "icon.h"
#include "iconText.h"
#include "text.h"
#include "../dataType.h"

namespace FluffyMultiplayer
{
  class LobbyCell : public UiComponent
  {
    private:
      //data
      FluffyMultiplayer::LobbyData lobbyInfo;

      //button
      sf::Sprite button;
      sf::Texture buttonTexture;
      std::string buttonTexturePath;
      sf::FloatRect buttonBound;

      //status elements
      FluffyMultiplayer::Icon iconVoiceChatStatus;
      FluffyMultiplayer::Icon iconTextChatStatus;
      FluffyMultiplayer::Icon iconSpecterStatus;
      FluffyMultiplayer::Icon iconLockedStatus;
      FluffyMultiplayer::IconText iconTextPlayers;
      FluffyMultiplayer::Text textInGameStatus;
      FluffyMultiplayer::Icon iconPrivateLobby;
      FluffyMultiplayer::Icon iconGameMode;


    public:

      sf::FloatRect getButtonBound() const
      {
        return buttonBound;
      }

      FluffyMultiplayer::LobbyData getLobbyData() const
      {
        return lobbyInfo;
      }

      void init(std::vector<std::string> gameModeTextures,
            FluffyMultiplayer::LobbyData lobby_data,float x, float y)
      {
        //load that base rectangle
        buttonTexturePath = std::string(LOBBY_CELL_RECTANGLE_TEXTURE);
        componentLoadTexture(buttonTexture,buttonTexturePath);
        button.setTexture(buttonTexture);
        button.setPosition(x,y);
        // button.rotate(LOBBY_CELL_ROTATE_VALUE);
        buttonBound = button.getGlobalBounds();


        //set received data into local
        lobbyInfo = lobby_data;


        //if lobby info is not private do elements/status init
        if(lobbyInfo.id>0)
        {
          if(lobbyInfo.showLobbyInList)
          {
            if(lobbyInfo.isVoiceChatForbidden)
            {
              iconVoiceChatStatus.initIcon
              (
                LOBBY_CELL_INFO_VOICECHAT_DISABLED_TEXTURE,
                x LOBBY_CELL_VOICE_STATUS_PADDING_X,
                y LOBBY_CELL_VOICE_STATUS_PADDING_Y
              );
            }
            else
            {
              iconVoiceChatStatus.initIcon
              (
                LOBBY_CELL_INFO_VOICECHAT_ENABLED_TEXTURE,
                x LOBBY_CELL_VOICE_STATUS_PADDING_X,
                y LOBBY_CELL_VOICE_STATUS_PADDING_Y
              );
            }

            if(lobbyInfo.isTextChatForbidden)
            {
              iconTextChatStatus.initIcon
              (
                LOBBY_CELL_INFO_TEXTCHAT_DISABLED_TEXTURE,
                x LOBBY_CELL_TEXT_STATUS_PADDING_X,
                y LOBBY_CELL_TEXT_STATUS_PADDING_Y
              );
            }
            else
            {
              iconTextChatStatus.initIcon
              (
                LOBBY_CELL_INFO_TEXTCHAT_ENABLED_TEXTURE,
                x LOBBY_CELL_TEXT_STATUS_PADDING_X,
                y LOBBY_CELL_TEXT_STATUS_PADDING_Y
              );
            }


            if(lobbyInfo.isSpecterForbidden)
            {
              iconSpecterStatus.initIcon
              (
                LOBBY_CELL_INFO_SPECTER_DISABLED_TEXTURE,
                x LOBBY_CELL_SPECTER_STATUS_PADDING_X,
                y LOBBY_CELL_SPECTER_STATUS_PADDING_Y
              );
            }
            else
            {
              iconSpecterStatus.initIcon
              (
                LOBBY_CELL_INFO_SPECTER_ENABLED_TEXTURE,
                x LOBBY_CELL_SPECTER_STATUS_PADDING_X,
                y LOBBY_CELL_SPECTER_STATUS_PADDING_Y
               );
            }

            iconTextPlayers.initIconText
            (
              std::string
              (
                std::to_string(lobbyInfo.currentPlayers)
                + "/" +
                std::to_string(lobbyInfo.maxPlayers)
              ),
              LOBBY_CELL_INFO_PLAYERS_STATUS_TEXTURE,
              x LOBBY_CELL_PLAYERS_STATUS_PADDING_X,
              y LOBBY_CELL_PLAYERS_STATUS_PADDING_Y
            );
            iconTextPlayers.setFontSize(LOBBY_CELL_PLAYERS_STATUS_FONT_SIZE);


            textInGameStatus.initText
            (
              (lobbyInfo.lobbyStatusInGame==true ? LOBBY_CELL_INGAME_STATUS_TRUE : LOBBY_CELL_INGAME_STATUS_FALSE),
              x LOBBY_CELL_INGAME_STATUS_PADDING_X,
              y LOBBY_CELL_INGAME_STATUS_PADDING_Y
            );
            textInGameStatus.setFontSize(LOBBY_CELL_INGAME_STATUS_FONT_SIZE);

            if(lobbyInfo.isLocked)
            {
              iconLockedStatus.initIcon
              (
                LOBBY_CELL_INFO_LOCKED_LOBBY_TEXTURE,
                x LOBBY_CELL_LOCKED_STATUS_PADDING_X,
                y LOBBY_CELL_LOCKED_STATUS_PADDING_Y
              );
            }

            iconGameMode.initIcon
            (
              gameModeTextures[lobbyInfo.gameMode],
              x LOBBY_CELL_GAMEMODE_STATUS_PADDING_X,
              y LOBBY_CELL_GAMEMODE_STATUS_PADDING_Y
            );
          }
          //when lobby is set to dont report lobby info to lobby list show a single icon in center
          else
          {
            iconPrivateLobby.initIcon
            (
              LOBBY_CELL_INFO_PRIVATE_LOBBY_TEXTURE,
              x LOBBY_CELL_PRIVATE_STATUS_PADDING_X,
              y LOBBY_CELL_PRIVATE_STATUS_PADDING_Y
            );
          }
        }
        else
          std::cout << "lobbyCell init -> invalid lobby id (id<=0)" << std::endl;





        //rotate all inited elements
        // iconVoiceChatStatus.rotate(LOBBY_CELL_ROTATE_VALUE);
        // iconTextChatStatus.rotate(LOBBY_CELL_ROTATE_VALUE);
        // iconSpecterStatus.rotate(LOBBY_CELL_ROTATE_VALUE);
        // iconTextPlayers.rotate(LOBBY_CELL_ROTATE_VALUE);
        // textInGameStatus.rotate(LOBBY_CELL_ROTATE_VALUE);
        // iconLockedStatus.rotate(LOBBY_CELL_ROTATE_VALUE);
        // iconGameMode.rotate(LOBBY_CELL_ROTATE_VALUE);
        // iconPrivateLobby.rotate(LOBBY_CELL_ROTATE_VALUE);
      }

      void render(sf::RenderWindow& window)
      {
        //render base
        window.draw(button);

        //if lobby id is zero so that lobby is invalid (not created) just draw simple button
        if(lobbyInfo.id>0)
        {
          //render elemnts to show status of lobby
          if(lobbyInfo.showLobbyInList)
          {
            iconVoiceChatStatus.render(window);
            iconTextChatStatus.render(window);
            iconSpecterStatus.render(window);
            iconTextPlayers.render(window);
            textInGameStatus.render(window);
            iconLockedStatus.render(window);
            iconGameMode.render(window);
          }
          else //if lobby is disabled to report status just draw this
          {
            iconPrivateLobby.render(window);
          }
        }
      }

      LobbyCell(std::vector<std::string> gameModeTexturesList,
                FluffyMultiplayer::LobbyData data,
                float x,float y)
      {
        init(gameModeTexturesList,data,x,y);
      }

      LobbyCell()
      {

      }

      ~LobbyCell()
      {

      }
  };
}

#endif
