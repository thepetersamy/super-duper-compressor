#include <stdio.h>

int main() {


    FILE *file;
    char fileName[100];
    printf("Please enter path to file:\n");
    scanf("%s", fileName);

    file = fopen(fileName, "r");

    if(!file){
        printf("file entered can't be found\n");
        printf("exiting...");
        return -1;
    }

    printf("opened");

    char map[255] = { 0 };

    fclose(file);

    return 0;
}
