for i in $(ls -R $1)
do
if [ ! -d $i ]
then 
# if first char is . then dont print
temp=$(printf "%s" "$i" |cut -c1)
if [ "$temp" != "." ]
then

echo $i
fi
fi
done
