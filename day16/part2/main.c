#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RANGE_VALUE 4000
#define MAX_TICKET_LENGTH 800
#define MAX_VALID_TICKETS 4000
#define MAX_TICKET_ENTRIES 1000

uint8_t validMap[MAX_RANGE_VALUE] = { 0 };
uint32_t validTickets[MAX_VALID_TICKETS][MAX_TICKET_LENGTH];
uint32_t ranges[MAX_TICKET_ENTRIES][4];
uint32_t validRanges[MAX_TICKET_ENTRIES][MAX_TICKET_ENTRIES];
uint32_t departureEntriesIndex[6];
uint32_t myTicket[20];

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    int k = 0;
    int p = 0;
    int stage = 0;
    uint32_t error = 0;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (strlen(line) == 1)
        {
            stage++;
            i = 0;
            continue;
        }

        if (stage == 0)
        {
            if (memcmp(line, "departure", 9) == 0)
            {
                departureEntriesIndex[p] = i;
                p++;
            }

            char* delimiter = ":-";
            char* token = strtok(line, delimiter);
            char* delimiter2 = "- ";
            token = strtok(NULL, delimiter2);
            uint32_t range1 = strtol(token, NULL, 10);
            token = strtok(NULL, delimiter2);
            uint32_t range2 = strtol(token, NULL, 10);
            token = strtok(NULL, delimiter2);
            token = strtok(NULL, delimiter2);
            uint32_t range3 = strtol(token, NULL, 10);
            token = strtok(NULL, delimiter2);
            uint32_t range4 = strtol(token, NULL, 10);
            int j = range1;

            while (j <= range2)
            {
                validMap[j] = 1;
                j++;
            }

            j = range3;

            while (j <= range4)
            {
                validMap[j] = 1;
                j++;
            }

            ranges[i][0] = range1;
            ranges[i][1] = range2;
            ranges[i][2] = range3;
            ranges[i][3] = range4;
            i++;
        }

        if (stage == 1)
        {
            if (memcmp(line, "your", 4) == 0)
            {
                continue;
            }

            char* delimiter = ",";
            char* token = strtok(line, delimiter);
            int u = 0;

            while (token != NULL)
            {
                myTicket[u] = strtol(token, NULL, 10);
                u++;
                token = strtok(NULL, delimiter);
            }
        }

        if (stage == 2)
        {
            if (memcmp(line, "nearby", 5) == 0)
            {
                continue;
            }

            char* delimiter = ",";
            char lineCopy[200];
            strcpy(lineCopy, line);
            char* token = strtok(line, delimiter);
            uint8_t isValid = 1;

            while (token != NULL)
            {
                if (!validMap[strtol(token, NULL, 10)])
                {
                    error += strtol(token, NULL, 10);
                    isValid = 0;
                }

                token = strtok(NULL, delimiter);
            }

            if (isValid)
            {
                char* delimiter2 = ",";
                token = strtok(lineCopy, delimiter2);
                k = 0;

                while (token != NULL)
                {
                    validTickets[i][k] = strtol(token, NULL, 10);
                    k++;
                    token = strtok(NULL, delimiter2);
                }

                i++;
            }
        }
    }

    int numberOfTickets = i;
    int numberOfEntriesPerTicket = k;

    // prepare valid ranges map
    for (int x = 0; x < numberOfEntriesPerTicket; x++)
    {
        for (int y = 0; y < numberOfEntriesPerTicket; y++)
        {
            validRanges[x][y] = 1;
        }
    }

    for (int t = 0; t < numberOfTickets; t++)
    {
        for (int e = 0; e < numberOfEntriesPerTicket; e++)
        {
            for (int r = 0; r < numberOfEntriesPerTicket; r++)
            {
                if (validTickets[t][e] < ranges[r][0] || validTickets[t][e] > ranges[r][3] || (validTickets[t][e] > ranges[r][1] && validTickets[t][e] < ranges[r][2]))
                {
                    // entry e not valid for range r
                    validRanges[r][e] = 0;
                }
            }
        }
    }

    int validEntryForRangeCount = 0;

    for (int h = 0; h < numberOfEntriesPerTicket; h++)
    {
        for (int e = 0; e < numberOfEntriesPerTicket; e++)
        {
            validEntryForRangeCount = 0;
            int range = 0;

            for (int r = 0; r < numberOfEntriesPerTicket; r++)
            {
                validEntryForRangeCount += validRanges[r][e];

                if (validRanges[r][e])
                {
                    range = r;
                }
            }

            if (validEntryForRangeCount == 1)
            {
                for (int e1 = 0; e1 < numberOfEntriesPerTicket; e1++)
                {
                    if (e1 == e)
                    {
                        continue;
                    }

                    validRanges[range][e1] = 0;
                }
            }
        }
    }

    uint64_t solution = 1;

    for (int r = 0; r < numberOfEntriesPerTicket; r++)
        for (int e = 0; e < numberOfEntriesPerTicket; e++)
            if (validRanges[r][e])
            {
                for (int y = 0; y < 6; y++)
                {
                    if (departureEntriesIndex[y] == r)
                    {
                        solution *= (uint64_t)myTicket[e];
                    }
                }
            }

    printf("solution : %llu\n", solution);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
