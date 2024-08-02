#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_content(char * path);
void list_content_v2(char * path);

//simple linked list
struct node
{
    char * path;
    struct node * next;
};

int main()
{
    /*
    FILE *fileIn;
    fileIn = fopen("input.txt", "r");

    if(fileIn == NULL)
    {
        printf("Error opening input file!");
        return 1;
    }
    
    while(fgets(buffer, 100, fileIn) != NULL)
    {
        printf("%s", buffer);
    }
    */

    char * path = "C:\\";
    list_content_v2(path);

    return 0;
}

void list_content_v2(char * path)
{
    DIR * d;
    struct dirent *dir;
    struct stat statbuf;
    struct node * current = NULL;

    d = opendir(path);

    if(d != NULL)
    {
        struct node * folder = malloc(sizeof(struct node));
        folder->path = (char *)malloc(strlen(path) + 1);
        strcpy(folder->path, path);
        folder->next = NULL;

        current = folder;

        do
        {
            while ((dir = readdir(d)) != NULL)
            {
                if(strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0)
                {
                    //skip the "." and ".." files
                    continue;
                }

                //we build the subpath to the next directory

                char * subpath = (char*)malloc(strlen(current->path) + strlen(dir->d_name) + 2);
                strcpy(subpath, current->path);
                strcat(subpath, "\\");
                strcat(subpath, dir->d_name);
                printf("%s ", subpath);

                if(stat(subpath, &statbuf) == -1)
                {
                    printf("Error recognising file type for %s\n", subpath);
                    free(subpath);
                    continue;
                }

                if(S_ISDIR(statbuf.st_mode))
                {
                    printf("\t-\t[Directory]\n");

                    folder->next = malloc(sizeof(struct node));
                    folder = folder->next;
                    folder->path = subpath;
                    folder->next = NULL;
                }
                else
                {
                    printf("\t-\t[File]\n");
                    free(subpath);
                    subpath = NULL;
                }

            }

            struct node * garb = current;
            current = current->next;
            free(garb->path);
            garb->path = NULL;
            garb->next = NULL;
            free(garb);
            garb = NULL;

            closedir(d);
            if(current != NULL)
            {
                d = opendir(current->path);
            }
            
        }while(current != NULL);
            
    }
    else
    {
        printf("Path not found");
    }
}

//this function is useful for listing the files in depth
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
                //skip the "." and ".." files
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
            closedir(d);
        }
    }
    else
    {
        printf("Path not found");
    }
}