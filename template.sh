#!/usr/bin/env bash

DAY=$1

CODE_PATH="src/day_${DAY}.c"
INPUT_PATH="input/day_${DAY}"

rm -rf ${CODE_PATH} ${INPUT_PATH}

touch ${INPUT_PATH}

echo "#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY \"${DAY}\"

enum aoc_err
day_${DAY}()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    int res[2] = { 0, 0 };

    fp = fopen(INPUT_F(DAY), \"r\");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {

    }

    fclose(fp);

    printf(\"D\" DAY \"P1: \%d\\n\", res[0]);
    printf(\"D\" DAY \"P2: \%d\\n\", res[1]);

    return AOC_SUCCESS;
}
" >> ${CODE_PATH}
