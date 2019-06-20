#!/bin/sh 
i=0
for ((VAR=0 ; VAR<2 ; VAR++ ))
do
  ./ttp1 $1 $2 $3
  ./ttp2 $1 $2 $3
  ./ttp3 $1 $2 $3
  ./ttp4 $1 $2 $3
  ./ttp5 $1 $2 $3
done


