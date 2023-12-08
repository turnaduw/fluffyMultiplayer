#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateRelogin::StateRelogin()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Trying to read local account files\nto re-login into your account.\nplease wait...");
    reloginData._inputs[0] = ""; //username
    reloginData._inputs[1] = ""; //password
    reloginData._saveLoginStatus=false;

    std::cout << "trying to re-login into account." << std::endl;
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
      identity = line.substr(key.length()+sperator.length(), indexEndline-endline.length()-8);
      std::cout << "found identity = " << identity << "." << std::endl;
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
          if(searchForIdentity(identity,line,std::string(MC_APP_CONFIG_IDENTITY_KEY),
                      std::string(MC_APP_CONFIG_SEPERATOR),std::string(MC_APP_CONFIG_ENDLINE)))
          {
            std::cout << "identity found to re-login" << std::endl;
            appConfigFile.close();
            reloginData.identity = identity;
            FluffyMultiplayer::AppState* res = nullptr;
            if(reloginData._saveLoginStatus)
              res = new FluffyMultiplayer::StateWriteIdentityToLocal;
            else
              res = new FluffyMultiplayer::StateMainPage;

            return new FluffyMultiplayer::StateWaitForResponse //will break loop
            (
              "waiting for response from server\nto re-login into account.\nplease wait..",
              new FluffyMultiplayer::StateLoginForm,
              reloginData,
              std::vector<FluffyMultiplayer::AppState*>
                  {
                      new FluffyMultiplayer::StateFailed("login session not found\n", new FluffyMultiplayer::StateLoginForm ,nullptr),
                      new FluffyMultiplayer::StateFailed("login session time expired\n", new FluffyMultiplayer::StateLoginForm ,nullptr),
                      new FluffyMultiplayer::StateFailed("could not relogin\n", new FluffyMultiplayer::StateLoginForm ,nullptr),
                  },
              res,
              std::vector<int>
                  {
                      MS_ERROR_FAILED_TO_RELOGIN_IDENTITY_INVALID_OR_NOT_EXISTS,
                      MS_ERROR_FAILED_TO_RELOGIN_IDENTITY_EXPIRED,
                      MS_ERROR_FAILED_TO_RELOGIN,
                  },
              MS_RESPONSE_SUCCESS_LOGIN
            );
          }
        }
        appConfigFile.close();
      }
    }
    std::cout << "could not find identity from local at all to re-login." << std::endl;
    return new FluffyMultiplayer::StateLoginForm;
  }


  FluffyMultiplayer::AppState* StateRelogin::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
