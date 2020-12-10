#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 4000

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;

        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }

        swap(&arr[min_idx], &arr[i]);
    }
}

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int adapters[MAX_LINES];
    int i = 0;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        adapters[i] = strtol(line, NULL, 10);
        i++;
    }

    sort(adapters, i);
    adapters[i] = adapters[i - 1] + 3;
    i++;
    long solution[500];

    // clean
    for (int j = 0 ; j < i; j++)
    {
        solution[j] = 0;
    }

    solution[0] = 1;

    for (int j = 0;  j < i; j++)
    {
        solution[adapters[j]] = 0;

        if (adapters[j] > 0)
        {
            solution[adapters[j]] += solution[adapters[j] - 1];
        }

        if (adapters[j] > 1)
        {
            solution[adapters[j]] += solution[adapters[j] - 2];
        }

        if (adapters[j] > 2)
        {
            solution[adapters[j]] += solution[adapters[j] - 3];
        }
    }

    printf("solution is %ld\n", solution[adapters[i - 1]]);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
