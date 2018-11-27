#!/bin/bash
let "temp=$1"
let "x=$temp & 1"
let "temp=$temp>>1"
let "y=$temp & 1"
let "temp=$temp>>1"
let "z=$temp & 1"
let "temp=$temp>>1"
let "q=$temp & 1"

if [ "$x" -eq 1 ]
then
gpio write 3 1
else
gpio write 3 0
fi
 
if [ "$y" -eq 1 ]
then
gpio write 2 1
else
gpio write 2 0
fi

if [ "$z" -eq 1 ]
then
gpio write 1 1
else
gpio write 1 0
fi

if [ "$q" -eq 1 ]
then
gpio write 0 1
else
gpio write 0 0
fi
