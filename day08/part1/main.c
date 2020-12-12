#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 4000

#define INSTRUCTION_MAX_LENGTH  10

typedef struct
{
    char instruction[INSTRUCTION_MAX_LENGTH];
    int argument;
} Instruction;

void debugInstructions(Instruction* ins)
{
    int pc = 0;

    while (1)
    {
        if (ins[pc].instruction[0] == '\0')
        {
            return;
        }

        printf("%d - %s (%d)\n", pc, ins[pc].instruction, ins[pc].argument);
        pc++;
    }
}

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int input[MAX_LINES];
    Instruction instructions[MAX_LINES];
    uint8_t runInstructionMap[MAX_LINES];
    int i = 0;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    // clean
    for (int j = 0; j < MAX_LINES; j++)
    {
        runInstructionMap[j] = 0;
        instructions[j].instruction[0] = '\0';
    }

    char delimiter[] = " ";

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char* token = strtok(line, delimiter);
        strcpy(instructions[i].instruction, token);
        token = strtok(NULL, delimiter);
        instructions[i].argument = strtol(token, NULL, 10);
        token = strtok(NULL, delimiter);

        if (token != NULL)
        {
            printf(":(\n");
            exit(0);
        }

        i++;
    }

    // run machine
    int pc = 0;
    int acc = 0;

    while (1)
    {
        if (runInstructionMap[pc] > 0)
        {
            break;
        }

        if (!strcmp(instructions[pc].instruction,  "acc"))
        {
            acc += instructions[pc].argument;
        }

        runInstructionMap[pc]++;

        if (!strcmp(instructions[pc].instruction, "jmp"))
        {
            pc += instructions[pc].argument;
        }
        else
        {
            pc++;
        }
    }

    printf("the instruction %d was run twice (acc = %d)\n", pc, acc);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
