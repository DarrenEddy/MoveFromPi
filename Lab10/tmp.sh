
initial=$(./thermo -d 28-021312cea6aa)
error=0
dif=0


while [ $error -eq 0 ]
do

temp=$(./thermo -d 28-021312cea6aa)

let "error=$?"
let "dif = $temp - $initial"

echo "-- $dif"
if [ $dif -gt 1000 ]
then
gpio write 0 1
else 
gpio write 0 0
fi

if [ $dif -gt 2000 ]
then 
gpio write 1 1
else
gpio write 1 0
fi

if [ $dif -gt 3000 ]
then 
gpio write 2 1
else 
gpio write 2 0
fi

done

echo "ERROR -> Connection Fault: Check your connection"
gpio write 0 0
gpio write 1 0
gpio write 2 0
