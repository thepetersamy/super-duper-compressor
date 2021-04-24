#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

int main()
{
    int map[256] = { 0 };

    FILE* file;
    char fileName[100] ,ch;
    printf("Please enter path to file:\n");
    scanf("%s", fileName);

    file = fopen(fileName, "r");

    if (!file) {
        printf("file entered can't be found\n");
        printf("exiting...");
        return -1;
    }
    printf("opened\n");

    while ((ch = fgetc(file)) != EOF)
    {
        int current = ch;
        map[current]++;

    }

    fclose(file);


    for (int i = 0; i < 256; i++) {
        if (map[i] != 0)
        {
            printf("%c : %d\n", i, map[i]);
        }
    }

    Node* head;


    return 0;
}
