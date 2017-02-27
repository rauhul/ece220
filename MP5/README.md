To run the program, type in the following command:
For command 0 (radius is an integer)
./mp5 <inputFile> <outputFile> <command> <radius>
For commands 1-8
./mp5 <inputFile> <outputFile> <command>

Command is an integer from 0-8. inputFile is a png file, such as ./Images/tajmahal.png. outputFile is the generated png file, such as ./out.png

for command 9 (the challenge problem)
./mp5 <inputFile> <outputFile> 9 <transformFile>
for command 10 (the challenge problem)
./mp5 <inputFile> <outputFile> 10 <targetFile>

<command> is a number from 0 to :
0 - cosine blur filter (uses cosineFilter, convolveImage)
1 - median filter (uses convolveImage)
2 - motion blur filter (uses convolveImage)
3 - sharpenLess filter (uses convolveImage)
4 - sharpenMore filter (uses convolveImage)
5 - edge detect filter (uses convolveImage)
6 - convert to gray
7 - invert colors
8 - color threshold
9 - transform image
10 - detectImage

Note for commands 1-5, the filter is already calculated for you in the given code. 

To run the tests run
./test
