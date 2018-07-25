#/usr/bin/!bash

echo "Shell programing practice"
ls
pwd
read count
while [ $count -gt 0 ]
do 
   echo "In side while"
   count=`expr $count - 1`
done

