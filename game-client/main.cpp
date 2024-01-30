#include <iostream>
#include "include/app.h"

int main(int argc, char** argv)
{
  FluffyMultiplayer::AnAddress serverAddress = {"127.0.0.1",7777};
  std::string identity = "6LIL84orxbKWTBcsKS1cgkTyyzCLaCDkH6H0qvegt24jX551hiF2L9fDSpos";
  try
  {
    FluffyMultiplayer::App app;
    app.init(serverAddress,identity);
    app.run(); //main loop is here
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
