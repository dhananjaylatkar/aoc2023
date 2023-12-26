#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "12"

enum spring_t
{
    SPRING_OPERATIONAL = 0,
    SPRING_DAMAGED = 1,
    SPRING_UNKNOWN = 2,
    SPRING_MAX
};

static bool
operational_spring_in_range(const enum spring_t springs[],
                            const int start,
                            const int end)
{
    for (int i = start; i < end; i++)
    {
        if (springs[i] == SPRING_OPERATIONAL)
        {
            return true;
        }
    }
    return false;
}

unsigned long long int dp[(AOC_ARR_LEN * 5) + 4 + 1][(AOC_ARR_LEN * 5) + 1];

static unsigned long long int
count(const enum spring_t springs[],
      const int groups[],
      const int springs_cnt,
      const int groups_cnt,
      int si,
      int gi)
{
    if (dp[si][gi] != -1)
    {
        return dp[si][gi];
    }

    if (gi == groups_cnt)
    {
        for (int i = si; i < springs_cnt; i++)
        {
            if (springs[i] == SPRING_DAMAGED)
                return 0;
        }
        return 1;
    }

    if (si == springs_cnt)
    {
        if (gi == groups_cnt)
        {
            return 1;
        }
        return 0;
    }

    unsigned long long int res = 0;
    enum spring_t cur_spring = springs[si];

    if (cur_spring == SPRING_OPERATIONAL || cur_spring == SPRING_UNKNOWN)
    {
        res += count(springs, groups, springs_cnt, groups_cnt, si + 1, gi);
    }

    if (cur_spring == SPRING_DAMAGED || cur_spring == SPRING_UNKNOWN)
    {
        int cur_group = groups[gi];
        int group_end = si + cur_group;

        if (group_end <= springs_cnt &&
            !operational_spring_in_range(springs, si, group_end) &&
            (group_end == springs_cnt || springs[group_end] != SPRING_DAMAGED))
        {
            res += count(
              springs, groups, springs_cnt, groups_cnt, group_end + 1, gi + 1);
        }
    }

    dp[si][gi] = res;
    return res;
}

static void
create_input_for_part2(const enum spring_t springs1[],
                       const int groups1[],
                       enum spring_t springs2[],
                       int groups2[],
                       const int springs_cnt,
                       const int groups_cnt)

{

    int k = 0;
    int times = 0;
    while (1)
    {
        int j = 0;
        while (j < springs_cnt)
        {
            springs2[k++] = springs1[j++];
        }

        times++;
        if (times == 5)
            break;

        springs2[k++] = SPRING_UNKNOWN;
    }

    k = 0;
    times = 0;
    while (1)
    {
        int j = 0;
        while (j < groups_cnt)
        {
            groups2[k++] = groups1[j++];
        }

        times++;
        if (times == 5)
            break;
    }
}
enum aoc_err
day_12()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    unsigned long long int res[2] = { 0, 0 };
    enum spring_t springs1[AOC_ARR_LEN];
    enum spring_t springs2[AOC_ARR_LEN * 5 + 4];
    int groups1[AOC_ARR_LEN];
    int groups2[AOC_ARR_LEN * 5];
    int springs_cnt;
    int groups_cnt;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        if (line[0] == '\n' || line[0] == '\0')
            continue;

        int i = 0;
        springs_cnt = 0;
        groups_cnt = 0;

        while (line[i] != ' ')
        {
            switch (line[i])
            {
                case '.':
                    springs1[springs_cnt] = SPRING_OPERATIONAL;
                    break;
                case '#':
                    springs1[springs_cnt] = SPRING_DAMAGED;
                    break;
                case '?':
                    springs1[springs_cnt] = SPRING_UNKNOWN;
                    break;
            }
            springs_cnt++;
            i++;
        }

        while (line[i] == ' ')
            i++;

        while (line[i] != '\n' && line[i] != '\0')
        {
            groups1[groups_cnt++] = atoi(&line[i]);

            while (line[i] != ',' && line[i] != '\n' && line[i] != '\0')
                i++;

            if (line[i] == ',')
                i++;
        }
        aoc_debug("%s", &line[0]);

        create_input_for_part2(
          springs1, groups1, springs2, groups2, springs_cnt, groups_cnt);

        memset(dp, -1, sizeof(dp));
        unsigned long long int c1 =
          count(springs1, groups1, springs_cnt, groups_cnt, 0, 0);
        aoc_debug("c1=%d\n", c1);

        memset(dp, -1, sizeof(dp));
        unsigned long long int c2 = count(
          springs2, groups2, ((springs_cnt * 5) + 4), groups_cnt * 5, 0, 0);
        aoc_debug("c2=%d\n", c2);

        res[0] += c1;
        res[1] += c2;
    }

    fclose(fp);

    printf("D" DAY "P1: %lld\n", res[0]);
    printf("D" DAY "P2: %lld\n", res[1]);

    return AOC_SUCCESS;
}
