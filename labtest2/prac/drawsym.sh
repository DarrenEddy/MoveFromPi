sym="*"
point=$1
space=1
for (( i=1; i<=$1; i++ ))
do

for (( j=1; j<=$point; j++ ))
do
printf " "
done
printf "*"

# if != 1 
# space increasing then *
if [ $i != 1 ]
then
for (( k=1; k<=$space; k++))
do

if [ $i == $1 ]
then
printf "*"
else
printf " "
fi


done
printf "*"

let space=1+$k
fi
printf "\n"
let point=point-1 
done
