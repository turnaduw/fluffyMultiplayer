#include "../include/dataSecurity.h"

namespace FluffyMultiplayer
{
  bool FluffyDataSecurity::isSQLCodeIncluded(const std::string& data)
  {
     boost::regex pattern("(\\b(union|select|insert|delete|update|drop|alter|create|truncate|grant|revoke)\\b)", boost::regex::icase);
     return boost::regex_search(data,pattern);
  }

  FluffyDataSecurity::FluffyDataSecurity()
  {

  }

  FluffyDataSecurity::~FluffyDataSecurity()
  {

  }


  void FluffyDataSecurity::removeSQLCodeFromData(std::string& data)
  {
    //..
  }

  void FluffyDataSecurity::decryptData(std::string& data)
  {
    /*
      The value 26 is used in the encrypt and decrypt functions to ensure
      that the shift wraps around the alphabet. In the Caesar cipher,
      when the shift reaches the end of the alphabet,
      it wraps around to the beginning.
      Therefore, the modulo operation with 26 ensures that the
      result stays within the range of the alphabet
       (i.e., 0-25 for English alphabets) and wraps
        around if necessary.
    */
    int shift = 26 - MS_DATA_ENCRYPT_DECRYPT_SHIFT;
      std::string result = "";
        for (char c : data)
        {
            if (isalpha(c))
            {
                char base = isupper(c) ? 'A' : 'a';
                result += static_cast<char>((c - base + shift) % 26 + base);
            }
            else
            {
                result += c;
            }
        }
      data = result;
  }

  void FluffyDataSecurity::encryptData(std::string& data)
  {
    /*
      The value 26 is used in the encrypt and decrypt functions to ensure
      that the shift wraps around the alphabet. In the Caesar cipher,
      when the shift reaches the end of the alphabet,
      it wraps around to the beginning.
      Therefore, the modulo operation with 26 ensures that the
      result stays within the range of the alphabet
       (i.e., 0-25 for English alphabets) and wraps
        around if necessary.
    */
    int shift = MS_DATA_ENCRYPT_DECRYPT_SHIFT;
      std::string result = "";
        for (char c : data)
        {
            if (isalpha(c))
            {
                char base = isupper(c) ? 'A' : 'a';
                result += static_cast<char>((c - base + shift) % 26 + base);
            }
            else
            {
                result += c;
            }
        }
      data = result;
  }

  std::string FluffyDataSecurity::generateIdentity()
  {
    std::string charecters = MS_CHARECTERS_ALLOWED_FOR_IDENTITY_GENERATOR;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0,charecters.size()-1);
    std::string result;

    for(int i=0; i< MS_CLIENT_MAXIMUM_IDENTITY_LENGTH; ++i)
    {
      result+=charecters[distribution(generator)];
    }
    return result;
  }

  bool FluffyDataSecurity::isPasswordEasy(const std::string& password)
  {
    // if(password.empty() || password.size() < MS_CLIENT_MINIMUM_PASSWORD_LENGTH)
    //   return true;
    //
    // boost::regex pattern("[a-zA-Z]"); //password contains only alphabet
    // boost::regex pattern2("[a-z]+"); //password contains only alphabet
    // boost::regex pattern3("[A-Z]+"); //password contains only alphabet
    // boost::regex pattern4("\\d+"); //password contains only digits
    //
    //
    // if( boost::regex_match(password,pattern) ||
    //     boost::regex_match(password,pattern2) ||
    //     boost::regex_match(password,pattern3) ||
    //     boost::regex_match(password,pattern4) )
    //   return true;

    return false;
  }
}
