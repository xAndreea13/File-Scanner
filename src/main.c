#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include "include/double_linked_list.h"

void list_content(char * path);
void list_content_v2(char * path);
void scan(size_t size, char * path);

//simple linked list
struct node
{
    struct list_node node;
    char * path;
};

int main()
{
    char * path = "C:\\MinGW";
    list_content_v2(path);

    return 0;
}


//listing function
void list_content_v2(char * path)
{
    DIR * d;
    struct dirent *dir;
    struct stat statbuf;
    struct list_head lh;  //we create the list_head
    double_linked_list_init(&lh); //we initialize it

    struct node * current = NULL;  //a pointer to the current node in the list

    d = opendir(path);

    if(d != NULL)
    {
        struct node * folder = (struct node *)malloc(sizeof(struct node));  //we create a node 
        add_end_node(&lh, &folder->node); //we add it to the list
        folder->path = (char *)malloc(strlen(path) + 1);  //we allocate memory for the path
        strcpy(folder->path, path);  //we copy the path of the folder
        current = folder; //the current folder is the first folder
        /*
        At this point, we have a list with 1 node
        */

        do
        {
            while ((dir = readdir(d)) != NULL)  //as long as there is something to read inside the folder
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
                
                //we check if the path is a directory or a file
                if(stat(subpath, &statbuf) == -1)
                {
                    printf("Error recognising file type for %s\n", subpath);
                    free(subpath);
                    continue;
                }

                if(S_ISDIR(statbuf.st_mode))
                {
                    printf("\t-\t[Directory]\n");

                    folder = (struct node *)malloc(sizeof(struct node));  //we create a new node

                    if(folder != NULL)
                    {
                        add_end_node(&lh, &folder->node); //we add it to the list
                        folder->path = subpath;
                    }
                }
                else
                {
                    printf("\t-\t[File]\n");

                    /*
                    Here should the scanning take place?
                    */

                    //(*ptr)(statbuf.st_size, subpath);

                    free(subpath);
                    subpath = NULL;
                }

            }

            struct node * garb = current;
            current = (struct node*)get_next_node(&current->node);  //the address of list_node is the same as the one of the node
            remove_node(&lh, &garb->node);

            free(garb->path);
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