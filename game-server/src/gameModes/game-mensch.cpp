#include "../../include/gameModes/game-mensch.h"


namespace FluffyMultiplayer
{
  FluffyMultiplayer::GameMode* process(FluffyMultiplayer::SocketReceiveData& currentItem,
                                               FluffyMultiplayer::SocketSendData& tempSend,
                                               FluffyMultiplayer::Player& tempPlayer,
                                               std::queue<FluffyMultiplayer::SocketSendData>& sendTextDataList,
                                               FluffyMultiplayer::Log& log,
                                               FluffyMultiplayer::DataBase& db) override
  {
    sendTemp.set(RESPONSE_UNKNOWN_REQUEST_GAME_IS_NOT_STARTED,currentItem.sender);
    sendTextDataList.push(sendTemp);
  }

}
