#include <iostream>
#include <string>
#include "../../include/dataSecurity.h"
#include <vector>

int fails=0;
std::vector<std::string> outputs;
std::vector<std::string> failedOutputWrongLength;
std::vector<std::string> failedOutputDuplicated;


bool isStringExists(const std::string& data)
{
  for (int i = 0; i < outputs.size(); i++)
  {
    if(outputs[i] == data)
      return true;
  }
  return false;
}

void prt(std::string output)
{
  if(!isStringExists(output))
  {
      if(output.length()<=MS_CLIENT_MAXIMUM_IDENTITY_LENGTH && output.length() > MS_CLIENT_MINIMUM_IDENTITY_LENGTH)
      {
        std::cout << "[DONE] identity generated = " << output << std::endl;
        outputs.push_back(output);
      }
      else
      {
        fails++;
        std::cout << "[ X ] wrong identity length, test failed identity generated = " << output << " ----------------------- " << std::endl;
        failedOutputWrongLength.push_back(output);
      }
  }
  else
  {
    fails++;
    std::cout << "[ X ] duplicated identity, test failed identity generated = " << output << " ----------------------- " << std::endl;
    failedOutputDuplicated.push_back(output);
  }
}

void test_generateIdentity(const int& count)
{
  FluffyMultiplayer::FluffyDataSecurity fds;

  for(int i=0; i<count; i++)
    prt(fds.generateIdentity());
}

int main()
{
  int count_test = 10;
  std::cout << "enter count of tests: ";
  std::cin >> count_test;
  test_generateIdentity(count_test);
  if(fails>0)
  {
    for(auto element : failedOutputDuplicated)
      std::cout << "failed identity duplicated = " << element << std::endl;

    for(auto element : failedOutputWrongLength)
      std::cout << "failed identity wrong length= " << element << std::endl;

    std::cout << "[ X ] test_generateIdentity " << fails <<" of " << count_test << " failed.\n";
    std::cout << "[COuNTS], failed due to duplicated: " << failedOutputDuplicated.size()
      << "\nfailed due to wrong length: " << failedOutputWrongLength.size()
      << "\nof " << count_test << " total cases.\n";
  }
  else
    std::cout << "[DONE] All " <<  count_test << " tests for test_generateIdentity successfully passed.\n";

  return 0;
}
