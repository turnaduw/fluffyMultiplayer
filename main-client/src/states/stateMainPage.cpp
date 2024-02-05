#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateMainPage::StateMainPage()
  {
    /*
     empty constructor is nothing so we need lobby list, if this constructor called
     turn on goGetLobbyList flag (on mehtod update will check then send request)
     so this goGetLobbyList will call once
     (exception: if turn it of with a timer from update will update lobbyList for a period of time)
    */

    goGetLobbyList = true;
  }

  StateMainPage::~StateMainPage()
  {

  }

  void StateMainPage::render(sf::RenderWindow& window)
  {
      lobbyIdInput.render(window);
      buttonSubmitLobbyId.render(window);
      buttonCreateLobby.render(window);
      buttonLogout.render(window);
      buttonRefreshLobbyList.render(window);
      buttonQuit.render(window);
      window.draw(line, 2, sf::Lines);

      for(int i=0; i<MS_GET_LOBBY_LIST_COUNT_OF_RESULTS; i++)
      {
        lobbyCells[i].render(window);
      }
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
      static_cast<unsigned short>(convertToInt(str.substr(posCol+1,str.length())))
    };

    return tempAddress;
  }

  FluffyMultiplayer::LobbyData StateMainPage::convertStringToLobby(const std::array<std::string,MS_GET_LOBBY_LIST_LOBBY_FILEDS>& str)
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


  FluffyMultiplayer::AppState* StateMainPage::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    if(goGetLobbyList)
    {
      goGetLobbyList=false;
      return new FluffyMultiplayer::StateWaitForResponse
      (
        "wait get lobby list..",
        std::to_string(MC_REQUEST_GET_LOBBY_LIST),
        this,
        new FluffyMultiplayer::StateMainPage,
        MS_RESPONSE_SUCCESS_GET_LOBBY_LIST
      );
    }
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


  std::vector<int> StateMainPage::dataIndexes(const std::string& data, const std::string& delimiter) const
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
  std::array<std::string,MS_GET_LOBBY_LIST_LOBBY_FILEDS> StateMainPage::dataSeparator(std::string& data, std::string delimiter)
  {
    std::array<std::string,MS_GET_LOBBY_LIST_LOBBY_FILEDS> result;

    std::vector<int>indexes = dataIndexes(data,delimiter);
    int index;
    for(int i=0; i<MS_GET_LOBBY_LIST_LOBBY_FILEDS-1; i++)
    {
      index = indexes[i];
      result[i] = data.substr(0,index);
      data = data.substr(index+delimiter.length() ,data.length());
    }

    //print lobby
    // std::cout << "\ndataSeparator(lobby list) result=";
    // for(int i=0; i<MS_GET_LOBBY_LIST_LOBBY_FILEDS-1; i++)
    // {
      // std::cout << result[i] << "\t";
    // }
    // std::cout << std::endl;

    return result;
  }


  StateMainPage::StateMainPage(std::string strlobbyList)
  {
    //to avoid pass condition if(goGetLobbyList) so if that is true will go create infinite time and send request to server like spam and lobby list every second updated and refreshd
    goGetLobbyList=false;

    //set game mode textures list
    lobbyGameModeTexturePathList = GAME_MODE_TEXTURE_LIST;

    float ytools = 27.5;

    //text inputs
    inputFocus = &lobbyIdInput;
    lobbyIdInput.init("",""," Lobby Id:","enter lobby id to join", 27.0, ytools);

    //buttons
    buttonSubmitLobbyId.init("   Join", 305.0,ytools, sf::Color::White, sf::Color::White, 30,30, 22);

    buttonCreateLobby.init("  Create", 566.0,ytools, sf::Color::White,sf::Color::White, 70,30, 22);

    buttonLogout.init("", PICTURE_BUTTON_LOGOUT_TEXTURE , 772.0,ytools, sf::Color::White,sf::Color::White, 18);
    buttonRefreshLobbyList.init("", PICTURE_BUTTON_REFRESH_LOBBY_LIST_TEXTURE , 858.0,ytools, sf::Color::White,sf::Color::White, 18);
    buttonQuit.init("", PICTURE_BUTTON_QUIT_TEXTURE, 946.0,ytools, sf::Color::White,sf::Color::White, 18);


    //line
    line[0] = sf::Vertex(sf::Vector2f(0 , ytools+70));
    line[1] = sf::Vertex(sf::Vector2f(998, ytools+70));



    //------------------------------------- END OF INIT COMPONENTS ------------------------------------------------

    //remove responseCode from data
    strlobbyList = strlobbyList.substr(MC_DATA_START_AT_INDEX, strlobbyList.length()-1);

    //we have X lobby from server create a loop to round that count and push into lobbyList
    for(int i=0; i<MS_GET_LOBBY_LIST_COUNT_OF_RESULTS; i++)
    {

      /*
        here have a single string which is holding that X LobbyData datas as string
        with delimiters so each lobby has K element like isLocked &..
        and need a loop to separate each lobby data from others
        we have a function which is looking for that delimtier we pass to them and
        return value of that so we call that for each element in bottom loop to
        find lobby data
      */
      lobbyList.push_back
      (
        convertStringToLobby
        (
          dataSeparator(strlobbyList,MC_REQUEST_DELIMITER)
        )
      );
    }

    int index=0;
    int spaceBetweenCell = 20;
    int eachCellSize = 186 + spaceBetweenCell;
    int window_x[2] = {50, 813}; //min, max
    int window_y[2] = {110, 813}; //min, max

    for(int y=window_y[0]; y<window_y[1] ; y+=eachCellSize)
    {
      if(index<MS_GET_LOBBY_LIST_COUNT_OF_RESULTS-1)
        for(int x=window_x[0]; x<window_x[1]; x+=eachCellSize)
        {
          lobbyCells[index].init(lobbyGameModeTexturePathList, lobbyList[index], static_cast<float>(x), static_cast<float>(y));
          if(index<MS_GET_LOBBY_LIST_COUNT_OF_RESULTS-1)
            index++;
          else
            break;
        }
      else
        break;
    }

  }

  FluffyMultiplayer::AppState* StateMainPage::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
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
        return new FluffyMultiplayer::StateWaitForResponse
        (
          "Wait.. refresh lobby list..",
          std::to_string(MC_REQUEST_GET_LOBBY_LIST),
          this,
          new FluffyMultiplayer::StateMainPage,
          MS_RESPONSE_SUCCESS_GET_LOBBY_LIST
        );
      }
      else if(buttonQuit.getButtonBound().contains(mousePosition))
      {
        return new FluffyMultiplayer::StateEnd;
      }
      else //is an element of lobby list
      {
        FluffyMultiplayer::LobbyData clickedLobby;
        for(int i=0; i<MS_GET_LOBBY_LIST_COUNT_OF_RESULTS; i++)
        {
          if(lobbyCells[i].getButtonBound().contains(mousePosition))
          {
            clickedLobby = lobbyCells[i].getLobbyData();
            return new FluffyMultiplayer::StateShowLobbyDetails(clickedLobby);
          }
        }
      }

    }


    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
      {
        if(event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return)
        {
            return formFinishedResult(true);
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
