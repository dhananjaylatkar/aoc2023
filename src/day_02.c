#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "02"

enum CUBE
{
    RED = 0,
    GREEN,
    BLUE,
    CUBE_MAX
};

const int given_cubes[CUBE_MAX] = { 12, 13, 14 };

enum CUBE
get_cube_color(char* str)
{
    switch (*str)
    {
        case 'r':
            return RED;
        case 'g':
            return GREEN;
        case 'b':
            return BLUE;
    }
    return CUBE_MAX;
}

bool
is_game_possible(int cubes[])
{
    for (int i = 0; i < CUBE_MAX; i++)
    {
        if (cubes[i] > given_cubes[i])
            return false;
    }
    return true;
}

enum aoc_err
day_02()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    unsigned long long int res[2] = { 0, 0 };
    int game_id = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        int i = 0;
        int num;
        int color;
        int is_valid = true;
        int min_cubes[CUBE_MAX] = { 0, 0, 0 };

        game_id++;
        /* skip the game ID in string */
        while (line[i++] != ':')
        {
        }
        aoc_debug("%s", line);
        aoc_debug("Game ID: %d\n", game_id);

        /* parse all turns for that game_id */
        while (line[i] != '\n')
        {
            int cubes[CUBE_MAX] = { 0, 0, 0 };

            /* parse each game turn */
            while (line[i] != ';' && line[i] != '\n')
            {
                /* seek to the start of number */
                while (line[i++] != ' ')
                {
                }

                /* get num of cubes */
                num = atoi(&line[i]);

                /* seek to the start of color */
                while (line[i++] != ' ')
                {
                }

                /* get color of cube */
                if (CUBE_MAX != (color = get_cube_color(&line[i])))
                    cubes[color] = num;
                else
                    aoc_debug("color is wrong. should not reach here\n");

                /* seek to next game turn */
                while (line[i] != ',' && line[i] != ';' && line[i] != '\n')
                {
                    i++;
                }
                if (line[i] == ',')
                    i++;
            }

            aoc_debug(
              "Cubes: R=%d G=%d B=%d\n", cubes[RED], cubes[GREEN], cubes[BLUE]);

            /* 
             * part 1
             * check whether game turn is possible or not
             */
            if (is_valid)
                is_valid = is_game_possible(cubes);

            /* 
             * part 2
             * get min cubes required for the game
             */
            for (int j = 0; j < CUBE_MAX; j++)
                min_cubes[j] = AOC_MAX(min_cubes[j], cubes[j]);

            if (line[i] == '\n')
                break;
            i++;
        }

        /* part 1 */
        aoc_debug("Valid: %d\n", is_valid);
        if (is_valid)
        {
            res[0] += game_id;
        }

        /* part 2 */
        aoc_debug("Min Cubes: R=%d G=%d B=%d power=%d\n",
                  min_cubes[RED],
                  min_cubes[GREEN],
                  min_cubes[BLUE],
                  min_cubes[RED] * min_cubes[GREEN] * min_cubes[BLUE]);
        res[1] += min_cubes[RED] * min_cubes[GREEN] * min_cubes[BLUE];
    }

    fclose(fp);

    printf("D" DAY "P1: %llu\n", res[0]);
    printf("D" DAY "P2: %llu\n", res[1]);

    return AOC_SUCCESS;
}
