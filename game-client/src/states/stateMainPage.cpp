#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateMainPage::StateMainPage(FluffyMultiplayer::App& app)
  {
    app.currentGameMode = new FluffyMultiplayer::GM_MENSCH;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    std::string txttemp = "lobbyId:"+std::to_string(app.lobby->id);
    initSimpleText(fontPath, txttemp);
    setSimpleTextPosition(150.0, 5.0);
    testPictureButton.init("piece",ICON_PIECE,300.0,150.0,sf::Color::Black,sf::Color::White,10);
    std::vector<FluffyMultiplayer::PictureButton> pi;

    testk.initText("TESTESTESTK",200.0,100.0);
    playerlisttest.init(5,"TESTA",200.0,200.0);
    playerlistest2 = new FluffyMultiplayer::PlayerList(6,"TESTB",200.0,300.0);

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

    playerList[0] = FluffyMultiplayer::PlayerList(1,tempNames[0],200.0,50.0);

  }

  StateMainPage::~StateMainPage()
  {

  }

  void StateMainPage::render(sf::RenderWindow& window)
  {
    window.draw(theText);

    //player list
    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      playerList[i].render(window);
    }
    //chat box

    testk.render(window);
    playerlisttest.render(window);
    playerlistest2->render(window);

    testPictureButton.render2(&window);
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
            //apply commands from server into client game
            if(app.currentGameMode!=nullptr)
              app.currentGameMode->update(app.sendTextDataList,currentItem);
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
