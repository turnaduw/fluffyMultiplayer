#include "../include/dataTypes.h"

namespace FluffyMultiplayer
{
  int convertStringToInt(const std::string& data)
  {
    const char* c = data.c_str();
    return std::atoi(c);
  }
}
