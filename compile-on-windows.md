# windows compiles by using g++:
## to compile main-client:
`
g++ -o main.exe ./main.cpp ./include/*.h ./include/states/*.h ./include/uiComponents/*.h ./src/*.cpp ./src/states/*.cpp -g -IC:\Boost\include\boost-1_84 -IC:\Users\windows10\Downloads\winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw64\bin\SFML-2.6.1\include -LC:\Boost\lib -LC:\Users\windows10\Downloads\winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw64\bin\SFML-2.6.1\lib -lboost_system-mgw13-mt-x64-1_84 -lboost_thread-mgw13-mt-x64-1_84 -lboost_filesystem-mgw13-mt-x64-1_84 -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lws2_32 -mwindows
`
<br>
optional: use -mwindows to remove console on execute.

## also for game-client:
`
g++ -o gs.exe ./main.cpp ./include/*.h ./include/gameModes/*.h ./include/states/*.h ./include/uiComponents/*.h ./src/*.cpp ./src/gameModes/*.cpp ./src/states/*.cpp -g -IC:\Boost\include\boost-1_84 -IC:\Users\windows10\Downloads\winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw64\bin\SFML-2.6.1\include -LC:\Boost\lib -LC:\Users\windows10\Downloads\winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw64\bin\SFML-2.6.1\lib -lboost_system-mgw13-mt-x64-1_84 -lboost_thread-mgw13-mt-x64-1_84 -lboost_filesystem-mgw13-mt-x64-1_84 -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lws2_32
`

## for servers (game and main):
need to install libboost-all-dev (version something like 1.70+) + sqlite3-dev + g++ then run ./compile.sh and put '1' wait for compile finished, then compile game-server using that ./compile.sh and copy ms.run and gs.run in a directory then use something like systemd create a service with that ms.run then all done quit vps.
