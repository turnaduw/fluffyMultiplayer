#isPasswordEasy
g++ ../../include/config.h ../../include/dataSecurity.h ../../src/dataSecurity.cpp test_isPasswordEasy.cpp -o isPasswordEasy.run -lboost_regex

#isSQLCodeIncluded
g++ ../../include/config.h ../../include/dataSecurity.h ../../src/dataSecurity.cpp test_isSQLCodeIncluded.cpp -o isSqlCodeIncluded.run -lboost_regex


rm *.o
rm *.gch
