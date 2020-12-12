#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 4000

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int input[MAX_LINES];
    int i = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        input[i] = strtol(line, NULL, 10);
        i++;
    }

    int index1 = 0;
    int index2 = 0;
    int index3 = 0;

    for(int j = 0; j < i; j++) {
        for(int k = j; k < i; k++) {
            for(int l = k; l < i; l++) {
                if (input[j] + input [k] + input[l] == 2020) {
                    index1 = j;
                    index2 = k;
                    index3 = l;
                    goto end;
                }
            }
        }
    }

end:
    printf("found items : %d %d %d\n", input[index1], input[index2], input[index3]);
    printf("solution is %d\n", input[index1] * input[index2] * input[index3]);

    if (line)
        free(line);

    fclose(fp);
}
