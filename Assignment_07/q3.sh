
echo "Enter name: "
read name

	if [ -f $name -a -x $name ]
	then
		echo "file name:"
		echo "$name"
		echo "size: "
		ls -lS "$name"

	elif [ -d $name -a -x $name ]
	then
		echo "Directory name:"
		echo "$name"
		echo "Content:"
		ls $name
	else
		echo "Not found"
	fi
