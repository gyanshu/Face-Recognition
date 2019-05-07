echo "Team 7"
echo "Face Detection"
echo "Compiling"
gcc -o seq seq.c -lm
gcc -fopenmp -o parallel parallel.c -lm
echo "Compiled"
