#ifndef H_DATA_SECURITY_CLASS
#define H_DATA_SECURITY_CLASS

namespace FluffyMultiplayer
{
  class DataSecurity
  {
    public:
      DataSecurity();
      ~DataSecurity();
      void encryptData(std::string&);
      void decryptData(std::string&);
  };
}

#endif
