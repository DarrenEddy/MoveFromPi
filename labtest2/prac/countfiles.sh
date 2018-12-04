# try to just count files in current dir
echo "$(ls -R $1| wc -w)"
