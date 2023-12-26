#!/bin/bash
compileMain="main.cpp ./include/*.h ./src/*.cpp -o gs.run -std=c++11 -lboost_regex -lboost_system -lboost_filesystem -lboost_thread -lsqlite3"
PS3="Select compile type: "
select compileMode in normal debug run runViaGDB
do
  case $REPLY in
    1)
          #compile whole program
          echo -e "\n\e[31m[START]\e[39m compile $compileMode started at: `date`"
          # rm fluffy.db
          g++ $compileMain
          rm *.o
          rm *.gch
          spd-say 'ready to run'
          echo -e "\n\e[32m[END]\e[39m compile $compileMode finished at: `date`"
          ;;
    2)
          #compile whole program for gdb
          echo -e "\n\e[31m[START]\e[39m compile $compileMode started at: `date`"
          # rm fluffy.db
          g++ -g $compileMain
          rm *.o
          rm *.gch
          spd-say 'ready to run'
          echo -e "\n\e[32m[END]\e[39m compile $compileMode finished at: `date`"
          ;;
    3)
          ./gs.run
          break
          ;;
    4)
          gdb ./gs.run
          break
          ;;
    *)
          echo "incorrect index."
          # break
          ;;
  esac
done
