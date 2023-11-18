#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateRelogin::StateRelogin()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Trying to read local account files\nto re-login into your account.\nplease wait...");
    req = std::to_string(MC_REQUEST_LOGIN)+ ""; //insert empty username for request to relogin
    req += MC_REQUEST_DELIMITER ""; //insert empty password for request to relogin
    req += MC_REQUEST_DELIMITER;
  }

  StateRelogin::~StateRelogin()
  {

  }

  void StateRelogin::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  int StateRelogin::findIndexOfValue(const std::string& str, std::string value)
  {
    size_t found = str.find(value);
    if (found != std::string::npos)
      return static_cast<int>(found);
    return -1;
  }

  bool StateRelogin::searchForIdentity(std::string& identity,
                  const std::string& line,std::string key,
                  std::string sperator,std::string endline)
  {
    int indexKey = findIndexOfValue(line,key);
    int indexEndline = findIndexOfValue(line,endline);
    if(indexKey==-1 || indexEndline==-1)
      return false; //key or endline not found this like need to skip
    else
    {
      int lengthSeprator = sperator.length();
      identity = line.substr(indexKey+lengthSeprator,indexEndline);

      //check for founded identity length
      if(identity.length()>=MC_IDENTITY_MIN_LENGTH
          && identity.length()<=MC_IDENTITY_MAX_LENGTH)
      {
        return true; //successfully identity set.
      }
    }
    return false;
  }


  FluffyMultiplayer::AppState* StateRelogin::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    std::string filename = CLIENT_LOCAL_APP_CONFIG_FILE;
    if(boost::filesystem::exists(filename))
    {
      std::string line;
      std::string identity;
      std::ifstream appConfigFile (filename);
      if (appConfigFile.is_open())
      {
        while ( getline (appConfigFile,line) )
        {
          if
          (
            searchForIdentity
            (
              identity,
              line,
              std::string(MC_APP_CONFIG_IDENTITY_KEY),
              std::string(MC_APP_CONFIG_SEPERATOR),
              std::string(MC_APP_CONFIG_ENDLINE)
            )
          )
          {
            appConfigFile.close();
            req += identity + MC_REQUEST_DELIMITER;
            req += MC_REQUEST_CLOSER;
            return new FluffyMultiplayer::StateWaitForResponse //will break loop
            (
              "waiting for response from server\nto re-login into account.\nplease wait..",
              req,
              this,
              new FluffyMultiplayer::StateLoginForm,
              MS_ERROR_FAILED_TO_LOGIN_CLIENT //in this case use this code, but needs some response code for relogin
            );
          }
        }
        appConfigFile.close();
      }
    }
    return new FluffyMultiplayer::StateLoginForm;
  }


  FluffyMultiplayer::AppState* StateRelogin::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
