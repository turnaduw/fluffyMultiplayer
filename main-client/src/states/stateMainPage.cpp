#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateMainPage::StateMainPage()
  {
    refreshLobbyListCounter=MC_MAIN_PAGE_LOBBY_LIST_REFRESH_TIMER;
    isPedding=false;

    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "state mainPage");


    stateIsBusyText.setFont(theFont);
    stateIsBusyText.setString("StateMainPage action pedding...\n please wait..");
  }

  StateMainPage::~StateMainPage()
  {

  }

  void StateMainPage::render(sf::RenderWindow& window)
  {
    if(isPedding==true)
      window.draw(stateIsBusyText);
    else
      window.draw(theText);
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


    return this;
  }


  FluffyMultiplayer::AppState* StateMainPage::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    if(isPedding==true) //state is busy
      return this;

    switch(event.type)
    {
      //keyboard
      case sf::Event::KeyPressed:
      {
        isPedding=true;
        if(event.key.code == sf::Keyboard::Enter)
        {
          //set lobby id
          if(!enteredLobbyId.empty())
            selectedLobby.id = convertToInt(enteredLobbyId);
          return new FluffyMultiplayer::StateWaitForResponse
          (
            "waiting for response from server\nto receive entered lobby id info.\nplease wait..",
            new FluffyMultiplayer::StateFailed("failed to receive response",this, new FluffyMultiplayer::StateEnd,nullptr),
            selectedLobby,
            new FluffyMultiplayer::StateFailed("that entered lobby id not found.", this,nullptr),
            MS_ERROR_FAILED_TO_GET_LOBBY_INFO_LOBBY_NOT_FOUND,
            nullptr,
            MS_RESPONSE_SUCCESS_GET_LOBBY_INFO
          );
        }
        else if(event.key.code == sf::Keyboard::Return)
        {
          //selected lobby
          return new FluffyMultiplayer::StateShowLobbyDetails(selectedLobby);
        }
        else if(event.key.code == sf::Keyboard::Space)
        {
          return new FluffyMultiplayer::StateCreateLobbyForm;
        }
        else if(event.key.code == sf::Keyboard::Backspace)
        {
          return new FluffyMultiplayer::StateLogout;
        }
        else if(event.key.code == sf::Keyboard::LAlt)
        {
          return new FluffyMultiplayer::StateEnd;
        }
        else
          isPedding=false;//not routed into other state
      }
      break;
    }
    return this;
  }
}
