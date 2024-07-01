#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_content(char * path);

int main()
{
    FILE *fileIn;
    fileIn = fopen("input.txt", "r");

    if(fileIn == NULL)
    {
        printf("Error opening input file!");
        return 1;
    }

    /*
    while(fgets(buffer, 100, fileIn) != NULL)
    {
        printf("%s", buffer);
    }
    */

    char * path = "F:\\Proiecte personale";
    list_content(path);

    return 0;
}


void list_content(char * path)
{
    DIR * d;
    struct dirent *dir;
    struct stat statbuf;

    d = opendir(path);

    if(d != NULL)
    {
        char * subpath = NULL;

        while ((dir = readdir(d)) != NULL)
        {
            //dir is one element inside the directory
            if(strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0)
            {
                continue;
            }

            char * subpath = (char*)malloc(strlen(path) + strlen(dir->d_name) + 2);
            strcpy(subpath, path);
            strcat(subpath, "\\");
            strcat(subpath, dir->d_name);
            printf("%s", subpath);

            if(stat(subpath, &statbuf) == -1)
            {
                printf("Error recognising file type for %s", subpath);
                free(subpath);
                continue;
            }

            if(S_ISDIR(statbuf.st_mode))
            {
                printf("\t-\t[Directory]\n");
                list_content(subpath);
            }
            else
            {
                printf("\t-\t[File]\n");
            }

            free(subpath);
        }
    }

    closedir(d);
}