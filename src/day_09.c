#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "09"

static void
parse_line(char line[], int arr[], int* len)
{
    int i = 0;
    int n = 0;

    while (line[i] != '\n' && line[i] != '\0')
    {
        arr[n++] = atoi(&line[i]);

        while (line[i] != ' ' && line[i] != '\n')
            i++;
        while (line[i] == ' ')
            i++;
    }
    *len = n;
}

/* return true if first n entries are zero */
static bool
n_zeroes(int history[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (history[i] != 0)
            return false;
    }
    return true;
}

static void
get_values(int history[], int n, int* prev, int* next)
{
    int level = 0;
    int next_val = 0;
    int prev_val = 0;
    int prev_sign = 1;

    while (!n_zeroes(history, n - level))
    {
        next_val += history[n - level - 1];
        prev_val += prev_sign * history[0];
        prev_sign *= -1;
        for (int i = 0; i < n - level - 1; i++)
        {
            history[i] = history[i + 1] - history[i];
        }
        level++;
    }

    aoc_debug(
      "n=%d level=%d prev_val=%d next_val=%d\n", n, level, prev_val, next_val);
    *next = next_val;
    *prev = prev_val;
}

enum aoc_err
day_09()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    int res[2] = { 0, 0 };
    int history[AOC_ARR_LEN];
    int history_len = 0;
    int next_val = 0;
    int prev_val = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        if (line[0] == '\n')
            continue;

        parse_line(line, history, &history_len);
        get_values(history, history_len, &prev_val, &next_val);
        res[0] += next_val;
        res[1] += prev_val;
    }

    fclose(fp);

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
