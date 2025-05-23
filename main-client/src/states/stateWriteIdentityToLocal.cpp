#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateWriteIdentityToLocal::StateWriteIdentityToLocal()
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Writing received identity into local files..\n please wait..");
  }

  StateWriteIdentityToLocal::~StateWriteIdentityToLocal()
  {

  }

  void StateWriteIdentityToLocal::render(sf::RenderWindow& window)
  {
    setSimpleTextPosition((window.getSize().x/2)-INITAL_TEXT_ON_SCREEN_PADDING_X,
                          (window.getSize().y/2)-INITAL_TEXT_ON_SCREEN_PADDING_Y);
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateWriteIdentityToLocal::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    try
    {
      std::string filename = CLIENT_LOCAL_APP_CONFIG_FILE;

      // Create and open a text file
      std::ofstream theFile(filename);

      // Write to the file
      std::string result = MC_APP_CONFIG_IDENTITY_KEY;
      result += MC_APP_CONFIG_SEPERATOR;
      result += app.getIdentity();
      result += MC_APP_CONFIG_ENDLINE;
      theFile << result;

      // Close the file
      theFile.close();
      std::cout << "success to wrote identity(" << app.getIdentity() << " on " CLIENT_LOCAL_APP_CONFIG_FILE << std::endl;
      return new FluffyMultiplayer::StateMainPage;
    }
    catch (std::exception& e)
    {
      std::cout << "failed to wrote identity(" << app.getIdentity() << " on " CLIENT_LOCAL_APP_CONFIG_FILE << std::endl;
      return new FluffyMultiplayer::StateFailed
      (
        "failed to write identity to local files.\n",
        new FluffyMultiplayer::StateWriteIdentityToLocal,
        new FluffyMultiplayer::StateEnd, //quit
        new FluffyMultiplayer::StateMainPage, //nevermind skip, i will login again.
        nullptr
      );
    }
    return this;
  }


  FluffyMultiplayer::AppState* StateWriteIdentityToLocal::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
