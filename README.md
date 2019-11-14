# Face Recognition

## Contents

1. [Introduction](#introduction)
2. [Step-by-Step](#step-by-step)  
3. [Conclusion](#Conclusion)
4. [Usage](#Usage)

# Introduction

We have done face recognition using Local Binary Patterns Histograms (LBPH). Local Binary Patterns (LBP) is a type of visual
descriptor used for classification in computer vision. LBP was first described in 1994 and has since been found to be a
powerful feature for texture classification. It has further been determined that when LBP is combined with the Histogram of
oriented gradients (HOG) descriptor, it improves the detection performance considerably on some datasets.

As LBP is a visual descriptor it can be used for face recognition tasks, as can be seen in the following Step-by-Step explanation.

# Step-by-Step

In this section, it is shown a step-by-step explanation of the LBPH algorithm for face recognition as used in our
application:

1. First of all, we need to train our model. For that we have to create a histogram for every training image.
2. All the images(2D matrices) are greyscale in our database and are of dimensions 180 * 200. Every image is given an 
identifier(unqiue number). In each image windows of 3 * 3 with stride 1 are used to compute the histogram for that image.
3. Make an array of size 256 for every image for storing its historgram intialized with zeroes.
4. In a 3 * 3 matrix compare all the neighbouring values to the middle one and if the neighbouring values are greater or
equal to the middle one put 1 for it, otherwise put 0.
5. Now start from the top left neighbour and make a binary number which will be of length 8 (as there are 8 neighbours)
moving clockwise.
6. Convert that binary number into its decimal representation and increment that index in the histogram array by 1. Now
the histogram is created. With that training phase is over.
7. Now for testing, make historgrams for the test images too.
8. Compare the test image histogram with all the train images histograms.
9. For comparison least distance one is selected and we have used below mentioned distance formula : <br/>
![equation](https://latex.codecogs.com/gif.latex?distance%28a%2C%20b%29%20%3D%20%5Csum_%7Bi%3D0%7D%5E%7B255%7D%5Cfrac%7B1%7D%7B2%7D%5Cfrac%7B%28a_i-b_i%29%5E2%7D%7Ba_i&plus;b_i%7D)
10. The above program is run multiple times varying the number of test and train images and the accuracy is printed in 
each case.

# Conclusion

The output is saved in /Output/output.csv. It shows that when we keep half the images for training and other half for 
testing accuracy is more than 98%.


# Usage
* Run below commands in a terminal.
```bash
git clone https://github.com/gyanshu/Face-Recognition
cd Face-Recognition
```
* Now go to Database directory and extract the images.
* Come back to Face-Recognition directory and execute the run.sh file using `bash run.sh`.
* You will find output in the Output directory.
 
