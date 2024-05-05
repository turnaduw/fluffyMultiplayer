how to setup and how it work:<a href="https://github.com/turnaduw/fluffyMultiplayer/blob/master/docs/document-body.pdf">click to see pdf file (presian)</a><h1>
cant open preview? <a href="https://github.com/turnaduw/fluffyMultiplayer/blob/master/docs/preview/final-preview-v3.0.0.mp4">click here</a> to load it from docs


https://github.com/mdeets/fluffyMultiplayer/assets/61864724/f8c53d57-cf43-411d-8c2c-da31a6daf741




________________________________________________
### there is some bug and problem:
  - **CLIENT/SERVER SIDE:** cpu usage is extremely high becuase of while loops to receive data... needed to replace by Asyncchronous way.
  - **CLIENT SIDE:** main-client has problem to load game-client (in this case we using std::system(...) to launch game-client so after launch main-client become notresponding..
  - **SERVER SIDE:** each user can create one lobby so if you create lobby and that does not destory you can not create another one so need to create another account this one is bullshit
  - **CLIENT SIDE:** game mode mensch has problem to place pieces in right places
  - **CLIENT/SERVER SIDE:** after game started there is no reconnect option if you left or disconnected or connection lost..
  - **SERVER SIDE:** if on create lobby form set gamemode on null or something like this (index 0) is invalid so game server will crash
  - **SERVER SIDE:** at this time main server is able to just run one game-server then will not create lobbies..

