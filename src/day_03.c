#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "03"

void
read_inp_arr(FILE* fp, char inp[AOC_ARR_LEN][AOC_ARR_LEN], int* n, int* m)
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

enum aoc_err
day_03()
{
    FILE* fp;
    int res[2] = { 0, 0 };
    char schematic[AOC_ARR_LEN][AOC_ARR_LEN];
    int n = 0;
    int m = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    read_inp_arr(fp, schematic, &n, &m);

    aoc_debug("n=%d m=%d\n", n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%c ", schematic[i][j]);
        printf("\n");
    }

    fclose(fp);

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
