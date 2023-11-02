#include <iostream>
#include <string>
#include "../../include/dataSecurity.h"

int fails=0;

void prt(bool returnedStatus, bool exceptedStatus, std::string functionName, std::string data)
{
  // std::cout << (returnedStatus==exceptedStatus? "[DONE]" : "[ X ]" ) << " test for " << functionName << ", data = " << data <<std::endl;
  if(returnedStatus!=exceptedStatus)
    fails++;
}

void test_isPasswordEasy()
{
  FluffyMultiplayer::FluffyDataSecurity fds;

  std::string data [15]
  {
    "hello world", "helloWorldAlex" , "00723489630564",
    "aaaaaa", "HELLO", "Hello131Alex995",
    "45A66c", "abc", " ",
    "+++++++++", "juvireGJREgjvref,VEvkeri", "#$%&*%$#@%^&*",
    "aaaaaa2", "2aaaaaa", "ABCDEF2",
  };
  prt(fds.isPasswordEasy(data[0]), false, "test_isPasswordEasy()", data[0]);
  prt(fds.isPasswordEasy(data[1]), false, "test_isPasswordEasy()", data[1]);
  prt(fds.isPasswordEasy(data[2]), true, "test_isPasswordEasy()", data[2]);
  prt(fds.isPasswordEasy(data[3]), true, "test_isPasswordEasy()", data[3]);
  prt(fds.isPasswordEasy(data[4]), true, "test_isPasswordEasy()", data[4]);
  prt(fds.isPasswordEasy(data[5]), false, "test_isPasswordEasy()", data[5]);
  prt(fds.isPasswordEasy(data[6]), false, "test_isPasswordEasy()", data[6]);
  prt(fds.isPasswordEasy(data[7]), true, "test_isPasswordEasy()", data[7]);
  prt(fds.isPasswordEasy(data[8]), true, "test_isPasswordEasy()", data[8]);
  prt(fds.isPasswordEasy(data[9]), false, "test_isPasswordEasy()", data[9]);
  prt(fds.isPasswordEasy(data[10]), false, "test_isPasswordEasy()", data[10]);
  prt(fds.isPasswordEasy(data[11]), false, "test_isPasswordEasy()", data[11]);
  prt(fds.isPasswordEasy(data[12]), false, "test_isPasswordEasy()", data[12]);
  prt(fds.isPasswordEasy(data[13]), false, "test_isPasswordEasy()", data[13]);

}

int main()
{
  test_isPasswordEasy();
  if(fails>0)
    std::cout << "[ X ] " << fails <<" test_isPasswordEasy failed.\n";
  else
    std::cout << "[DONE] All test_isPasswordEasy passed.\n";
  return 0;
}
