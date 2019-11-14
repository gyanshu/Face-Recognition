#!/bin/bash
rm output.csv
./compile.sh
echo
echo -ne "Running"
echo "OUTPUT" >> output.csv
for i in 1 2 5 7 10; 
do
	echo -ne "."
	echo "k = ${i}" >> output.csv
	echo "Image name, Predicted image number, Actual image number" >>output.csv
	./FacialRecognition ${i} >> output.csv
	echo -ne "."
done

echo "Completed"
