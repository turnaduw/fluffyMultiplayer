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

  std::vector<int> dataIndexes(const std::string& data, const std::string& delimiter)
  {
    std::vector<int> result;
    std::string str;
    str = data;

    int index;
    for(int i=0; i<data.length(); i++)
    {
      if(str.empty())
        break;

      index = str.find(delimiter);
      if (index == std::string::npos) //delimiter not found
        break;

      str = str.substr(index+delimiter.length() ,str.length()-1);
      result.push_back(index);
    }

    return result;
  }

  std::vector<std::string> dataSeparator(const std::string& data, std::string delimiter, int startIndex=0)
  {
    std::cout << "dataSeparator.data="+data << std::endl;
    std::vector<std::string> result;
    std::string str = data.substr(startIndex,data.length()-1);

    std::vector<int>indexes = dataIndexes(str,delimiter);
    for(int i=0; i<indexes.size(); i++)
    {
      int index=indexes[i];

      result.push_back(str.substr(0,index));
      str = str.substr(index+delimiter.length() ,str.length()-1);
    }
    return result;
  }



  FluffyMultiplayer::AppState* StateMainPage::update(FluffyMultiplayer::App& app)
  {
    //read from received data..
    FluffyMultiplayer::SocketReceiveData currentItem;
    std::vector<std::string> cData;
    if(app.receivedTextDataList.size()>1)
      for(int i=0; i<app.receivedTextDataList.size(); i++)
      {
        currentItem = app.receivedTextDataList.front();
        cData = dataSeparator(currentItem.data, MS_DATA_DELIMITER);



        switch(currentItem.code)
        {
          case RESPONSE_YOU_ARE_JOINT_INTO_LOBBY:
          {
            app.log.print("joint into lobby.", FluffyMultiplayer::LogType::Information);
          }break;

          case RESPONSE_LOBBY_PLAYERS_ARE: //playerId, playerName
          {
            app.log.print("lobby details..", FluffyMultiplayer::LogType::Information);
            if(cData.size()%2==0) //to avoid 3 items then we call segfault by pres
            {
              for(int i=0; i<cData.size(); i+=2)
              {
                std::cout << "player: id=" << cData[i] << "\tname=" << cData[i+1] << std::endl;
              }
            }
            else
              std::cout << "a problem while loading players\n";
          }break;

          default:
          {
            //apply commands from server into client game
            if(app.currentGameMode!=nullptr)
              app.currentGameMode->update(currentItem.code,cData);
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
