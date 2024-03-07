how to setup and how it work:<a href="https://github.com/turnaduw/fluffyMultiplayer/blob/master/docs/document-body.pdf">click to see pdf file (presian)</a><h1>

  <h3>preview vesrion 3.0.0: </h3>
  <h4>a preview video from project v3.0.0 click on blow picture</h4>
  
  </h2>
   <h3><a href="https://github.com/turnaduw/fluffyMultiplayer/blob/master/docs/preview/final-preview-v3.0.0.mp4">
   <img src="https://github.com/turnaduw/fluffyMultiplayer/blob/master/docs/preview/ss-v3.png"></img></a></h3>

<br/><br/>

<h3><a href="https://github.com/turnaduw/fluffyMultiplayer/tree/master/docs">also other docs located at docs directory</a><h3>



update: (windows compiles by using g++):
to compile main-client:
`
g++ -o main.exe ./main.cpp ./include/*.h ./include/states/*.h ./include/uiComponents/*.h ./src/*.cpp ./src/states/*.cpp -g -IC:\Boost\include\boost-1_84 -IC:\Users\windows10\Downloads\winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw64\bin\SFML-2.6.1\include -LC:\Boost\lib -LC:\Users\windows10\Downloads\winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw64\bin\SFML-2.6.1\lib -lboost_system-mgw13-mt-x64-1_84 -lboost_thread-mgw13-mt-x64-1_84 -lboost_filesystem-mgw13-mt-x64-1_84 -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lws2_32 -mwindows
`
optional: use -mwindows to remove console on execute.

also for game-client:
`
g++ -o gs.exe ./main.cpp ./include/*.h ./include/gameModes/*.h ./include/states/*.h ./include/uiComponents/*.h ./src/*.cpp ./src/gameModes/*.cpp ./src/states/*.cpp -g -IC:\Boost\include\boost-1_84 -IC:\Users\windows10\Downloads\winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw64\bin\SFML-2.6.1\include -LC:\Boost\lib -LC:\Users\windows10\Downloads\winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw64\bin\SFML-2.6.1\lib -lboost_system-mgw13-mt-x64-1_84 -lboost_thread-mgw13-mt-x64-1_84 -lboost_filesystem-mgw13-mt-x64-1_84 -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lws2_32
`

for servers (game and main) need to install libboost-all-dev (version something like 1.70+) + sqlite3-dev + g++ then run ./compile.sh and put '1' wait for compile finished, then compile game-server using that ./compile.sh and copy ms.run and gs.run in a directory then use something like systemd create a service with that ms.run then all done quit vps.

________________________________________________
### there is some bug and problem:
  - at this time main server is able to just run one game-server then will not create lobbies..
  - main-client has problem to load game-client (in this case we using std::system(...) to launch game-client so after launch main-client become notresponding..
  - each user can create one lobby so if you create lobby and that does not destory you can not create another one so need to create another account this one is bullshit
  - game mode mensch has problem to place pieces in right places
  - after game started there is no reconnect option if you left or disconnected or connection lost..
  - if on create lobby form set gamemode on null or something like this (index 0) is invalid so game server will crash

<h1>preview vesrion 1.0.0:</h1>
<h3><a href="https://github.com/turnaduw/fluffyMultiplayer/blob/master/docs/preview/main-server-client-v1.0.0.mp4">
a preview of main client/server v1.0.0 (main client and main server)  click on blow picture <img src="https://github.com/turnaduw/fluffyMultiplayer/blob/master/docs/preview/v1.png"></img>
</a></h3>
