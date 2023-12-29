#include "../../include/gameModes/game-mensch.h"


namespace FluffyMultiplayer
{
  FluffyMultiplayer::GameMode* GameModeMensch::process(FluffyMultiplayer::SocketReceiveData& currentItem,
                                               std::queue<FluffyMultiplayer::SocketSendData>& sendTextDataList,
                                               FluffyMultiplayer::Log& log,
                                               FluffyMultiplayer::DataBase& db,
                                               FluffyMultiplayer::DataSecurity& ds)
  {
    // sendTemp.set(RESPONSE_UNKNOWN_REQUEST_GAME_IS_NOT_STARTED,currentItem.sender);
    // sendTextDataList.push(sendTemp);
    return this;
  }


  void GameModeMensch::roleDice()
  {

  }

  void GameModeMensch::nowTurn()
  {

  }

  void GameModeMensch::movePiece()
  {

  }


}
