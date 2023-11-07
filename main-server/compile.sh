#compile whole program
rm fluffy.db
g++ main.cpp ./include/*.h ./src/*.cpp -o ms.run -std=c++11 -lboost_regex -lboost_system -lboost_filesystem -lboost_thread -lsqlite3
rm *.o
rm *.gch
