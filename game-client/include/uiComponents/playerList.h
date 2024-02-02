#ifndef H_PLAYERLIST_COMPONENT
#define H_PLAYERLIST_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../config.h"
#include "uiComponent.h"
#include "pictureButton.h"
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
      std::array<FluffyMultiplayer::Text,PL_EXISTS_LABELS>labels;

      //status elements
      bool voiceChat;
      bool isOwner;
      bool isSpecter;
      bool isAdmin;
      bool isMe;



    public:
      //publiced to access into bounds from outside like playerList[i].pictureButtons[j].getButtonBound()
      std::array<FluffyMultiplayer::PictureButton,PL_MAX_PICTUREBUTTONS> pictureButtons;

      void setPos(float _x, float _y)
      {
        x = _x;
        y = _y;
      }

      void render(sf::RenderWindow& window)
      {
        for(int i=0; i<PL_EXISTS_LABELS; i++)
          labels[i].render(window);

        //render elemnts to show status of player
        for(int i=0; i<PL_MAX_PICTUREBUTTONS; i++)
          pictureButtons[i].render(window);

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

      void init(int playerId, std::string playerName, float _x, float _y)
      {
        PlayerList(playerId,playerName,_x,_y);
      }
      PlayerList()
      {
        PlayerList(0,"?",0.0,0.0);
      }
      PlayerList(int playerId, std::string playerName, float _x, float _y)
        : id(playerId), name(playerName), x(_x), y(_y)
      {
        PlayerList(id,name,x,y,false,false,false,false,false);
      }
      PlayerList(int playerId, std::string playerName, float _x, float _y,
              bool me, bool vc=false, bool owner=false, bool specter=false,
              bool admin=false)
                : id(playerId), name(playerName), x(_x), y(_y),
                  isMe(me), voiceChat(vc), isOwner(owner),
                  isSpecter(specter), isAdmin(admin)
      {
        std::string idprint = "("+std::to_string(id)+")";
        if(isMe)
          name += "*****ME";


        // labels[0]= FluffyMultiplayer::Text(idprint,x+PLAYER_LIST_LABEL_ID_PADDING_X,y+PLAYER_LIST_LABEL_ID_PADDING_Y);
        // labels[1] = FluffyMultiplayer::Text(name,x+PLAYER_LIST_LABEL_NAME_PADDING_X,y+PLAYER_LIST_LABEL_NAME_PADDING_Y);
        labels[0].initText(idprint,200.0,20.0);
        labels[1].initText(name,200.0,90.0);

        float ytools = 25.0;
        pictureButtons[0].init("voice", PICTURE_BUTTON_REFRESH_LOBBY_LIST_TEXTURE , 867.0,ytools, sf::Color::Black,sf::Color::White, 18);
        pictureButtons[1].init("owner", ICON_OWNER , 867.0,ytools, sf::Color::Black,sf::Color::White, 18);
        pictureButtons[2].init("admin", ICON_ADMIN , 867.0,ytools, sf::Color::Black,sf::Color::White, 18);
        pictureButtons[3].init("specter", ICON_SPECTER , 867.0,ytools, sf::Color::Black,sf::Color::White, 18);

        //status and buttons
        // if(voiceChat)
          // pictureButtons[0] = FluffyMultiplayer::PictureButton("voice",ICON_VOICECHAT, x+PLAYER_LIST_PICBUTTON_VOICECHAT_PADDING_X,y+PLAYER_LIST_PICBUTTON_VOICECHAT_PADDING_Y);

        // if(isOwner)
          // pictureButtons[1] = FluffyMultiplayer::PictureButton("owner",ICON_OWNER, x+PLAYER_LIST_PICBUTTON_OWNER_PADDING_X, y+PLAYER_LIST_PICBUTTON_OWNER_PADDING_Y);

        // if(isAdmin)
          // pictureButtons[2] = FluffyMultiplayer::PictureButton("admin",ICON_ADMIN,x+PLAYER_LIST_PICBUTTON_ADMIN_PADDING_X,y+PLAYER_LIST_PICBUTTON_ADMIN_PADDING_Y);

        // if(isSpecter)
          // pictureButtons[3] = FluffyMultiplayer::PictureButton("specter",ICON_SPECTER, x+PLAYER_LIST_PICBUTTON_SPECTER_PADDING_X,y+PLAYER_LIST_PICBUTTON_SPECTER_PADDING_Y);
      }

      ~PlayerList()
      {

      }
  };
}

#endif
