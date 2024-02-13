#include "../../include/states.h"

namespace FluffyMultiplayer
{
  void StateLobbySettings::init() //lobbyStr = gamemode, maxplayers, textchat, voicechat, specter, owner, password
  {
    inputFocus = &passwordInput;
    maxPlayersList = MAX_PLAYER_LIST;
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Lobby Settings");
    setSimpleTextPosition(395.0, 5.0);

    passwordInput.init(std::string((*lobbyStr)[6]),"","Password:","enter password..",340.0, 75.0);

    gameModeSpinBox.init("Game Mode:", GAME_MODE_LIST, 340.0, 200.0, sf::Color::White, sf::Color::White, 22);
    gameModeSpinBox.setCurrent(stringToInt((*lobbyStr)[0]));

    maxPlayersSpinBox.init("Max Players:", maxPlayersList, 340.0, 300.0, sf::Color::White, sf::Color::White, 22);
    for(int i=0; i<maxPlayersList.size(); i++)
    {
      if(maxPlayersList[i] == (*lobbyStr)[1])
      {
        maxPlayersSpinBox.setCurrent(i);
        break;
      }
    }

    int ownerId = stringToInt((*lobbyStr)[5]);
    std::vector<std::string> tempPlayerNames;
    std::string temp;
    int pId;
    int ownerIndex = 0;
    for(int i=0; i<MAX_PLAYERS_IN_LOBBY; i++)
    {
      pId = (*playerList)[i].getId();
      if(pId == ownerId)
      {
        ownerIndex=i;
      }

      //avoid list empty slots..
      if(pId > -1)
      {
        temp =  (*playerList)[i].getName() + " ("+ std::to_string(pId) + ")";
        tempPlayerNames.push_back(temp);
      }
    }

    ownerSpinBox.init("Owner: ", tempPlayerNames, 340.0, 400.0, sf::Color::White, sf::Color::White, 22);
    ownerSpinBox.setCurrent(ownerIndex);

    specterCheckBox.init("Specter:", 340.0, 500.0, sf::Color::White, sf::Color::White, 22);
    specterCheckBox.setStatus(!stringToBool((*lobbyStr)[4]));

    voiceChatCheckBox.init("Voice Chat:", 340.0, 550.0, sf::Color::White, sf::Color::White, 22);
    voiceChatCheckBox.setStatus(!stringToBool((*lobbyStr)[3]));

    textChatCheckBox.init("Text Chat:", 340.0, 600.0, sf::Color::White, sf::Color::White, 22);
    textChatCheckBox.setStatus(!stringToBool((*lobbyStr)[2]));

    buttonSubmit.init("  Submit", 540.0,700.0, sf::Color::White,sf::Color::White, 60,30, 22);
    buttonCancel.init("  Cancel", 340.0,700.0, sf::Color::White,sf::Color::White, 60,30, 22);
    buttonDeleteLobby.init(" Destory", 777.0,700.0, sf::Color::Red,sf::Color::White, 60,30, 22);
  }

  bool StateLobbySettings::stringToBool(const std::string& str)
  {
    const char* c = str.c_str();
    if(std::atoi(c)>0)
    {
      return true;
    }
    return false;
  }

  int StateLobbySettings::stringToInt(const std::string& str)
  {
    const char* c = str.c_str();
    return std::atoi(c);
  }

  StateLobbySettings::StateLobbySettings(std::vector<FluffyMultiplayer::Player>& _players,
                              int& _textChatLines,
                              std::array<FluffyMultiplayer::PlayerList,MAX_PLAYERS_IN_LOBBY>& _playerList,
                              FluffyMultiplayer::Text& _textChat,
                              bool& _amILobbyOwner,
                              FluffyMultiplayer::App& _app,
                              std::vector<std::string>& _lobbyStr)
  {
    players = &_players;
    textChatLines = &_textChatLines;
    playerList = &_playerList;
    textChat = &_textChat;
    amILobbyOwner = &_amILobbyOwner;
    app = &_app;
    lobbyStr = &_lobbyStr;

    init();
  }

  StateLobbySettings::~StateLobbySettings()
  {

  }

  void StateLobbySettings::render(sf::RenderWindow& window)
  {
    window.draw(theText);
    passwordInput.render(window);
    gameModeSpinBox.render(window);
    maxPlayersSpinBox.render(window);
    ownerSpinBox.render(window);
    specterCheckBox.render(window);
    voiceChatCheckBox.render(window);
    textChatCheckBox.render(window);
    buttonSubmit.render(window);
    buttonCancel.render(window);
    buttonDeleteLobby.render(window);
  }


