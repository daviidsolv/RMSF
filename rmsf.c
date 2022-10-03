#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>

int createTrashFolder();
int setupTrashFolder();

int main(int argc, char const *argv[])
{
    char* baseDir;
    getcwd(baseDir, sizeof(baseDir));
    //setupTrashFolder();
    for(int i = 2; i < argc; i++) {
        char* temp;
        strcpy(temp, baseDir);
        strcat(temp, argv[i]);
        moveToTrash(temp);
    }
    return 0;
}

int setupTrashFolder() {
    char final[30];
    char directory[] = "/home/";
    char* userName = getlogin();
    char binDir[] = "/.trash/   ";
    strcat(directory, userName);
    strcat(directory, binDir);
    strcpy(final, directory);
    printf("Trying to open: %s and %s\n", directory, final);
    DIR* dir = opendir(directory);
    if(dir) {
        printf("Directory already exists!\n");
    } else if (ENOENT == errno) {
        if(createTrashFolder(final) != 0)
            printf("Cannot create folder at location: %s\n", final);
    } else {
        printf("Undefined error!\n");
    }
    return 0;
}

int createTrashFolder(char directory[30]) {
    return mkdir(directory, 0777);
}

int moveToTrash(char* fileOrDirectory) {
    char trashbin[] = "/home/david/.trash";
    char* temp;
    char c;
    int i = strlen(fileOrDirectory);
    while(c != '/' || i == 0) {
        c = fileOrDirectory[i];
        strcat(temp, c);
        i--;
    }
    strcat(trashbin, strrev(temp));
    rename(fileOrDirectory, trashbin);
}
