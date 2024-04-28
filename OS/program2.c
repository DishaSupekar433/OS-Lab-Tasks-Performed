#include <stdio.h>
#include <unistd.h>

void main()
{
    int shared, y;
    FILE* fptr = fopen("shared.txt","r+");
    shared=5;
    y = shared;
    y--;
    sleep(10);
    shared = y;
    fprintf(fptr,"%d",shared);
    fclose(fptr);
}
