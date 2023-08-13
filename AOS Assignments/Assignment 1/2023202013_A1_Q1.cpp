#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
//#define ll long long
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Error giving inputs");
        return 1;
    }

    const char* inputFilePath = argv[1];
    string dirPath = "Assignment1_1/";
    string outputPath = "1_";
    string outputFilePath = dirPath + outputPath + inputFilePath;
    
    const char* cDirPath = outputFilePath.c_str();
    
    struct stat sb;
    if(stat("Assignment1_1", &sb)!=0){
        int dirStatus = mkdir("Assignment1_1", 0777);
        if (dirStatus == -1) {
            perror("Error creating output directory");
            return 1;
        }
    }
    
    int inputFile = open(inputFilePath, O_RDONLY);
    if (inputFile == -1) {
        perror("Error opening input file");
        return 1;
    }

    int outputFile = open(cDirPath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (outputFile == -1) {
        perror("Error opening output file");
        return 1;
    }
    truncate(cDirPath,0);

    off_t bufferSize = 4096;
    char buffer[bufferSize];
    ssize_t chunk;
    off_t fileSize = lseek(inputFile, 0, SEEK_END);//to get file size
    if(fileSize == -1)
    {
        perror("Error in getting size of input file");
        return 1;
    }
    off_t n;
    off_t totalSize = fileSize;//since fileSize will change value later
    off_t totalBytesWritten = 0;

    while(fileSize > 0)
    {
        off_t st1 =0;//offset
        if(fileSize > bufferSize)//for the leftover bytes when filesize becomes less than buffer size
            chunk = bufferSize;
        else 
            chunk = fileSize;

        lseek(inputFile, st1, SEEK_SET);//pointer to the start
        n = read(inputFile, buffer, chunk);//read the inputFile into buffer of size chunk
        if(n == -1)
        {
            perror("Error! Reading input file");
            return 1;
        }
        for(ssize_t i=0; i<chunk/2; i++)//reversing the coontents of buffer
        {
            char temp = buffer[i];
            buffer[i] = buffer[chunk - i - 1];
            buffer[chunk - i - 1] = temp;
        }
        lseek(inputFile, st1, SEEK_SET);
        write(outputFile, buffer, n);//writing the reversed buffer into outputFile

        fileSize -= chunk;//removing chunk size after each iteration
        st1 += chunk;//moving the offset by chunk size
        totalBytesWritten += chunk;//for percentage calculation
        float percentage = ((float)totalBytesWritten / totalSize )* 100;
        printf("%.2f%%\r", percentage);
        fflush(stdout);
    
    }

    close(inputFile);
    close(outputFile);

    return 0;
}
