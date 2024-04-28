#include <stdio.h>
#include <unistd.h>

void main()
{
    int shared, x;
    FILE *fptr = fopen("shared.txt", "r+");
    shared = 5;
    x = shared;
    x++;
    sleep(10);
    shared = x;
    fprintf(fptr, "%d", shared);
    fclose(fptr);
}
