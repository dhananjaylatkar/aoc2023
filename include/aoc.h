#ifndef __LIB_AOC_H__
#define __LIB_AOC_H__

#define INPUT_F(DAY) "input/day_" DAY

#define AOC_DAY_ALL 0x1FFFFFF
#define AOC_DAY_MIN 1
#define AOC_DAY_MAX 2

#define AOC_STR_LEN 4096
#define AOC_INT_MAX 0xFFFFFFFF

#define AOC_MAX(x, y)((x > y) ? x : y)
#define AOC_MIN(x, y)((x > y) ? y : x)

#ifdef DEBUG
#define aoc_debug(arg, ...)                                                    \
    printf("AOC_DEBUG(%s:%d): " arg, __func__, __LINE__, ##__VA_ARGS__)
#else
#define aoc_debug(arg, ...)
#endif /* DEBUG */

enum aoc_err
{
    AOC_SUCCESS = 0,
    AOC_INVALID_ARGS,
    AOC_INPUT_FILE_NOT_FOUND
};

enum aoc_err
day_01();

enum aoc_err
day_02();

typedef enum aoc_err (*solution)();

#endif /* __LIB_AOC_H__ */
