#compile whole program
rm fluffy.db
g++ main.cpp ./include/*.h ./src/*.cpp -o ms.run -std=c++11 -lboost_regex -lboost_system -lboost_filesystem -lboost_thread -lsqlite3


# includes priority are like:
# g++
# ./include/config.h
# ./include/response-list.h
# ./include/request-list.h
# ./include/error-list.h
# ./include/internal-error-list.h
# ./include/dataSecurity.h
# ./include/dataTypes.h
# ./include/database.h
# ./include/processData.h
# ./src/dataSecurity.cpp
# ./src/dataTypes.cpp
# ./src/database.cpp
# ./src/processData.cpp
# main.cpp
#
# -o main-server.run
# -std=c++11 -lboost_regex -lboost_system -lboost_filesystem -lboost_thread -lsqlite3
#
# rm *.o
# rm *.gch
