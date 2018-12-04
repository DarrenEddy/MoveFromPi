for i in $(find .)
do
if [ -d $i ]
then
if [ $(ls $i | wc -l) -eq 0 ]
then
rm -r $i
fi
fi
done
