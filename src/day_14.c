#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "14"
#define MAX_CACHE_LEN 200
char cache[MAX_CACHE_LEN][AOC_ARR_LEN][AOC_ARR_LEN];

static void
print_dish(char dish[AOC_ARR_LEN][AOC_ARR_LEN], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            aoc_debug_s("%c ", dish[i][j]);
        aoc_debug_s("\n");
    }
}

static void
tilt_north(char dish[AOC_ARR_LEN][AOC_ARR_LEN], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dish[i][j] == 'O')
            {
                int initial_pos = i;
                int final_pos = i - 1;

                while (final_pos >= 0 && dish[final_pos][j] == '.')
                    final_pos--;

                final_pos++;

                dish[initial_pos][j] = '.';
                dish[final_pos][j] = 'O';
            }
        }
    }
}

static void
tilt_west(char dish[AOC_ARR_LEN][AOC_ARR_LEN], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dish[i][j] == 'O')
            {
                int initial_pos = j;
                int final_pos = j - 1;

                while (final_pos >= 0 && dish[i][final_pos] == '.')
                    final_pos--;

                final_pos++;

                dish[i][initial_pos] = '.';
                dish[i][final_pos] = 'O';
            }
        }
    }
}

static void
tilt_south(char dish[AOC_ARR_LEN][AOC_ARR_LEN], int m, int n)
{
    for (int i = m - 1; i >= 0; i--)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (dish[i][j] == 'O')
            {
                int initial_pos = i;
                int final_pos = i + 1;

                while (final_pos < m && dish[final_pos][j] == '.')
                    final_pos++;

                final_pos--;

                dish[initial_pos][j] = '.';
                dish[final_pos][j] = 'O';
            }
        }
    }
}

static void
tilt_east(char dish[AOC_ARR_LEN][AOC_ARR_LEN], int m, int n)
{
    for (int i = m - 1; i >= 0; i--)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (dish[i][j] == 'O')
            {
                int initial_pos = j;
                int final_pos = j + 1;

                while (final_pos < n && dish[i][final_pos] == '.')
                    final_pos++;

                final_pos--;

                dish[i][initial_pos] = '.';
                dish[i][final_pos] = 'O';
            }
        }
    }
}

static void
do_rotation(char dish[AOC_ARR_LEN][AOC_ARR_LEN], int m, int n)
{
    tilt_north(dish, m, n);
    tilt_west(dish, m, n);
    tilt_south(dish, m, n);
    tilt_east(dish, m, n);

    print_dish(dish, m, n);
}

static int
load_on_north_beam(char dish[AOC_ARR_LEN][AOC_ARR_LEN], int m, int n)
{
    int load = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dish[i][j] == 'O')
                load += m - i;
        }
    }
    return load;
}

static int
present_in_cache(char cache[MAX_CACHE_LEN][AOC_ARR_LEN][AOC_ARR_LEN],
                 char dish[AOC_ARR_LEN][AOC_ARR_LEN],
                 int m,
                 int n,
                 int cache_len)
{
    for (int c = 0; c < cache_len; c++)
    {
        bool same = true;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (cache[c][i][j] != dish[i][j])
                {
                    same = false;
                    break;
                }
            }
            if (!same)
                break;
        }
        if (same)
            return c;
    }
    return -1;
}

enum aoc_err
day_14()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    int res[2] = { 0, 0 };
    char dish[AOC_ARR_LEN][AOC_ARR_LEN];
    int m = 0;
    int n = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        if (line[0] == '\n')
            break;

        int i = 0;
        while (line[i] != '\n' && line[i] != '\0')
        {
            dish[m][i] = line[i];
            i++;
        }
        if (n == 0)
            n = i;
        m++;
    }
    fclose(fp);

    aoc_debug("dish\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            aoc_debug_s("%c ", dish[i][j]);
        }
        aoc_debug_s("\n");
    }

    tilt_north(dish, m, n);
    res[0] = load_on_north_beam(dish, m, n);

    /*
     * part 2
     * rotation are bound to repeat after some time.
     * we have to find where it starts repeating
     * and repeating location can be used to get millionth occurrence from cache
     */

    /* complete the remaining rotation */
    tilt_west(dish, m, n);
    tilt_south(dish, m, n);
    tilt_east(dish, m, n);

    const int TOTAL_ROTATIONS = 1000000000;
    int cache_len = 0;
    int rotation = 1;     /* current rotation */
    int cache_match = -1; /* where cache matches */
    memcpy(cache[cache_len], dish, sizeof(dish));
    cache_len++;

    for (; rotation < TOTAL_ROTATIONS; rotation++)
    {
        do_rotation(dish, m, n);
        int cache_found = present_in_cache(cache, dish, m, n, cache_len);

        if (cache_found != -1)
        {
            aoc_debug(
              "found in cache loc=%d at rotation=%d\n", cache_found, rotation);
            cache_match = cache_found;
            break;
        }
        memcpy(cache[cache_len], dish, sizeof(dish));
        cache_len++;
        if (cache_len >= MAX_CACHE_LEN)
        {
            fprintf(stderr,
                    "D12: cache is not enough for part 2. please increase "
                    "MAX_CACHE_LEN and try again\n");
            return AOC_CACHE_LIMIT_EXCEEDED;
        }
    }

    int millionth_state_in_cache =
      ((TOTAL_ROTATIONS - 1 - cache_match) % (rotation - cache_match)) +
      cache_match;

    res[1] = load_on_north_beam(cache[millionth_state_in_cache], m, n);

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
