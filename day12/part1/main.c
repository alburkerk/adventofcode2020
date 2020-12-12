#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINES 4000
#define PI 3.14159265
#define FLOAT_TO_INT(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    int x = 0;
    int y = 0;
    // east
    int xDir = 1;
    int yDir = 0;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        int moveDistance = strtol(&(line[1]), NULL, 10);

        if (line[0] == 'N')
        {
            y += moveDistance;
        }

        if (line[0] == 'S')
        {
            y -= moveDistance;
        }

        if (line[0] == 'E')
        {
            x += moveDistance;
        }

        if (line[0] == 'W')
        {
            x -= moveDistance;
        }

        if (line[0] == 'F')
        {
            x += xDir * moveDistance;
            y += yDir * moveDistance;
        }

        if (line[0] == 'L' || line[0] == 'R')
        {
            float angle = (float)moveDistance / 360.0f * 2 * PI;

            if (line[0] == 'R')
            {
                angle = -angle;
            }

            int _xDir = FLOAT_TO_INT((float)xDir * cos(angle) - (float)yDir * sin(angle));
            int _yDir = FLOAT_TO_INT((float)xDir * sin(angle) + (float)yDir * cos(angle));
            xDir = _xDir;
            yDir = _yDir;
        }
    }

    printf("solution : %d\n", abs(x) + abs(y));

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
