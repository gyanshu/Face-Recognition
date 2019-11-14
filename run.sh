#!/bin/bash
rm output.txt
./compile.sh
echo
echo -ne "SERIAL" 
echo "SEQUENTIAL PART" >> output.txt
for i in 1 2 5 7 10; 
do
	echo -ne "."
	echo "k = ${i}" >> output.txt
	./seq ${i} >> output.txt
	echo -ne "."
done

echo "Completed"
