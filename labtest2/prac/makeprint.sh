> stdout.txt
for i in $(hexdump -e '16/1 "%02x " "\n"' stdin.txt)
do
if [ $((0x$i)) -gt 31 ]
then
printf "$i" | xxd -r -p >> stdout.txt
#printf "0x$i." >> stdout.txt
fi
done

