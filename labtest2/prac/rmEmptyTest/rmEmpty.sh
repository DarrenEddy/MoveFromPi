for i in $(find .)
do
if [ -f $i ]
then
if [ $(wc -c < $i) == 0 ]
then
rm $i

fi
fi
done
