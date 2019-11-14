#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

//utility functions
int **alloc_2d_matrix(int r, int c)
{
    int ** a;
    int i; 
    a = (int **)malloc(sizeof(int *) * r);
    if (a == NULL) {
        perror("memory allocation failure");
        exit(0);
    } 
    for (i = 0; i < r; ++i) {
        a[i] = (int *)malloc(sizeof(int) * c);
        if (a[i] == NULL) {
            perror("memory allocation failure");
            exit(EXIT_FAILURE);
        }
    }
    return a;
}
 
void dealloc_2d_matrix(int **a, int r, int c)
{
    int i;
    for (i = 0; i < r; ++i)
        free(a[i]);
    free(a);
}

int ** read_pgm_file(char * file_name, int h, int w)
{
    FILE * file;
    int i,j, int_tmp;
    int** data =  alloc_2d_matrix(h,w);
        
    if ((file = fopen(file_name, "r+")) == NULL)
    {
        printf("ERROR: file open failed\n");
        return(NULL);
    }
    
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            fscanf(file,"%d", &int_tmp);
            data[i][j] = int_tmp;   
        }
    }    
    fclose(file);
    return data;
}

const int NUMOFPEOPLE = 27;
const int NUMOFFILE = 20;
const int IMGH = 180;
const int IMGW = 200;

void  create_histogram(int * histogram, int ** image, int num_rows, int num_cols) {

    int row, col,i,j;
    int decimal = 0;
    int count = 0;

    #pragma omp parralel for
    for (row = 0; row < 256; row++){
        histogram[row] = 0;
    }

    for(row = 1; row < num_rows-1; row++){              
        for(col = 1; col < num_cols-1; col++){          
            char binary[8];
            int i;

            for (i = 0; i < 8; i++){
                binary[i] = '0';
            }

            i = 0;

            if(image[row][col] <= image[row][col-1]){
                binary[i] = '1';
            }
            i++;
            if(image[row][col] <= image[row+1][col-1]){
                binary[i] = '1';
            }
            i++;
            if(image[row][col] <= image[row+1][col]){
                binary[i] = '1';
            }
            i++;
            if(image[row][col] <= image[row+1][col+1]){
                binary[i] = '1';
            }
            i++;
            if(image[row][col] <= image[row][col+1]){
                binary[i] = '1';
            }
            i++;
            if(image[row][col] <= image[row-1][col+1]){
                binary[i] = '1';
            }
            i++;
            if(image[row][col] <= image[row-1][col]){
                binary[i] = '1';
            }
            i++;
            if(image[row][col] <= image[row-1][col-1]){
                binary[i] = '1';
            }

            int index = 0;
            for(i = 0; i < 8; i++) {
                index *= 2;
                index += binary[i] - '0';
            }

            histogram[index]++;
        }
    }
}

double distance(int *training_image, int *test_image, int size) {

    double sum = 0;
    int i;
    double nom, denom;

    for (i = 0; i < size; i++){
        if(training_image[i] + test_image[i] != 0){
            sum = sum + pow((training_image[i]-test_image[i]),2) / (2*(training_image[i]+test_image[i]));
        }
    }

    return sum;

}

int find_closest(int training_set[NUMOFPEOPLE][NUMOFFILE][256], int num_persons, int num_training, int size, int *test_image){
    int sampPeople, sampImg, count, match = 0;
    int min = 1000;
    int temp[256];
    for(sampPeople = 0; sampPeople < num_persons; sampPeople++){
        for (sampImg = 0; sampImg < num_training; sampImg++){
            int dist = distance(training_set[sampPeople][sampImg], &test_image[0], 256);
            if(dist < min){
                min = dist;
                match = sampPeople;
            }
        }
    }
    return match;
}

int main (int argc, char *argv[]){
	int k = atoi(argv[1]);
    int i, j, acc = 0, numOfTests = 0;
	int histogram[NUMOFPEOPLE][NUMOFFILE][256], testhistogram[NUMOFPEOPLE][NUMOFFILE][256];
	int** result [NUMOFPEOPLE][NUMOFFILE];
    result[0][0] = alloc_2d_matrix(IMGH, IMGW);
    //TRAINING
	for (i = 0; i < NUMOFPEOPLE; i++){
		for (j = 0 ; j < NUMOFFILE; j++){
            char buf[64];
			sprintf(buf, "Database/images/%d.%d.txt", i+1, j+1);
			result[i][j] = read_pgm_file(buf, IMGH, IMGW);
			if (j < k ) {
				create_histogram(histogram[i][j],result[i][j], IMGH, IMGW);				
			}
			else {
				create_histogram(testhistogram[i][j],result[i][j], IMGH, IMGW);
			}
		}
	}
    //TESTING
	for(i = 0; i < NUMOFPEOPLE; i++) {
		for (j = k; j < NUMOFFILE; j++){
            int match = find_closest(histogram, NUMOFPEOPLE, k, 256, testhistogram[i][j]);
			printf("%d.%d.txt, %d, %d\n", i+1,j+1,match+1,i+1);
			if (match == i){
                acc++;
			}
            numOfTests++;
		}
	}
	printf("Accuracy: %d correct answers for %d tests - %.2f%%,,\n\n", acc, numOfTests, ((float)acc/numOfTests)*100 );

	return 0;
}
