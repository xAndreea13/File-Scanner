#include <stdio.h>

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

}