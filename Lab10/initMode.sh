#!/bin/bash
i=0
while test $i -lt 5; do
gpio mode $i out
gpio write $i 0
let "i = $i + 1"
done

gpio mode 5 in
gpio mode 5 up





