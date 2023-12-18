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
    SPRING_CHANGED_OPERATIONAL = 3,
    SPRING_CHANGED_DAMAGED = 4,
    SPRING_MAX
};

#define OPERATIONAL(x)                                                         \
    ((x) == SPRING_CHANGED_OPERATIONAL || (x) == SPRING_OPERATIONAL)
#define DAMAGED(x) ((x) == SPRING_CHANGED_DAMAGED || (x) == SPRING_DAMAGED)

bool
group_fits(enum spring_t springs[AOC_ARR_LEN],
           int springs_cnt,
           int springs_i,
           int group)
{
    int group_end = springs_i + group;

    if (group_end > springs_cnt)
        return false;

    for (int i = springs_i; i < group_end && i < springs_cnt; i++)
    {
        if (springs[i] != SPRING_UNKNOWN && springs[i] != SPRING_DAMAGED)
        {
            return false;
        }
    }

    if (group_end < springs_cnt && DAMAGED(springs[group_end]))
    {
        return false;
    }

    return true;
}

static void
insert_group(enum spring_t springs[AOC_ARR_LEN],
             int springs_cnt,
             int springs_i,
             int group)
{
    int group_end = springs_i + group;

    for (int i = springs_i; i < group_end && i < springs_cnt; i++)
    {
        if (springs[i] == SPRING_UNKNOWN)
        {
            springs[i] = SPRING_CHANGED_DAMAGED;
        }
    }

    if (group_end < springs_cnt && springs[group_end] == SPRING_UNKNOWN)
    {
        springs[group_end] = SPRING_CHANGED_OPERATIONAL;
    }
}

static void
remove_group(enum spring_t springs[AOC_ARR_LEN],
             int springs_cnt,
             int springs_i,
             int group)
{
    int group_end = springs_i + group;

    for (int i = springs_i; i < group_end && i < springs_cnt; i++)
    {
        if (springs[i] == SPRING_CHANGED_DAMAGED)
        {
            springs[i] = SPRING_UNKNOWN;
        }
    }

    if (group_end < springs_cnt &&
        springs[group_end] == SPRING_CHANGED_OPERATIONAL)
    {
        springs[group_end] = SPRING_UNKNOWN;
    }
}

int ways = 0;
static void
count(enum spring_t springs[AOC_ARR_LEN],
      int groups[AOC_ARR_LEN],
      int springs_cnt,
      int groups_cnt,
      int springs_i,
      int groups_i)
{

    aoc_debug_s("spings: ");
    for (int i = 0; i < springs_cnt; i++)
    {
        aoc_debug_s("%d ", springs[i]);
    }
    aoc_debug_s("\n");

    aoc_debug_s("groups: ");
    for (int i = 0; i < groups_cnt; i++)
    {
        aoc_debug_s("%d ", groups[i]);
    }
    aoc_debug_s("\n");
    aoc_debug("si=%d gi=%d sc=%d gc=%d\n",
              springs_i,
              groups_i,
              springs_cnt,
              groups_cnt);

    if (groups_i == groups_cnt)
    {
        for (int i = springs_i; i < springs_cnt; i++)
        {
            if (DAMAGED(springs[i]))
                return;
        }
        ways++;
        aoc_debug("ways=%d\n", ways);
        return;
    }

    if (springs_i >= springs_cnt)
    {
        aoc_debug("out of bounds\n");
        return;
    }

    int group = groups[groups_i];
    if (springs_i == 0 || (OPERATIONAL(springs[springs_i - 1]) ||
                           springs[springs_i - 1] == SPRING_UNKNOWN) &&
                            !OPERATIONAL(springs[springs_i]))
    {
        if (group_fits(springs, springs_cnt, springs_i, group))
        {
            aoc_debug("group=%d fits at %d\n", group, springs_i);

            insert_group(springs, springs_cnt, springs_i, group);

            count(springs,
                  groups,
                  springs_cnt,
                  groups_cnt,
                  springs_i + groups[groups_i] + 1,
                  groups_i + 1);

            remove_group(springs, springs_cnt, springs_i, group);
        }
        else
        {
            aoc_debug("group=%d does not fit at %d\n", group, springs_i);
        }
    }
    else
    {
        aoc_debug("group=%d does not fit at %d\n", group, springs_i);
        // aoc_debug("prev_spring=%d spring=%d condition1=%d condition2=%d\n",
        // springs[springs_i - 1], springs[springs_i], );
    }
    count(springs, groups, springs_cnt, groups_cnt, springs_i + 1, groups_i);
}

enum aoc_err
day_12()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    int res[2] = { 0, 0 };
    enum spring_t springs[AOC_ARR_LEN];
    int groups[AOC_ARR_LEN];
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
                    springs[springs_cnt] = SPRING_OPERATIONAL;
                    break;
                case '#':
                    springs[springs_cnt] = SPRING_DAMAGED;
                    break;
                case '?':
                    springs[springs_cnt] = SPRING_UNKNOWN;
                    break;
            }
            springs_cnt++;
            i++;
        }

        while (line[i] == ' ')
            i++;

        while (line[i] != '\n' && line[i] != '\0')
        {
            groups[groups_cnt++] = atoi(&line[i]);

            while (line[i] != ',' && line[i] != '\n' && line[i] != '\0')
                i++;

            if (line[i] == ',')
                i++;
        }
        ways = 0;
        count(springs, groups, springs_cnt, groups_cnt, 0, 0);
        res[0] += ways;
        printf("%d\n", ways);
    }

    fclose(fp);

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
