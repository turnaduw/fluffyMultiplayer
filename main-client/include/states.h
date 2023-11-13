#ifndef H_ALL_STATES
#define H_ALL_STATES
// all states include here and just call this file into all states, on this way can easly access to all states as we want.

#include "../include/states/stateReadServerList.h"
#include "../include/states/stateUnableToReadServerList.h"
#include "../include/states/stateBindPickPort.h"
#include "../include/states/stateFailedToBindPickPort.h"
#include "../include/states/stateConnectingToServer.h"
#include "../include/states/stateWaitForResponse.h"
#include "../include/states/stateFailedConnectToAllServers.h"
#include "../include/states/stateConnectedToTheServer.h"
#include "../include/states/stateRelogin.h"
#include "../include/states/stateFailedRelogin.h"
#include "../include/states/stateLoginForm.h"
#include "../include/states/stateFailedLogin.h"
#include "../include/states/stateEnd.h"
#include "../include/states/stateRegisterForm.h"
#include "../include/states/stateFailedRegister.h"
#include "../include/states/stateAccountIsBanned.h"
#include "../include/states/stateWriteIdentityToLocal.h"
#include "../include/states/stateFailedWriteIdentityToLocal.h"
#include "../include/states/stateMainPage.h"
#include "../include/states/state"


#endif
