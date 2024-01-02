#ifndef H_ALL_STATES
#define H_ALL_STATES
// all states include here and just call this file into all states, on this way can easly access to all states as we want.

//request and response list mayneeds in anyState
#include "../include/lobby-request-response-list.h"
#include <iostream>

#include "../include/states/stateBindPickPort.h"
#include "../include/states/stateConnectingToServer.h"
#include "../include/states/stateWaitForResponse.h"
#include "../include/states/stateConnectedToTheServer.h"
#include "../include/states/stateEnd.h"
#include "../include/states/stateMainPage.h"
#include "../include/states/stateJoinLobby.h"
#include "../include/states/stateFailed.h"

#endif
