#!/bin/bash
rm -f Output/output.csv
./compile.sh
echo
echo -ne "Running"
echo "OUTPUT,," >> Output/output.csv
for i in 1 2 5 7 10; 
do
	echo -ne "."
	echo "k = ${i},," >> Output/output.csv
	echo "Image name, Predicted image number, Actual image number" >> Output/output.csv
	./FacialRecognition ${i} >> Output/output.csv
	echo -ne "."
done

echo "Completed"
