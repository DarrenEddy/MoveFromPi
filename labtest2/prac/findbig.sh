for i in $(find .)
do
if [ -f $i ]
then
size=$(wc -c < $i)
if [ $size -gt $1 ]
then
echo $i
fi
fi
done
