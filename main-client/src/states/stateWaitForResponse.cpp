#include "../../include/states.h"

namespace FluffyMultiplayer
{
  StateWaitForResponse::StateWaitForResponse(std::string text, FluffyMultiplayer::AppState* retryState,
                       FluffyMultiplayer::AppState* acceptedState,
                       int responseCodeAccepts)
  {
    std::string fontPath = MC_PATH_TO_FONTS MC_DEFAULT_FONT;
    initSimpleText(fontPath, "Wait for response:\n"+text);
  }

  StateWaitForResponse::~StateWaitForResponse()
  {

  }

  void StateWaitForResponse::render(sf::RenderWindow& window)
  {
    window.draw(theText);
  }


  FluffyMultiplayer::AppState* StateWaitForResponse::update(FluffyMultiplayer::App& app,
                    std::queue<std::string>& receiveDataQueue,
                    std::queue<std::string>& sendDataQueue)

  {
    return this;
  }


  FluffyMultiplayer::AppState* StateWaitForResponse::eventHandle(FluffyMultiplayer::App& app,
                            sf::Event& event)
  {
    return this;
  }
}
