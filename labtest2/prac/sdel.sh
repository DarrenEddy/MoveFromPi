has=$( ls ~/.trash | grep "$1" |wc -l)
if [ $has == 0 ]
then
mv $1 ~/.trash
else
echo "Will not overwite $1"
fi
 
