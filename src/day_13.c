#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "13"

static bool
can_smudge_fix_it_horizontal(char valley[AOC_ARR_LEN][AOC_STR_LEN],
                             int m,
                             int n,
                             int r1,
                             int r2)
{
    int diff = 0;

    for (int i = 0; i < n; i++)
    {
        if (valley[r1][i] != valley[r2][i])
            diff++;

        if (diff > 1)
            return false;
    }

    return diff == 1;
}

static int
get_horizontal_reflection(char valley[AOC_ARR_LEN][AOC_STR_LEN],
                          int m,
                          int n,
                          int skip)
{
    int i = 0;

    while (i + 1 < m)
    {
        if (skip != i + 1 && 0 == strncmp(valley[i], valley[i + 1], n))
        {
            int _i = i - 1;
            int _j = i + 2;

            while (_i >= 0 && _j < m && 0 == strncmp(valley[_i], valley[_j], n))
            {
                _i--;
                _j++;
            }
            if (_i < 0 || _j >= m)
                return i + 1;
        }
        i++;
    }

    return -1;
}

static bool
same_cols(char valley[AOC_ARR_LEN][AOC_STR_LEN], int m, int n, int c1, int c2)
{
    if (c1 >= n || c2 >= n)
        return false;

    for (int i = 0; i < m; i++)
    {
        if (valley[i][c1] != valley[i][c2])
            return false;
    }
    return true;
}

static int
get_vertical_reflection(char valley[AOC_ARR_LEN][AOC_STR_LEN],
                        int m,
                        int n,
                        int skip)
{
    int i = 0;

    while (i + 1 < n)
    {
        if (skip != i + 1 && same_cols(valley, m, n, i, i + 1))
        {
            int _i = i - 1;
            int _j = i + 2;

            while (_i >= 0 && _j < n && same_cols(valley, m, n, _i, _j))
            {
                _i--;
                _j++;
            }
            if (_i < 0 || _j >= n)
                return i + 1;
        }
        i++;
    }

    return -1;
}

enum aoc_err
day_13()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    int res[2] = { 0, 0 };
    char valley[AOC_ARR_LEN][AOC_STR_LEN];
    int m, n;
    int hr1, vr1;
    int hr2 = -1;
    int vr2 = -1;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        m = 0;
        while (line[0] != '\n')
        {
            memcpy(valley[m++], line, AOC_STR_LEN);
            if (fgets(line, AOC_STR_LEN, fp) == NULL)
                break;
        }

        n = strlen(valley[0]) - 1;

        aoc_debug("m=%d n=%d\n", m, n);

        for (int i = 0; i < m; i++)
            aoc_debug("%s", &valley[i]);
        hr1 = get_horizontal_reflection(valley, m, n, -1);
        vr1 = get_vertical_reflection(valley, m, n, -1);
        aoc_debug("hr1=%d vr1=%d\n", hr1, vr1);

        hr1 = hr1 == -1 ? 0 : hr1;
        vr1 = vr1 == -1 ? 0 : vr1;
        res[0] += (hr1 * 100) + vr1;

        bool found_hr2 = false;
        bool found_vr2 = false;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                if (valley[i][j] == '.')
                    valley[i][j] = '#';
                else
                    valley[i][j] = '.';

                hr2 = get_horizontal_reflection(valley, m, n, hr1);

                if (hr2 != -1 && hr2 != hr1)
                {
                    goto p2res;
                }

                vr2 = get_vertical_reflection(valley, m, n, vr2);

                if (vr2 != -1 && vr2 != vr1)
                {
                    goto p2res;
                }

                if (valley[i][j] == '.')
                    valley[i][j] = '#';
                else
                    valley[i][j] = '.';
            }
        }
    p2res:
        aoc_debug("hr2=%d vr2=%d\n\n", hr2, vr2);
        hr2 = (hr2 == -1 || hr2 == hr1) ? 0 : hr2;
        vr2 = (vr2 == -1 || vr2 == vr1) ? 0 : vr2;
        res[1] += (hr2 * 100) + vr2;
    }

    fclose(fp);

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
