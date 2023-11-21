#include <iostream>
#include "include/app.h"

int main()
{
  try
  {
    // app grapchic
    FluffyMultiplayer::App app;
    app.init();
    app.run(); //main loop is here
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
