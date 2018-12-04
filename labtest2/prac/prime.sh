for (( i=2; i<=$1; i++))
do
temp=$(factor $i | wc -w)
if [ $temp -eq 2 ]
then
echo "$i"

fi
done
