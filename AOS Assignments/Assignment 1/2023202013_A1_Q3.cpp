#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#define ll long long
using namespace std;

int main(int argc, char* argv[])
{   //4 inputs to be given
    if(argc != 4)
    {
        perror("Error in file. Less inputs given");
        return 1;
    }
    const char* newFilePath = argv[1];
    const char* oldFilePath = argv[2];
    const char* dirPath = argv[3];

    string newPath = "Assignment1_1/";//since output file is inside the directory Assignment1_1
    string finalNewPath = newPath + newFilePath;
    const char* cNewPath = finalNewPath.c_str();

    
    string flag, flagRev;//flags to check for permissions and reversing 
    struct stat snewFile ;
    struct stat soldFile;
    struct stat sdir;
    
    char buffer1, buffer2;//two buffers to compare the two files

    if(stat(dirPath, &sdir) == 0 && S_ISDIR(sdir.st_mode))//checks if directory exists
        flag = "YES";
    else
        flag = "NO";
    cout<<"Directory is created: "<<flag<<endl;

    ll oldFile = open(oldFilePath, O_RDONLY);
    if(oldFile == -1)
    {
        perror("Error opening input file");
        return 1;
    }
    
    ll newFile = open(cNewPath, O_RDONLY);
    if (newFile == -1) {
        perror("Error opening output file");
        return 1;
    }

    off_t fileSize1 = lseek(oldFile, 0, SEEK_END);
    if(fileSize1 == -1)
    {
        perror("Error in getting size of file2");
        return 1;
    }
    off_t fileSize2 = lseek(newFile, 0, SEEK_END);
    if(fileSize2 == -1)
    {
        perror("Error in getting the size of file1");
        return 1;
    }
    if(fileSize1 != fileSize2)//checks if both files have the same sizes
        flagRev = "NO";
    else
        flagRev = "YES";

    for(ssize_t i =0; i<fileSize1; i++)//one lseek pointer is positioned at the start of newfile and one at the end of oldfile
    {//reads a character one by one in buffer1 and buffer2 for old and newfile. Checks if they match, if they dont, set flagRev as NO
    //and comes out of the loop.
        lseek(newFile, i, SEEK_SET);
        lseek(oldFile, fileSize1 - i -1, SEEK_SET);
        read(oldFile, &buffer1, 1);
        read(newFile, &buffer2, 1);
        if(buffer1 != buffer2)
        {
            flagRev = "NO";
            break;
        }
        flagRev = "YES";
    }

    
    cout<<"Whether file contents are reversed in newfile: "<<flagRev<<endl;
    
    if(stat(newFilePath, &snewFile) == 0)//checks permissions on newfile
    {
        flag = (snewFile.st_mode & S_IRUSR) ? "YES" : "NO";
        cout<<"User has read permissions on newfile: "<<flag<<endl;

        flag = (snewFile.st_mode & S_IWUSR) ? "YES" : "NO";
        cout<<"User has write permissions on newfile: "<<flag<<endl;

        flag = (snewFile.st_mode & S_IXUSR) ? "YES" : "NO";
        cout<<"User has execute permissions on newfile: "<<flag<<endl;


        flag = (snewFile.st_mode & S_IRGRP) ? "YES" : "NO";
        cout<<"Group has read permissions on newfile: "<<flag<<endl;

        flag = (snewFile.st_mode & S_IWGRP) ? "YES" : "NO";
        cout<<"Group has write permissions on newfile: "<<flag<<endl;

        flag = (snewFile.st_mode & S_IXGRP) ? "YES" : "NO";
        cout<<"Group has execute permissions on newfile: "<<flag<<endl;


        flag = (snewFile.st_mode & S_IROTH) ? "YES" : "NO";
        cout<<"Others has read permissions on newfile: "<<flag<<endl;

        flag = (snewFile.st_mode & S_IWOTH) ? "YES" : "NO";
        cout<<"Others has write permissions on newfile: "<<flag<<endl;

        flag = (snewFile.st_mode & S_IXOTH) ? "YES" : "NO";
        cout<<"Others has execute permissions on newfile: "<<flag<<endl;
    }

    if(stat(oldFilePath, &soldFile) == 0)//checks permissions on oldfile
    {
        flag = (soldFile.st_mode & S_IRUSR) ? "YES" : "NO";
        cout<<"User has read permissions on oldfile: "<<flag<<endl;

        flag = (soldFile.st_mode & S_IWUSR) ? "YES" : "NO";
        cout<<"User has write permissions on oldfile: "<<flag<<endl;

        flag = (soldFile.st_mode & S_IXUSR) ? "YES" : "NO";
        cout<<"User has execute permissions on oldfile: "<<flag<<endl;


        flag = (soldFile.st_mode & S_IRGRP) ? "YES" : "NO";
        cout<<"Group has read permissions on oldfile: "<<flag<<endl;

        flag = (soldFile.st_mode & S_IWGRP) ? "YES" : "NO";
        cout<<"Group has write permissions on oldfile: "<<flag<<endl;

        flag = (soldFile.st_mode & S_IXGRP) ? "YES" : "NO";
        cout<<"Group has execute permissions on oldfile: "<<flag<<endl;


        flag = (soldFile.st_mode & S_IROTH) ? "YES" : "NO";
        cout<<"Others has read permissions on oldfile: "<<flag<<endl;

        flag = (soldFile.st_mode & S_IWOTH) ? "YES" : "NO";
        cout<<"Others has write permissions on oldfile: "<<flag<<endl;

        flag = (soldFile.st_mode & S_IXOTH) ? "YES" : "NO";
        cout<<"Others has execute permissions on oldfile: "<<flag<<endl;
    }

    if(stat(dirPath, &sdir) == 0)//checks permissions on directory
    {
        flag = (sdir.st_mode & S_IRUSR) ? "YES" : "NO";
        cout<<"User has read permissions on directory: "<<flag<<endl;

        flag = (sdir.st_mode & S_IWUSR) ? "YES" : "NO";
        cout<<"User has write permissions on directory: "<<flag<<endl;

        flag = (sdir.st_mode & S_IXUSR) ? "YES" : "NO";
        cout<<"User has execute permissions on directory: "<<flag<<endl;


        flag = (sdir.st_mode & S_IRGRP) ? "YES" : "NO";
        cout<<"Group has read permissions on directory: "<<flag<<endl;

        flag = (sdir.st_mode & S_IWGRP) ? "YES" : "NO";
        cout<<"Group has write permissions on directory: "<<flag<<endl;

        flag = (sdir.st_mode & S_IXGRP) ? "YES" : "NO";
        cout<<"Group has execute permissions on directory: "<<flag<<endl;


        flag = (sdir.st_mode & S_IROTH) ? "YES" : "NO";
        cout<<"Others has read permissions on directory: "<<flag<<endl;

        flag = (sdir.st_mode & S_IWOTH) ? "YES" : "NO";
        cout<<"Others has write permissions on directory: "<<flag<<endl;

        flag = (sdir.st_mode & S_IXOTH) ? "YES" : "NO";
        cout<<"Others has execute permissions on directory: "<<flag<<endl;
    }


    return 0;
    
}