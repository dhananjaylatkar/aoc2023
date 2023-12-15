#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "11"

static int
comparator(const void* _g1, const void* _g2)
{
    unsigned long long int* g1 = (unsigned long long int*)_g1;
    unsigned long long int* g2 = (unsigned long long int*)_g2;

    if (g1[1] < g2[1])
    {
        return -1;
    }

    if (g1[1] > g2[1])
    {
        return 1;
    }

    return g1[0] - g2[0];
}

static unsigned long long int
get_dist(unsigned long long int x, unsigned long long int y)
{
    if (x > y)
        return x - y;
    return y - x;
}

static unsigned long long int
get_sum_of_dist(unsigned long long int galaxy_loc[AOC_ARR_LEN * AOC_ARR_LEN][2],
                int galaxy_loc_cnt,
                unsigned long long int expansion)
{
    unsigned long long int res = 0;
    unsigned long long int prev = -1;
    unsigned long long int e = 0;

    for (int i = 0; i < galaxy_loc_cnt; i++)
    {
        if (galaxy_loc[i][0] > prev + 1)
            e += (expansion - 1) * (galaxy_loc[i][0] - prev - 1);

        prev = galaxy_loc[i][0];
        galaxy_loc[i][0] += e;
    }

    qsort((void*)galaxy_loc, galaxy_loc_cnt, sizeof(galaxy_loc[0]), comparator);

    prev = -1;
    e = 0;

    for (int i = 0; i < galaxy_loc_cnt; i++)
    {
        if (galaxy_loc[i][1] > prev + 1)
            e += (expansion - 1) * (galaxy_loc[i][1] - prev - 1);

        prev = galaxy_loc[i][1];
        galaxy_loc[i][1] += e;
    }

    for (int i = 0; i < galaxy_loc_cnt - 1; i++)
    {
        for (int j = i + 1; j < galaxy_loc_cnt; j++)
        {
            unsigned long long int dist =
              get_dist(galaxy_loc[i][0], galaxy_loc[j][0]) +
              get_dist(galaxy_loc[i][1], galaxy_loc[j][1]);

            aoc_debug("G1=(%lld, %lld) G2=(%lld, %lld) dist=%lld\n",
                      galaxy_loc[i][0],
                      galaxy_loc[i][1],
                      galaxy_loc[j][0],
                      galaxy_loc[j][1],
                      dist);

            res += dist;
        }
    }

    return res;
}

enum aoc_err
day_11()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    unsigned long long int res[2] = { 0, 0 };
    unsigned long long int galaxy_loc[AOC_ARR_LEN * AOC_ARR_LEN][2];
    unsigned long long int galaxy_loc_cpy[AOC_ARR_LEN * AOC_ARR_LEN][2];
    int galaxy_loc_cnt = 0;
    int m = 0;
    int n = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        if (line[0] == '\n')
            continue;

        int i = 0;

        while (line[i] != '\n' && line[i] != '\0')
        {
            if (line[i] == '#')
            {
                galaxy_loc[galaxy_loc_cnt][0] = m;
                galaxy_loc[galaxy_loc_cnt][1] = i;
                galaxy_loc_cnt++;
            }
            i++;
        }

        if (n == 0)
            n = i;
        m++;
    }

    fclose(fp);

    aoc_debug("m=%d n=%d galaxies=%d\n", m, n, galaxy_loc_cnt);

    memcpy(galaxy_loc_cpy, galaxy_loc, sizeof(galaxy_loc));
    res[0] = get_sum_of_dist(galaxy_loc_cpy, galaxy_loc_cnt, 2);

    memcpy(galaxy_loc_cpy, galaxy_loc, sizeof(galaxy_loc));
    res[1] = get_sum_of_dist(galaxy_loc_cpy, galaxy_loc_cnt, 1000000);

    printf("D" DAY "P1: %lld\n", res[0]);
    printf("D" DAY "P2: %lld\n", res[1]);

    return AOC_SUCCESS;
}
