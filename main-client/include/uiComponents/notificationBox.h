#ifndef H_NOTIFICATION_COMPONENT
#define H_NOTIFICATION_COMPONENT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "../config.h"
#include "../dataType.h"

#include "uiComponent.h"

#include "icon.h"
#include "text.h"
#include "pictureButton.h"

namespace FluffyMultiplayer
{
  class NotificationBox : public UiComponent
  {
    private:

      //that element draw under all if clicked on that pop/close popup/notifications
      //this helps to make client limit, to must close box then do action/click or .. on ui
      sf::Texture backOfBackgroundTexture;
      sf::Sprite backOfBackgroundSprite;
      sf::FloatRect backOfBackgroundBound;

      FluffyMultiplayer::Icon bgIcon;
      FluffyMultiplayer::Text titleText;
      FluffyMultiplayer::Text messageText;
      FluffyMultiplayer::NotificationData notificationData;
      bool boxClosed;

      int x,y;
      sf::Color bgColor, fgColor;

    public:

      //because need to call method getbound on app.cpp for check for clicks must be public
      FluffyMultiplayer::PictureButton closeButton;
      FluffyMultiplayer::PictureButton copyButton;

      void init(FluffyMultiplayer::NotificationData data, sf::Vector2u windowSize)
      {
          notificationData = data;
          boxClosed=false;
          fgColor = sf::Color::White;

          //set position
          switch (notificationData.position)
          {
            case FluffyMultiplayer::NotificationPosition::center:
            {
              x= static_cast<float>(windowSize.x/2);
              y= static_cast<float>(windowSize.y/2);
            }break;
            case FluffyMultiplayer::NotificationPosition::bottomLeft:
            {
              x= 0.0;
              y= static_cast<float>(windowSize.y);
            }break;
            case FluffyMultiplayer::NotificationPosition::bottomRight:
            {
              x= static_cast<float>(windowSize.x);
              y= static_cast<float>(windowSize.y);
            }break;
            case FluffyMultiplayer::NotificationPosition::bottomCenter:
            {
              x= static_cast<float>(windowSize.x/2);
              y= static_cast<float>(windowSize.y);
            }break;
            default:
            {
              x= static_cast<float>(windowSize.x/2);
              y= static_cast<float>(windowSize.y/2);
            }break; //unknown notification position..
          }


          //minus half of width and height background texture size
          //to make element center (due to origin things.)
          x -= bgIcon.iconTexture.getSize().x/2;
          y -= bgIcon.iconTexture.getSize().y/2;



          //make a dynamic size to create texture and set position to B.O.B sprite
          int size_bob_width = (windowSize.x/100)*NOTIFICATIONBOX_BACK_OF_BACKGROUND_WIDTH_PERCENT;
          int size_bob_height = (windowSize.y/100)* NOTIFICATIONBOX_BACK_OF_BACKGROUND_HEIGHT_PERCENT;

          // create an empty texture
          backOfBackgroundTexture.create(size_bob_width, size_bob_height);

          //backOfBackground init
          backOfBackgroundSprite.setTexture(backOfBackgroundTexture);
          backOfBackgroundSprite.setColor(NOTIFICATIONBOX_BACK_OF_BACKGROUND_COLOR);
          backOfBackgroundSprite.setPosition(windowSize.x-size_bob_width, windowSize.y-size_bob_height);
          backOfBackgroundBound = backOfBackgroundSprite.getGlobalBounds();

          //set color
          switch (notificationData.type)
          {
            case FluffyMultiplayer::NotificationType::normal : bgColor = sf::Color::White; break;
            case FluffyMultiplayer::NotificationType::error : bgColor = sf::Color::White; break;
            case FluffyMultiplayer::NotificationType::success : bgColor = sf::Color::White; break;
            case FluffyMultiplayer::NotificationType::warning : bgColor = sf::Color::White; break;
            default: bgColor = sf::Color::White; break; //unkwon notification type..
          }

          //icon init
          bgIcon.initIcon
          (
            NOTIFICATIONBOX_BACKGROUND_TEXTURE,
            x NOTIFICATIONBOX_BACKGROUND_PADDING_X,
            y NOTIFICATIONBOX_BACKGROUND_PADDING_Y
          );
          bgIcon.icon.setColor(bgColor);

          //texts init
          titleText.initText
          (
            notificationData.title + " " + std::to_string(notificationData.code),
            x NOTIFICATIONBOX_TITLE_PADDING_X,
            y NOTIFICATIONBOX_TITLE_PADDING_Y
          );
          titleText.setFontSize(NOTIFICATIONBOX_TITLE_FONT_SIZE);
          // titleText.setTextColor(fgColor); //before this method have to implement in text.h

          messageText.initText
          (
            notificationData.message,
            x NOTIFICATIONBOX_MESSAGE_PADDING_X,
            y NOTIFICATIONBOX_MESSAGE_PADDING_Y
          );
          messageText.setFontSize(NOTIFICATIONBOX_MESSAGE_FONT_SIZE);
          // messageText.setTextColor(fgColor); //before this method have to implement in text.h


          //buttons init
          closeButton.init("", NOTIFICATIONBOX_CLOSE_BUTTON_TEXTURE, x + NOTIFICATIONBOX_CLOSEBUTTON_PADDING_X, y + NOTIFICATIONBOX_CLOSEBUTTON_PADDING_Y,
                bgColor,fgColor, 1);
          copyButton.init("", NOTIFICATIONBOX_COPY_ERROR_BUTTON_TEXTURE , x + NOTIFICATIONBOX_COPYBUTTON_PADDING_X, y + NOTIFICATIONBOX_COPYBUTTON_PADDING_Y,
                bgColor,fgColor, 1);
      }

      sf::FloatRect getBackofBackgroundBound()
      {
          return backOfBackgroundBound;
      }

      void closeBox()
      {
        boxClosed=true;
      }

      std::string copyError()
      {
        return "error code=" + std::to_string(notificationData.code) + " message:" + notificationData.message;
      }

      NotificationBox()
      {

      }

      ~NotificationBox()
      {

      }

      void render(sf::RenderWindow& window)
      {
        if(!boxClosed)
        {
          window.draw(backOfBackgroundSprite);
          bgIcon.render(window);
          titleText.render(window);
          messageText.render(window);
          closeButton.render(window);
          copyButton.render(window);
        }
      }


  };
}

#endif
