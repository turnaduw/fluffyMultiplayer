#!/bin/bash
compileMain="main.cpp ./include/*.h ./include/states/*.h ./include/uiComponents/*.h ./src/*.cpp ./src/states/*.cpp -o gc.run -std=c++11 -lboost_system -lboost_filesystem -lboost_thread -lsfml-graphics -lsfml-window -lsfml-system -pthread -lpthread"
PS3="Select compile type: "
select compileMode in normal debug run runViaGDB
do
  case $REPLY in
    1)
          #compile whole program
          echo -e "\n\e[31m[START]\e[39m compile $compileMode started at: `date`"
          g++ $compileMain
          spd-say 'ready to run'
          echo -e "\n\e[32m[END]\e[39m compile $compileMode finished at: `date`"
          ;;
    2)
          clear
          #compile whole program for gdb
          echo -e "\n\e[31m[START]\e[39m compile $compileMode started at: `date`"
          g++ -g $compileMain
          spd-say 'ready to run'
          echo -e "\n\e[32m[END]\e[39m compile $compileMode finished at: `date`"
          ;;
    3)
          ./gc.run
          break
          ;;
    4)
          gdb ./gc.run
          break
          ;;
    *)
          echo "incorrect index."
          # break
          ;;
  esac
done
