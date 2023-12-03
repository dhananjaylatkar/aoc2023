#ifndef __LIB_AOC_H__
#define __LIB_AOC_H__

#define INPUT_F(DAY) "input/day_" DAY

#define AOC_DAY_ALL 0x1FFFFFF
#define AOC_DAY_MIN 1
#define AOC_DAY_MAX 1

#define AOC_STR_LEN 4096

enum aoc_err
{
    AOC_SUCCESS = 0,
    AOC_INVALID_ARGS,
    AOC_INPUT_FILE_NOT_FOUND
};

enum aoc_err
day_01();

typedef enum aoc_err (*solution)();

#endif /* __LIB_AOC_H__ */
