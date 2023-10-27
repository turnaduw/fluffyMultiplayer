#ifndef H_DATA_SECURITY_CLASS
#define H_DATA_SECURITY_CLASS

#include <iostream>
#include <string>

namespace FluffyMultiplayer
{
  class FluffyDataSecurity
  {
  priavte:
    bool isSQLCodeIncluded(const std::string&); //writecode..

  public:
    void removeSQLCodeFromData(std::string&); //writecode..
    void decryptData(std::string&); //writecode..
    void encryptData(std::string&); //writecode..
    std::string generateIdentity(); //writecode..

  };
}

#endif
