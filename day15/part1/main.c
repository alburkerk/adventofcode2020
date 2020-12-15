#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 4000
#define INDEX_TO_FIND 2020


uint32_t input[INDEX_TO_FIND] = {  2, 0, 6, 12, 1, 3 };

int indexOfNumber(uint32_t number, int startIndex)
{
    for (int i = startIndex; i >= 0; i--)
    {
        if (input[i] == number)
        {
            return i;
        }
    }

    return -1;
}

int main(void)
{
    for (int i = 6; i < INDEX_TO_FIND; i++)
    {
        int index = indexOfNumber(input[i - 1], i - 2);

        if (index == -1)
        {
            input[i] = 0;
        }
        else
        {
            input[i] = i - index - 1;
        }
    }

    printf("solution : %u\n", input[INDEX_TO_FIND - 1]);
}
