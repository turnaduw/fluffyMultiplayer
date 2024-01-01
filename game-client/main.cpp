#include <iostream>
#include "include/app.h"

int main(int argc, char** argv)
{
  FluffyMultiplayer::AnAddress serverAddress = {"127.0.0.1",6666};
  std::string identity = "LQLDH5qSBsqtQp1DHULePGNBFwfdTMiUqlF6WRYTX5lVX8UsfjrtH4XgWDCk";
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
