#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 4000
#define INDEX_TO_FIND 30000000
#define MAX_INDEXES  50000000

uint32_t input[6] = {  2, 0, 6, 12, 1, 3 };
int indexes[MAX_INDEXES] = {[0 ... MAX_INDEXES - 1] =  -1};

int main(void)
{
    printf("go\n");
    uint64_t solution = 0;
    uint64_t lastNumber = 0;
    uint64_t nextNumber = 0;
    uint64_t previousLastNumber = 0;

    for (int i = 0; i < 6; i++)
    {
        indexes[input[i]] = i;
    }

    for (int j = 6; j < INDEX_TO_FIND;)
    {
        if (lastNumber > MAX_INDEXES)
        {
            printf("\n:(\n");
            exit(-1);
        }

        if (indexes[lastNumber] == -1)
        {
            nextNumber = 0;
        }
        else
        {
            nextNumber = j - indexes[lastNumber];
        }

        indexes[lastNumber] = j++;
        previousLastNumber = lastNumber;
        lastNumber = nextNumber;
    }

    printf("solution : %llu\n", previousLastNumber);
}
