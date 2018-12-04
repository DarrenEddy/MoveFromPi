ref=()
time=0

for first in "$@"
do
time=0

	for second in "$@"
	do
		has=$(echo $ref | grep $second| wc -l)
		
		if [ $first != $second ] && [ $has -eq 0 ]
		then
			same=$(cmp $second $first | wc -l)
			if [ $same -eq 0 ]
				then
				if [ $time -eq 0 ]
					then
						printf "$first: $second "
						let time=1
						ref+=$second
					else 
						printf "$second "
						ref+=$second
						
					
					fi
					
				fi
			ref+=$first			
		fi	
	done
	
	if [ $time -eq 1 ]
	then
		printf "\n"
	fi
	
let time=0
done
