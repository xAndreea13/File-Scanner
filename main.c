#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main()
{
    FILE *fileIn;
    char buffer[100];

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

    char * path = "F:\\Proiecte personale";
    list_content(path);

    return 0;
}

void list_content(char * path)
{
    DIR * d;
    struct dirent *dir;
    d = opendir(path);

    if(d != NULL)
    {
        while ((dir = readdir(d)) != NULL)
            printf("%s\n", dir->d_name);
    }

    closedir(d);
}