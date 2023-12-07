#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "03"

int dir[8][2] = {
    AOC_DIR_RIGHT,    AOC_DIR_LEFT,       AOC_DIR_DOWN,    AOC_DIR_UP,
    AOC_DIR_RIGHT_UP, AOC_DIR_RIGHT_DOWN, AOC_DIR_LEFT_UP, AOC_DIR_LEFT_DOWN,
};

void static read_inp_arr(FILE* fp,
                         char inp[AOC_ARR_LEN][AOC_ARR_LEN],
                         int* n,
                         int* m)
{
    char line[AOC_STR_LEN];
    int _n = 0;
    int _m = 0;
    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        if (0 == _m)
        {
            aoc_debug("%d\n", _m);
            while ('\n' != line[_m])
                _m++;
        }
        int i = 0;
        while (i < _m)
        {
            inp[_n][i] = line[i];
            i++;
        }
        _n++;
    }

    *n = _n;
    *m = _m;
}

static bool
does_surrounding_have_symbol(char inp[AOC_ARR_LEN][AOC_ARR_LEN],
                             const int n,
                             const int m,
                             const int i,
                             const int j)
{
    for (int d = AOC_DIR_RIGHT_ENUM; d < AOC_DIR_MAX_ENUM; d++)
    {
        int x = i + dir[d][0];
        int y = j + dir[d][1];

        if (x >= 0 && x < n && y >= 0 && y < m && inp[x][y] != '.' &&
            !AOC_IS_DIGIT(inp[x][y]))
        {
            return true;
        }
    }
    return false;
}

static unsigned long int
get_gear_ratio(char inp[AOC_ARR_LEN][AOC_ARR_LEN],
               const int n,
               const int m,
               const int i,
               const int j)
{
    unsigned long int ratio = 1;
    int num_count = 0;
    int skip_dir = 0;
    for (int d = AOC_DIR_RIGHT_ENUM; d < AOC_DIR_MAX_ENUM; d++)
    {
        if (skip_dir & 1 << d)
            continue;

        int x = i + dir[d][0];
        int y = j + dir[d][1];

        if (x >= 0 && x < n && y >= 0 && y < m && AOC_IS_DIGIT(inp[x][y]))
        {
            num_count++;
            if (num_count > 2)
                return 0;

            int _j = y;
            int num = 0;
            while (_j >= 0 && AOC_IS_DIGIT(inp[x][_j]))
                _j--;

            _j++;

            if (d == AOC_DIR_UP_ENUM && _j < y)
            {
                skip_dir |= 1 << AOC_DIR_LEFT_UP_ENUM;
            }
            else if (d == AOC_DIR_DOWN_ENUM && _j < y)
            {
                skip_dir |= 1 << AOC_DIR_LEFT_DOWN_ENUM;
            }

            aoc_debug("x=%d _j=%d\n", x, _j);
            while (_j < m && AOC_IS_DIGIT(inp[x][_j]))
            {
                num = (num * 10) + (inp[x][_j] - '0');
                aoc_debug("char=%c\n", inp[x][_j]);
                _j++;
            }
            aoc_debug("found num=%d at d=%d\n", num, d);

            if (d == AOC_DIR_UP_ENUM && _j > y)
            {
                skip_dir |= 1 << AOC_DIR_RIGHT_UP_ENUM;
            }
            else if (d == AOC_DIR_DOWN_ENUM && _j > y)
            {
                skip_dir |= 1 << AOC_DIR_RIGHT_DOWN_ENUM;
            }

            ratio *= num;
        }
    }
    if (num_count == 2)
        return ratio;
    return 0;
}
enum aoc_err
day_03()
{
    FILE* fp;
    unsigned long int res[2] = { 0, 0 };
    char schematic[AOC_ARR_LEN][AOC_ARR_LEN];
    int n = 0;
    int m = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    read_inp_arr(fp, schematic, &n, &m);

    fclose(fp);

    aoc_debug("n=%d m=%d\n", n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m;)
        {
            int num = 0;
            bool is_valid = false;

            while (true)
            {
                if (j >= m ||
                    !AOC_IS_DIGIT(schematic[i][j]) && schematic[i][j] != '*')
                {
                    j++;
                    break;
                }

                if (schematic[i][j] == '*')
                {
                    /*
                     * part 2
                     * found gear => get gear ratio
                     */
                    aoc_debug("p2\n");
                    res[1] += get_gear_ratio(schematic, n, m, i, j);
                    j++;
                    break;
                }

                /* part 1
                 * found digit => create number and also check if surrounding
                 * has symbol
                 */
                num = (num * 10) + (schematic[i][j] - '0');
                aoc_debug("curr_char=%c converted_char=%d num=%d\n",
                          schematic[i][j],
                          schematic[i][j] - '0',
                          num);

                is_valid |= does_surrounding_have_symbol(schematic, n, m, i, j);
                j++;
            }

            aoc_debug("num=%d is_valid=%d\n", num, is_valid);

            if (is_valid)
                res[0] += num;
        }
    }

    printf("D" DAY "P1: %lu\n", res[0]);
    printf("D" DAY "P2: %lu\n", res[1]);

    return AOC_SUCCESS;
}
