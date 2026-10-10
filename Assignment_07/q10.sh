

echo "Enter range:"
read num

a=0
b=1
i=1

for (( i = 1; i<=num ; i++ ))
do
 	c=$(( a + b ))
	a=$b
 	b=$c

	echo -n "$c "
done
 




