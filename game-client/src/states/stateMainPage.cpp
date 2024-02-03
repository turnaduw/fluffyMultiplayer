#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateMainPage::StateMainPage(FluffyMultiplayer::App& app)
  {
    std::cout << "statemainPage constructor called=======================\n";
    app.currentGameMode = new FluffyMultiplayer::GM_MENSCH(app.appWindow,app.lobby);
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    std::string txttemp = "lobbyId:"+std::to_string(app.lobby->id);
    initSimpleText(fontPath, txttemp);
    setSimpleTextPosition(150.0, 5.0);

    //example
    float startX=200.0;
    float startY=100.0;
    float eachXstep=0.0;
    float eachYstep=30.0;
    std::array<std::string,MAX_PLAYERS_IN_LOBBY> tempNames = {"peter","alex","mamad","joker","Yray"};
    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      playerList[i] = FluffyMultiplayer::PlayerList(i+1,tempNames[i],startX,startY);
      startX+=eachXstep;
      startY+=eachYstep;
    }
  }

  StateMainPage::~StateMainPage()
  {

  }

  void StateMainPage::render(sf::RenderWindow& window)
  {
    window.draw(theText);

    //player list
    // for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    // {
      // playerList[i].render(window);
    // }
    //chat box

    //game..

  }

  FluffyMultiplayer::AppState* StateMainPage::update(FluffyMultiplayer::App& app)
  {
    //read from received data..
    FluffyMultiplayer::SocketReceiveData currentItem;
    if(app.receivedTextDataList.size()>1)
      for(int i=0; i<app.receivedTextDataList.size(); i++)
      {
        currentItem = app.receivedTextDataList.front();
        switch(currentItem.code)
        {
          case RESPONSE_YOU_ARE_JOINT_INTO_LOBBY:
          {
            app.log.print("joint into lobby.", FluffyMultiplayer::LogType::Information);
          }break;

          default:
          {
            std::cout << "passing vlaue into gamemode ................\n";
            //apply commands from server into client game
            if(app.currentGameMode!=nullptr)
              app.currentGameMode->update(currentItem);
          }
        }


        //remove proccess item
         app.receivedTextDataList.pop();
      }


    return this;
  }


  FluffyMultiplayer::AppState* StateMainPage::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
