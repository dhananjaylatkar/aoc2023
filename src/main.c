#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <aoc.h>

solution solutions[AOC_DAY_MAX] = { day_01, day_02, day_03, day_04, day_05,
                                    day_06, day_07, day_08, day_09, day_10,
                                    day_11, day_12, day_13 };

int
main(int argc, char* argv[])
{

    int opt;
    int days = 0; /* bitmask of days */

    while ((opt = getopt(argc, argv, "ad:")) != -1)
    {
        switch (opt)
        {
            case 'a':
                days = AOC_DAY_ALL;
                break;
            case 'd':
            {
                int day = atoi(optarg);
                if (day >= AOC_DAY_MIN && day <= AOC_DAY_MAX)
                    days |= 1 << (day - 1);
                else
                    fprintf(
                      stderr, "Solution is not implemented for DAY %d\n", day);
                break;
            }
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-d day] [-a]\n", argv[0]);
                return AOC_INVALID_ARGS;
        }
    }

    for (int i = 0; i < AOC_DAY_MAX; i++)
    {
        if (days & (1 << i))
            solutions[i]();
    }

    return AOC_SUCCESS;
}
