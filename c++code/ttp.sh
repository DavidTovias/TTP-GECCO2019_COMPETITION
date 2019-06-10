#!/bin/sh 
i=0
for ((VAR=0 ; VAR<1 ; VAR++ ))
do
#  g++ ttp_saV3.cpp -o ttp -std=c++11
  ./ttp $1 $2 $3
done


