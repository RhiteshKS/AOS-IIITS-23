# Assignment 1
### Rhitesh Kumar Singh, 2023202013, AOS

## Q1
* I have assumed that only the file name is to be given i.e., for eg, "input.txt", and not the whole path. 
* The output file gets created in a directory named Assignment1_1. 
* The output file gets the name "1_<input_text_file>" with the reversed contents of the given <input_text_file>.
To run the first question, use these commands,
```
g++ 2023202013_A1_Q1.cpp
./a.out <input_text_file>
```
* Output is shown as "1_<input_text_file>" residing in Assignment1_1 directory.


## Q2
* I have assumed that only the file name is to be given i.e., for eg, "input.txt", and not the whole path. 
You are required to give 2 additional arguments of integer type, the start index(startIndex) and the end index(endIndex). 
* The content between the two indices, both inclusive, remains unchanged, while the rest of the content, from beginning of file to the start index and the from end index+1 to the end of file is copied in the reverse fashion to the output file.
The output file gets created in a directory named Assignment1_2. 
* The output file gets the name "2_<input_file_name>".
To run the second question, use these commands,
```
g++ 2023202013_A1_Q2.cpp
./a.out <input_text_file> startIndex endIndex
```
* Output is shown as "2_<input_text_file>" residing in Assignment1_2 directory. 

## Q3
* I have assumed that the files to be input in command line arguments are just stand alone text files without giving their absolute paths. 
* The newfile resides inside the directory "Assignment1_1" and I have included that in my code as such. The oldfile and the directory are in the current directory.
* If the absolute path is given, then the code will not work. As long as just the text files are given, it will work.
To run the third question, use the commands,
```
g++ 2023202013_A1_Q3.cpp
./a.out <newfile> <oldfile> <directory>
```
* So in our case the command would look like
```
./a.out 1_input.txt input.txt Assignment1_1
``` 
* where 1_input.txt lies inside Assignment1_1 directory and is the reversed content of input.txt mentioned in Q1.