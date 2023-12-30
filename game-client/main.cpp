#include "app.h"

//argv-> [0]->server ip.  [1]->server port. [2]->identity
int main(int argc, char** argv)
{
  //get server address from argv
  FluffyMultiplayer::AnAddress serverAddress = {"127.0.0.1",8889};


  FluffyMultiplayer::App app;
  app.init(serverAddress,argv[2]);
  app.run();
  return 0;
}
