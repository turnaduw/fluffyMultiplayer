#!/bin/bash
compileMain="main.cpp ./include/*.h ./include/states/*.h ./include/uiComponents/*.h ./src/*.cpp ./src/states/*.cpp -o mc.run -std=c++11 -lboost_system -lboost_filesystem -lboost_thread -lsfml-graphics -lsfml-window -lsfml-system -pthread -lpthread"
PS3="Select compile type: "
select compileMode in normal debug
do
  case $REPLY in
    1)
          #compile whole program
          echo -e "\n\e[31m[START]\e[39m compile $compileMode started at: `date`"
          g++ $compileMain
          echo -e "\n\e[32m[END]\e[39m compile $compileMode finished at: `date`"
          break
          ;;
    2)
          #compile whole program for gdb
          echo -e "\n\e[31m[START]\e[39m compile $compileMode started at: `date`"
          g++ -g $compileMain
          echo -e "\n\e[32m[END]\e[39m compile $compileMode finished at: `date`"
          break
          ;;
    *)
          echo "incorrect index."
          # break
          ;;
  esac
done
