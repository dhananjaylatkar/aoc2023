#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "08"

#define LOC_LEN 3
#define MAX_LOCATION 17576 /* (26^2 * 25) + (26^1 * 25) + (26^0 * 25) + 1 */
#define MAX_NAVIGATION 1000

#define LOC_TO_DEC(z, y, x) ((676 * (z - 'A')) + (26 * (y - 'A') + (x - 'A')))

enum dir
{
    DIR_L = 0,
    DIR_R = 1
};

unsigned long long int
gcd(unsigned long long int a, unsigned long long int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

unsigned long long int
lcm(unsigned int arr[], int n)
{
    unsigned long long int ans = arr[0];

    for (int i = 1; i < n; i++)
    {
        ans = (((arr[i] * ans)) / (gcd(arr[i], ans)));
    }

    return ans;
}

enum aoc_err
day_08()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    unsigned long long int res[2] = { 0, 0 };

    int network[MAX_LOCATION][2] = { 0 };

    enum dir nav[MAX_NAVIGATION];
    int nav_cnt = 0;
    int nav_i = 0;

    /* part 1*/
    const int start_loc = LOC_TO_DEC('A', 'A', 'A');
    const int end_loc = LOC_TO_DEC('Z', 'Z', 'Z');
    int curr_loc = start_loc;

    /* part 2*/
    int start_locs[MAX_LOCATION];
    unsigned int sols[MAX_LOCATION] = { 0 };
    int start_locs_cnt = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    /* navigation */
    if (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        int i = 0;
        while (line[i] != '\n')
        {
            if (line[i] == 'R')
                nav[nav_cnt] = DIR_R;
            else
                nav[nav_cnt] = DIR_L;
            nav_cnt++;
            i++;
        }
    }

    /* network */
    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        if (line[0] == '\n')
            continue;

        int loc = LOC_TO_DEC(line[0], line[1], line[2]);
        network[loc][DIR_L] = LOC_TO_DEC(line[7], line[8], line[9]);
        network[loc][DIR_R] = LOC_TO_DEC(line[12], line[13], line[14]);

        if (line[2] == 'A')
            start_locs[start_locs_cnt++] = loc;

        aoc_debug("%c%c%c = %d\n",
                  line[0],
                  line[1],
                  line[2],
                  LOC_TO_DEC(line[0], line[1], line[2]));
    }

    fclose(fp);

    aoc_debug("nav: ");
    for (int i = 0; i < nav_cnt; i++)
    {
        aoc_debug_s("%d ", nav[i]);
    }
    aoc_debug_s("\n");

    while (curr_loc != end_loc)
    {
        aoc_debug("curr_loc=%d nav[%d]=%d\n", curr_loc, nav_i, nav[nav_i]);
        curr_loc = network[curr_loc][nav[nav_i]];
        nav_i = (nav_i + 1) % nav_cnt;
        res[0]++;
    }

    for (int i = 0; i < start_locs_cnt; i++)
    {
        nav_i = 0;
        curr_loc = start_locs[i];
        while (curr_loc % 26 != 25)
        {
            curr_loc = network[curr_loc][nav[nav_i]];
            nav_i = (nav_i + 1) % nav_cnt;
            sols[i]++;
        }
    }

    res[1] = lcm(sols, start_locs_cnt);

    printf("D" DAY "P1: %lld\n", res[0]);
    printf("D" DAY "P2: %lld\n", res[1]);

    return AOC_SUCCESS;
}
