x=1
for i in "$@"
do
	printf "$i"
	let mod=$x%3	
	
	if [ $mod -eq 0 ]
		then
		if [ $x -lt 7 ]
			then
			printf "\n-+-+-\n"
			fi
		else
		printf "|"
	fi
	 
	
let x=x+1
done
printf "\n"
