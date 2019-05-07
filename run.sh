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
echo
echo -ne "PARALLEL"
echo "...................." >> output.txt
echo "...................." >> output.txt
echo "PARALLEL PART" >> output.txt
echo "k set to 10" >> output.txt
for i in 1 2 4 6 8 16;
do
	echo -ne "."
	echo "Results for thread count = ${i}" >> output.txt
	OMP_NUM_THREADS=${i} ./parallel 10 >> output.txt
	echo -ne "."
done

echo "Completed"
