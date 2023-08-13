#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define ll long long

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        perror("Error in file. Less inputs given");
        return 1;
    }
    const char* inputFilePath = argv[1];
    string startIndex = argv[2];//storing start and end index in strings and later conver then into ll
    string endIndex = argv[3];
    ll start, end;
    ll a=0, b=0;

    string dirPath = "Assignment1_2/";
    string outputPath = "2_";
    string outputFilePath = dirPath + outputPath + inputFilePath;//concatenate the outputFilePath
    
    const char* cDirPath = outputFilePath.c_str();//converting string to const char* 
    
    for(ll i=0; i<startIndex.length(); i++)//converts string start to int
    {
        a = a*10 + (startIndex[i] - '0');
    }
    for(ll i=0; i<endIndex.length(); i++)//converts string end to int
    {
        b = b*10 + (endIndex[i] - '0');

    }   
    
    start = a;
    end = b;
    struct stat sb;//for creating and verifying the creation of directory
    if(stat("Assignment1_1", &sb)!=0){
        int dirStatus = mkdir("Assignment1_2", 0777);
        if (dirStatus == -1) {
            perror("Error creating output directory");
            return 1;
        }
    }

    ll inputFile = open(inputFilePath, O_RDONLY);
    if(inputFile == -1)
    {
        perror("Error opening input file");
        return 1;
    }

    ll outputFile = open(cDirPath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (outputFile == -1) {
        perror("Error opening output file");
        return 1;
    }
    truncate(cDirPath,0);//to overwrite in the outputFile

    off_t bufferSize = 4096;
    char buffer[bufferSize];
    
    off_t fileSize = lseek(inputFile, 0, SEEK_END);//getting the file size
    if(fileSize == -1)
    {
        perror("Error in getting size of input file");
        return 1;
    }
    lseek(inputFile, 0, SEEK_SET);//getting the lseek pointer to point to the start
    char temp;//for reversing
    ssize_t chunk;//buffer size available
    off_t totalBytesWritten = 0;//to calculate percentage 
    
    
    if(start >= fileSize || end >= fileSize || start < 0 || start > end)//all corner cases for indexes
    {
        perror("Error! Indices out of bound!");
        return 1;
    }

    off_t fileSize1 = start;//fileSize1 is for the part to be reversed from beginning of file till before start index
    while( fileSize1 > 0)
    {
        off_t st1 =0;
        if(fileSize1 > bufferSize)//for the leftover bytes, after fileSize1 becomes smaller than the buffer size
            chunk = bufferSize;
        else 
            chunk = fileSize1;

        lseek(inputFile, st1, SEEK_SET);//points to the start
        read(inputFile, buffer, chunk);//reads the input file into buffer of size chunk
        for(ssize_t i=0; i<chunk/2; i++)//for reversing the contents of the buffer
        {
            temp = buffer[i];
            buffer[i] = buffer[chunk - i - 1];
            buffer[chunk - i - 1] = temp;
        }
        lseek(inputFile, st1, SEEK_SET);//points to the front 
        write(outputFile, buffer, chunk);//writes content of reversed buffer into outputFile

        fileSize1 -= chunk;//removing the chunk size from fileSize1 
        st1 += chunk;//moving the offset ahead by chunk size
        totalBytesWritten += chunk;
        float percentage = ((float)totalBytesWritten / fileSize )* 100;
        printf("%.2f%%\r", percentage);
        fflush(stdout);
    }

    off_t fileSize2 = end - start+1;//for the part that should remain unchanged
    while(fileSize2 > 0)
    {
        off_t st2 = start;
        if(fileSize2 > bufferSize)
            chunk = bufferSize;
        else 
            chunk = fileSize2;
        lseek(inputFile, st2, SEEK_SET);
        read(inputFile, buffer, chunk);
        write(outputFile, buffer, chunk);

        fileSize2 -= chunk;
        st2 += chunk;
        totalBytesWritten += chunk;
        float percentage = ((float)totalBytesWritten / fileSize )* 100;
        printf("%.2f%%\r", percentage);
        fflush(stdout);
    }
    
    off_t startIdx = end+1;//for the last part that would be reversed
    off_t fileSize3 = fileSize - startIdx;
    off_t st3 =startIdx;
    while(fileSize3 > 0)
    {
        
        if(fileSize3 > bufferSize)
            chunk = bufferSize;
        else 
            chunk = fileSize3;

        lseek(inputFile, st3, SEEK_SET);
        read(inputFile, buffer, chunk);
    
        for(ssize_t i=0; i<chunk/2; i++)
        {
            temp = buffer[i];
            buffer[i] = buffer[chunk - i - 1];
            buffer[chunk - i - 1] = temp;
        }
        lseek(inputFile, st3, SEEK_SET);
        write(outputFile, buffer, chunk);

        st3 += chunk;
        fileSize3 -= chunk;
        totalBytesWritten += chunk;
        float percentage = ((float)totalBytesWritten / fileSize )* 100;
        printf("%.2f%%\r", percentage);
        fflush(stdout);
        
    }
    return 0;
}
