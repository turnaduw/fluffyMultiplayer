#include "../../include/states.h"

namespace FluffyMultiplayer
{

  int StateMainPage::genrate_random_number(int min, int max)
  {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = std::rand() % (max - min + 1) + min;
    return randomNumber;
  }

  void StateMainPage::initAllLobbyCells()
  {
    int tempId=1;
    int maxplayers,currentplayers,gamemode;
    for(int lobbies=0; lobbies<MAX_LOBBY_CELL_LOAD; lobbies++)
    {
      for(float y=0; y<static_cast<float>(WINDOW_WIDTH); y+=100.0)
      {
        for(float x=0; x<static_cast<float>(WINDOW_WIDTH); x+=100.0)
        {
          tempId++;
          maxplayers = genrate_random_number(1,20);
          currentplayers = genrate_random_number(0,maxplayers);
          gamemode = genrate_random_number(0,2);
          bool temp[6];
          for(int i=0; i<=5; i++)
          {
            temp[i] = static_cast<bool>(genrate_random_number(0,1));
          }

          FluffyMultiplayer::LobbyData manualLobbyA = {temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],tempId,maxplayers,currentplayers,gamemode};
          lobbyCells[tempId-1].init(&lobbyGameModeTexturePathList, manualLobbyA, x, y);
        }
      }
    }
  }

  StateMainPage::StateMainPage()
  {
    refreshLobbyListCounter=MC_MAIN_PAGE_LOBBY_LIST_REFRESH_TIMER;
    isPedding=false;

    //set game mode textures list
    lobbyGameModeTexturePathList = GAME_MODE_TEXTURE_LIST;

    //titles
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state mainPage");
    setSimpleTextPosition(150.0, 5.0);
    stateIsBusyText.setFont(theFont);
    stateIsBusyText.setString("StateMainPage action pedding...\n please wait..");

    //text inputs
    inputFocus = &lobbyIdInput;
    lobbyIdInput.init("","","lobby id","enter lobby id to join", 50.0, 100.0);

    //buttons
    buttonSubmitLobbyId.init("join", 200.0,300.0, sf::Color::Black, sf::Color::White, 60,30, 22);

    buttonLogout.init("LogOut", PICTURE_BUTTON_LOGOUT_TEXTURE , 550.0,400.0, sf::Color::Black,sf::Color::White, 22);
    buttonRefreshLobbyList.init("Refresh lobby list", PICTURE_BUTTON_REFRESH_LOBBY_LIST_TEXTURE , 450.0,500.0, sf::Color::Black,sf::Color::White, 22);

    buttonCreateLobby.init("create lobby", 700.0,600.0, sf::Color::Black,sf::Color::White, 60,30, 22);

    buttonQuit.init("quit", PICTURE_BUTTON_QUIT_TEXTURE, 800.0,700.0, sf::Color::Black,sf::Color::White, 22);


    //line
    line[0] = sf::Vertex(sf::Vector2f(0, 250));
    line[1] = sf::Vertex(sf::Vector2f(800, 250));



    //lobbies
    // if(lobbyList.size()>0)
    {
      FluffyMultiplayer::LobbyData manualLobbyA = {false,true,true,true,true,true,1,10,2,1};
      lobbyCells[0].init(&lobbyGameModeTexturePathList, manualLobbyA, 200.0, 500.0);
    }

    initAllLobbyCells();


  }

  StateMainPage::~StateMainPage()
  {

  }

  void StateMainPage::render(sf::RenderWindow& window)
  {
    if(isPedding==true)
      window.draw(stateIsBusyText);
    else
    {
      window.draw(theText);
      lobbyIdInput.render(window);
      buttonSubmitLobbyId.render(window);
      buttonCreateLobby.render(window);
      buttonLogout.render(window);
      buttonRefreshLobbyList.render(window);
      buttonQuit.render(window);
      window.draw(line, 2, sf::Lines);


      if(lobbyCells.size()>0)
      {
        for(int i=0; i<=MAX_LOBBY_CELL_LOAD-1; i++)
        {
          lobbyCells[i].render(window);
        }
      }
    }
  }


  int StateMainPage::checkResponseCode(const std::string& _data)
  {
    std::string tempStr = _data.substr(MC_RESPONSE_POSITION_MIN_INDEX,MC_RESPONSE_POSITION_MAX_INDEX);
    const char* temp = tempStr.c_str();
    int code = std::atoi(temp);
    std::cout << "checkResponseCode=" << code << ";~;" << std::endl;
    if(code>=MC_MINUMUM_RESPONSE_CODE)
      return code;
    return -1;
  }


  int StateMainPage::countLobbies(const std::string& str)
  {
    int count=0;
    for(int i=0; i<str.length(); i++)
    {
      if(findIndexOfDelimiter(str,MC_REQUEST_DELIMITER)>=0)
        count++;
    }
    return count;
  }

  int StateMainPage::findIndexOfDelimiter(const std::string& str, std::string c)
  {
    int index = str.find(c);
    if (index != std::string::npos)
      return index;
    else
      return -1;
  }

  int StateMainPage::convertToInt(const std::string& str)
  {
    const char* val = str.c_str();
    return std::atoi(val);
  }

  bool StateMainPage::convertToBool(const std::string& str)
  {
    return static_cast<bool>(convertToInt(str));
  }

  FluffyMultiplayer::AnAddress StateMainPage::convertToAnAddress(const std::string& str)
  {
    int posCol = findIndexOfDelimiter(str,MC_IP_PORT_SEPARATOR);
    FluffyMultiplayer::AnAddress tempAddress
    {
      boost::asio::ip::address::from_string(str.substr(0,posCol)),
      static_cast<unsigned short>(convertToInt(str.substr(posCol,str.length())))
    };

    return tempAddress;
  }

  FluffyMultiplayer::LobbyData StateMainPage::convertStringToLobby(const std::array<std::string,11>& str)
  {
    FluffyMultiplayer::LobbyData temp
    {
      convertToBool(str[0]),
      convertToBool(str[1]),
      convertToBool(str[2]),
      convertToBool(str[3]),
      convertToBool(str[4]),
      convertToBool(str[5]),

      convertToInt(str[6]),
      convertToInt(str[7]),
      convertToInt(str[8]),
      convertToInt(str[9]),

      convertToAnAddress(str[10])
    };
    return temp;
  }

  bool StateMainPage::updateLobbyList()
  {
    int posDelimiter=0;
    int posCloser=0;
    posCloser = findIndexOfDelimiter(receivedData,MC_REQUEST_CLOSER);
    std::array<std::string,11> temp;
    int lastPosDelimiter=2; //2x jump for code (000) request code
    for(int i=0; i<=countLobbies(receivedData); i++)
    {
      for(int k=0; k<=10; k++) //each lobby has 11 element
      {
        posDelimiter = findIndexOfDelimiter(receivedData,MC_REQUEST_DELIMITER);
        temp[k] = receivedData.substr(lastPosDelimiter,posDelimiter);
        receivedData = receivedData.substr(posDelimiter,receivedData.length());
      }
      lobbyList.push_back(convertStringToLobby(temp));
    }
    if(lobbyList.size()>=1)
      return true;
    else
      return false;
  }

  FluffyMultiplayer::AppState* StateMainPage::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    /*
    if(refreshLobbyListCounter>=1)
    {
      refreshLobbyListCounter--;
    }
    else
    {
      //refresh lobby list
      isPedding=true;


      refreshLobbyResultCode=0;
      refreshLobbyTimeoutCounter=MC_MAIN_PAGE_LOBBY_LIST_REFRESH_TIMEOUT;
      successToRefreshLobbyList=false;
      while(refreshLobbyTimeoutCounter>=1)
      {
        refreshLobbyTimeoutCounter--;


        receivedData = receiveDataQueue.front();
        receiveDataQueue.pop();
        refreshLobbyResultCode = checkResponseCode(receivedData);

        if(refreshLobbyResultCode == MS_RESPONSE_SUCCESS_GET_LOBBY_LIST)
        {
          //set value
          if(updateLobbyList())
          {
            successToRefreshLobbyList=true;
            // std::cout << "succsess to refresh lobby list\n";
            break;
          }
          else
          {
            successToRefreshLobbyList=false;
            std::cout << "failed to refresh lobby list (lobby list received from server but in func updateLobbyList broken)\n";
          }
        }
        else
        {
          // show failed to update lobby list
          successToRefreshLobbyList=false;
          std::cout << "failed to refresh lobby list (invalid response code)\n";
        }

        if(refreshLobbyTimeoutCounter<=0)
        {
          successToRefreshLobbyList=false;
          std::cout << "failed to refresh lobby list (timeout)\n";
        }
      }

      //reset values
      isPedding=false;
      refreshLobbyListCounter=MC_MAIN_PAGE_LOBBY_LIST_REFRESH_TIMER;
    }
    */

    return this;
  }


  FluffyMultiplayer::AppState* StateMainPage::formFinishedResult(bool byId)
  {
    if(byId)
    {
      std::string lobbyIdValue = lobbyIdInput.getEnteredText();
      if(!lobbyIdValue.empty())
      {
        selectedLobby.id = convertToInt(lobbyIdValue);
      }
    }

    return new FluffyMultiplayer::StateWaitForResponse
    (
      "waiting for response from server\nto receive entered lobby id info.\nplease wait..",
      this, //new FluffyMultiplayer::StateFailed("failed to receive response",this, new FluffyMultiplayer::StateEnd,nullptr),
      selectedLobby,
      new FluffyMultiplayer::StateFailed("that entered lobby id not found.", this,nullptr),
      MS_ERROR_FAILED_TO_GET_LOBBY_INFO_LOBBY_NOT_FOUND,
      nullptr, //in statewait will call StateShowLobbyDetails
      MS_RESPONSE_SUCCESS_GET_LOBBY_INFO
    );
  }

  FluffyMultiplayer::AppState* StateMainPage::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    if(isPedding==true) //state is busy
      return this;

    if(event.type == sf::Event::MouseButtonPressed)
    {
      inputFocus = nullptr;

      mousePosition = app.appWindow.mapPixelToCoords(sf::Mouse::getPosition(app.appWindow));

      if(lobbyIdInput.getInputBoxBound().contains(mousePosition))
      {
        inputFocus = &lobbyIdInput;
      }
      else if(buttonCreateLobby.getButtonBound().contains(mousePosition))
      {
        return new FluffyMultiplayer::StateCreateLobbyForm;
      }
      else if(buttonSubmitLobbyId.getButtonBound().contains(mousePosition))
      {
        return formFinishedResult(true);
      }
      else if(buttonLogout.getButtonBound().contains(mousePosition))
      {
        return new FluffyMultiplayer::StateLogout;
      }
      else if(buttonRefreshLobbyList.getButtonBound().contains(mousePosition))
      {
        std::cout << "button refresh lobby list clicked." << std::endl;
      }
      else if(buttonQuit.getButtonBound().contains(mousePosition))
      {
        return new FluffyMultiplayer::StateEnd;
      }

      // if(lobbyList.size()>=1)
      // {
      //   for(auto element : lobbyList)
      //   {
      //     if(element.getBound().contains(mousePosition))
      //     {
      //       std::cout << "clicked on lobby from lobby list lobby id=" << element.id << std::endl;
      //       // return new FluffyMultiplayer::StateShowLobbyDetails(selectedLobby);
      //     }
      //   }
      // }
    }


    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
      {
        isPedding=true;
        if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
        {
            return formFinishedResult(true);
        }
        if(event.key.code == sf::Keyboard::Backspace)
        {
          if(inputFocus!=nullptr)
            inputFocus->removeFromText();
        }
        else
          isPedding=false;//not routed into other state
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
