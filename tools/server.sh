#!/bin/bash

#make ../
g++  ../src/main.cpp ../src/*/*.cpp -lboost_thread -lboost_timer -lboost_chrono -lrt
echo $?
if [[ $? -e 0 ]]; then
    echo "good"
    sudo ./a.out
else 
    echo "success"
fi;



