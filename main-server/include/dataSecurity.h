#ifndef H_DATA_SECURITY_CLASS
#define H_DATA_SECURITY_CLASS

#include <iostream>
#include <string>

//for function isSQLCodeIncluded, isPasswordEasy
#include <boost/regex.hpp>

//access to MS_CLIENT_MAXIMUM_IDENTITY_LENGTH, MS_CHARECTERS_ALLOWED_FOR_IDENTITY_GENERATOR
#include "config.h"

//for function generateIdentity
#include <random>

namespace FluffyMultiplayer
{
  class FluffyDataSecurity
  {
  public:
    FluffyDataSecurity();
    ~FluffyDataSecurity();

    bool isSQLCodeIncluded(const std::string&);
    void removeSQLCodeFromData(std::string&); //writecode..
    void decryptData(std::string&); //writecode..
    void encryptData(std::string&); //writecode..
    std::string generateIdentity();
    bool isPasswordEasy(const std::string&);

  };
}

#endif
