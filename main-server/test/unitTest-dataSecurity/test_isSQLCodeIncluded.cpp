#include <iostream>
#include <string>
#include "../../include/dataSecurity.h"

int fails = 0;

void prt(bool returnedStatus, bool exceptedStatus, std::string functionName, std::string data)
{
  // std::cout << (returnedStatus==exceptedStatus ? "[DONE]" : "[ X ]") <<" test for " << functionName << " has been " << (returnedStatus==exceptedStatus ? "SUCCESSED" : "FAILED") << ", data = " << data <<std::endl;
  if(returnedStatus!=exceptedStatus)
    fails++;
}

void test_isSQLCodeIncluded()
{
  FluffyMultiplayer::FluffyDataSecurity fds;

  std::string data [5]
  {
     "132;peter;passwordExpanded2213#;addressFoxy;",
     "132;peter;updatePasswordExpanded2213#;addressFoxy;",
     "132;peter;passwordExpanded2213# drop fm_client;addressFoxy;",
     "insertAskllpdkwokfeokgorekg3ru3498tug",
     "; create mananufenuigrg",
  };

  prt(fds.isSQLCodeIncluded(data[0]), false, "test_isSQLCodeIncluded()", data[0]);
  prt(fds.isSQLCodeIncluded(data[1]), false, "test_isSQLCodeIncluded()", data[1]);
  prt(fds.isSQLCodeIncluded(data[2]), true, "test_isSQLCodeIncluded()", data[2]);
  prt(fds.isSQLCodeIncluded(data[3]), false, "test_isSQLCodeIncluded()", data[3]);
  prt(fds.isSQLCodeIncluded(data[4]), true, "test_isSQLCodeIncluded()", data[4]);

}

int main()
{
  test_isSQLCodeIncluded();
  if(fails>0)
    std::cout << "[ X ] " << fails <<" test_isSQLCodeIncluded failed.\n";
  else
    std::cout << "[DONE] All test_isSQLCodeIncluded passed.\n";
  return 0;
}
