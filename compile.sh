#! /bin/zsh

cp $1$2 Temp/src$2
g++ Temp/src$2 -o Temp/exec -std=c++98 -Wall -Wshadow -Wextra