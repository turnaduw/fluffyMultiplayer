#include "../include/dataSecurity.h"


namespace FluffyMultiplayer
{
  DataSecurity::DataSecurity()
  {

  }

  DataSecurity::~DataSecurity()
  {

  }

  void DataSecurity::encryptData(std::string& data)
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

  void DataSecurity::decryptData(std::string& data)
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
}
