#!/bin/bash

echo "1.Date" 
echo "2.Cal"
echo "3.Ls"
echo "4.Pwd"
echo "5.Esist"

echo "Enter choice :"

read choice

if [ "$choice" -eq 1 ]
then 
	date

elif [ "$choice" -eq 2 ]
then
  	cal

elif [ "$choice" -eq 3 ]
then
	ls

elif [ "$choice" -eq 4 ]
then 
	pwd
elif [ "$choice" -eq 5 ]
then 
	exit

else
	echo "Invalid choice"

fi