  FluffyMultiplayer::AppState* StateLobbySettings::update(FluffyMultiplayer::App& app)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateLobbySettings::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    //mouse realtime
    if(event.type == sf::Event::MouseButtonPressed)
    {
        mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

        //this focus only works for passwordInput, when cliecked somewhere will be nowhere
        inputFocus = nullptr;


        /*
          deceide delcre array in header to avoid clear each time
          then call getter for bounds and assing then here.
          can not assing anywhere else due to here we're using continues if elses
        */
        gameModeSpinBoxBounds = gameModeSpinBox.getBound();
        maxPlayersSpinBoxBounds = maxPlayersSpinBox.getBound();
        ownerSpinBoxBounds = ownerSpinBox.getBound();

        //buttons
        if(buttonSubmit.getButtonBound().contains(mousePosition))
        {
          // client will send: [0]->(maxPlayers), [1]->gameMode,
          //                   [2]->isVoiceChatForbidden
          //                   [3]->isTextChatForbidden, [4]->isSpecterForbidden,
          //                   [5]->password, [6]->ownerId


          std::vector<std::string> gmList = GAME_MODE_LIST;

          std::string lobbyUpdatedData = maxPlayersList[maxPlayersSpinBox.getCurrentIndex()];
          lobbyUpdatedData += MS_DATA_DELIMITER;
          lobbyUpdatedData += std::to_string(gameModeSpinBox.getCurrentIndex());
          lobbyUpdatedData += MS_DATA_DELIMITER;
          lobbyUpdatedData += std::to_string(!voiceChatCheckBox.getStatus());
          lobbyUpdatedData += MS_DATA_DELIMITER;
          lobbyUpdatedData += std::to_string(!textChatCheckBox.getStatus());
          lobbyUpdatedData += MS_DATA_DELIMITER;
          lobbyUpdatedData += std::to_string(!specterCheckBox.getStatus());
          lobbyUpdatedData += MS_DATA_DELIMITER;
          lobbyUpdatedData += passwordInput.getEnteredText();
          lobbyUpdatedData += MS_DATA_DELIMITER;
          lobbyUpdatedData += std::to_string((*playerList)[ownerSpinBox.getCurrentIndex()].getId());
          lobbyUpdatedData += MS_DATA_DELIMITER;

          app.addSendText(REQUEST_UPDATE_LOBBY_SETTINGS,lobbyUpdatedData);
          return new FluffyMultiplayer::StateMainPage((*players),(*textChatLines),(*playerList),(*textChat),(*amILobbyOwner),app);
        }
        else if(buttonCancel.getButtonBound().contains(mousePosition))
        {
          return new FluffyMultiplayer::StateMainPage((*players),(*textChatLines),(*playerList),(*textChat),(*amILobbyOwner),app);
        }
        else if(buttonDeleteLobby.getButtonBound().contains(mousePosition))
        {
          app.addSendText(REQUEST_DELETE_LOBBY);
          return new FluffyMultiplayer::StateMainPage((*players),(*textChatLines),(*playerList),(*textChat),(*amILobbyOwner),app);
        }

        //text fields
        else if(passwordInput.getInputBoxBound().contains(mousePosition))
        {
          inputFocus = &passwordInput;
        }

        // SPIN BOXES
        else if(gameModeSpinBoxBounds[0].contains(mousePosition)) //spin box game mode
        {
          gameModeSpinBox.spinUp();
        }
        else if(gameModeSpinBoxBounds[1].contains(mousePosition)) //spin box game mode
        {
          gameModeSpinBox.spinDown();
        }
        else if(maxPlayersSpinBoxBounds[0].contains(mousePosition)) //spin box max players
        {
          maxPlayersSpinBox.spinUp();
        }
        else if(maxPlayersSpinBoxBounds[1].contains(mousePosition)) //spin box max players
        {
          maxPlayersSpinBox.spinDown();
        }
        else if(ownerSpinBoxBounds[0].contains(mousePosition)) //spin box max players
        {
          ownerSpinBox.spinUp();
        }
        else if(ownerSpinBoxBounds[1].contains(mousePosition)) //spin box max players
        {
          ownerSpinBox.spinDown();
        }

        //check boxes
        else if(specterCheckBox.getBound().contains(mousePosition))
        {
          specterCheckBox.clickedOnCheckBox();
        }
        else if(voiceChatCheckBox.getBound().contains(mousePosition))
        {
          voiceChatCheckBox.clickedOnCheckBox();
        }
        else if(textChatCheckBox.getBound().contains(mousePosition))
        {
          textChatCheckBox.clickedOnCheckBox();
        }
    }



    switch(event.type)
    {
      //keyboard
        case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
          {
            // return formFinishedResult(app.getIdentity(),true);
          }

          if(event.key.code == sf::Keyboard::Backspace)
          {
            if(inputFocus!=nullptr)
              inputFocus->removeFromText();
          }
        }break;

        case sf::Event::TextEntered:
        {
          if (event.text.unicode < 128)
          {
            if(inputFocus != nullptr)
              inputFocus->update(static_cast<char>(event.text.unicode));
          }
        }break;
    }
    return this;
  }
}
