while read p; do
i=0
sum=0
IFS=","
	for tok in $p
	do
		if [ $i -eq 0 ]
		then
			printf "$tok "	
		elif [ $i -gt 2 ]
		then
			let sum=sum+$tok
		fi

		let i=i+1
	done
	printf "$sum\n"
done 
