#!/bin/bash
g++ -g main.cpp -o main.out -std=c++0x
if [ "$?" = "0" ]; then
./main.out "$@"
fi
