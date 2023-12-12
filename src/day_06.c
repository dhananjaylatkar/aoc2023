#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "06"

static void
parse_line(char line[], int arr[], int* len)
{
    int i = 0;
    int n = 0;
    while (line[i] != ':')
        i++;
    i++;
    while (line[i] == ' ')
        i++;

    while (line[i] != '\n')
    {
        arr[n++] = atoi(&line[i]);

        while (line[i] != ' ' && line[i] != '\n')
            i++;
        while (line[i] == ' ')
            i++;
    }
    *len = n;
}

enum aoc_err
day_06()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    int time[AOC_ARR_LEN];
    int dist[AOC_ARR_LEN];
    int t_len = 0;
    int d_len = 0;

    unsigned long int time2 = 0;
    unsigned long int dist2 = 0;
    char* time2_str;
    char* dist2_str;

    int res[2] = { 1, 0 };

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    fgets(line, AOC_STR_LEN, fp);
    parse_line(line, time, &t_len);

    fgets(line, AOC_STR_LEN, fp);
    parse_line(line, dist, &d_len);

    fclose(fp);

    /* part 1 */
    for (int i = 0; i < t_len; i++)
    {
        int win = 0;
        for (int j = 0; j <= time[i]; j++)
        {
            if ((time[i] - j) * j > dist[i])
                win++;
        }
        res[0] *= win;
    }

    /* part 2 */
    for (int i = 0; i < t_len; i++)
    {
        int len = snprintf(NULL, 0, "%d", time[i]);
        time2 = time2 * pow(10, len) + time[i];
        len = snprintf(NULL, 0, "%d", dist[i]);
        dist2 = dist2 * pow(10, len) + dist[i];
    }

    for (int j = 0; j <= time2; j++)
    {
        if ((time2 - j) * j > dist2)
            res[1]++;
    }

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
