#!/bin/bash
function shuf() {
 	local x
 	while read -r x; do
 	echo $RANDOM'|'$x
 	done | sort | while IFS='|' read -r x y; do
 	echo $y
 done
}
shuf
