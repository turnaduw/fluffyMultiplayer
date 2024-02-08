#ifndef H_PLAYERLIST_COMPONENT
#define H_PLAYERLIST_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../config.h"
#include "uiComponent.h"
#include "pictureButton.h"
#include "icon.h"
#include "text.h"
#include "../dataType.h"



namespace FluffyMultiplayer
{
  class PlayerList : public UiComponent
  {
    private:
      float x,y;

      int id;
      std::string name;
      FluffyMultiplayer::Text idText;
      FluffyMultiplayer::Text nameText;


      //status elements
      bool isOwner;
      bool isSpecter;
      bool isAdmin;
      FluffyMultiplayer::Icon ownerIcon;
      FluffyMultiplayer::Icon adminIcon;
      FluffyMultiplayer::Icon specterIcon;




      bool voiceChat;
      bool isMe;

    public:
      //publiced to access into bounds from outside like playerList[i].pictureButtons[j].getButtonBound()
      FluffyMultiplayer::PictureButton voiceChatPB;


      // void setPos(float _x, float _y)
      // {
      //   x = _x;
      //   y = _y;
      // }

      void updateVoiceChatStatus(bool status)
      {
        voiceChat = status;
      }

      void render(sf::RenderWindow& window)
      {
        idText.render(window);
        nameText.render(window);


        if(isOwner)
          ownerIcon.render(window);
        if(isAdmin)
          adminIcon.render(window);
        if(isSpecter)
          specterIcon.render(window);

        if(voiceChat)
          voiceChatPB.render(window);
      }

      void operator=(FluffyMultiplayer::PlayerList other)
      {
          id = other.id;
          name = other.name;
          x = other.x;
          y = other.y;
          isMe = other.isMe;
          voiceChat = other.voiceChat;
          isOwner = other.isOwner;
          isSpecter = other.isSpecter;
          isAdmin = other.isAdmin;
      }

      void init(int playerId, std::string playerName, float _x=0.0, float _y=0.0,
              bool me=false, bool vc=false, bool owner=false, bool specter=false,
              bool admin=false)
      {
        std::string idprint = "("+std::to_string(id)+")";
        if(isMe)
          name += "*****ME" + playerName;

        idText.initText(idprint,x+PLAYER_LIST_ID_PADDING_X, y+PLAYER_LIST_ID_PADDING_Y);
        nameText.initText(name,x+PLAYER_LIST_NAME_PADDING_X, y+PLAYER_LIST_NAME_PADDING_Y);

        voiceChatPB.init("voice", ICON_VOICECHAT, x+PLAYER_LIST_VOICECHAT_PADDING_X , y+PLAYER_LIST_VOICECHAT_PADDING_Y, sf::Color::White,sf::Color::White, 18);
        ownerIcon.initIcon(ICON_OWNER, x+PLAYER_LIST_OWNER_PADDING_X , y+PLAYER_LIST_OWNER_PADDING_Y);
        adminIcon.initIcon(ICON_ADMIN, x+PLAYER_LIST_ADMIN_PADDING_X , y+PLAYER_LIST_ADMIN_PADDING_Y);
        specterIcon.initIcon(ICON_SPECTER, x+PLAYER_LIST_SPECTER_PADDING_X , y+PLAYER_LIST_SPECTER_PADDING_Y);
      }

      PlayerList()
      {

      }

      PlayerList(int playerId, std::string playerName, float _x, float _y)
      {
        init(playerId,playerName,_x,_y);
      }

      PlayerList(int playerId, std::string playerName,
              bool me, bool vc, bool owner, bool specter,
              bool admin)
      {
        init(playerId,playerName,me,vc,owner,specter,admin);
      }

      ~PlayerList()
      {

      }
  };
}

#endif
