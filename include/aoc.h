#ifndef __LIB_AOC_H__
#define __LIB_AOC_H__

#define INPUT_F(DAY) "input/day_" DAY

#define AOC_DAY_ALL 0x1FFFFFF
#define AOC_DAY_MIN 1
#define AOC_DAY_MAX 13

#define AOC_STR_LEN 4096
#define AOC_INT_MAX 0xFFFFFFFF

#define AOC_ARR_LEN 250

#define AOC_MAX(x, y) ((x > y) ? x : y)
#define AOC_MIN(x, y) ((x > y) ? y : x)
#define AOC_ABS(x) (((x) > 0) ? (x) : -(x))

// clang-format off
#define AOC_DIR_RIGHT {0, 1}
#define AOC_DIR_LEFT {0, -1}
#define AOC_DIR_DOWN {1, 0}
#define AOC_DIR_UP {-1, 0}
#define AOC_DIR_RIGHT_UP {-1, 1}
#define AOC_DIR_RIGHT_DOWN {1, 1}
#define AOC_DIR_LEFT_UP {-1, -1}
#define AOC_DIR_LEFT_DOWN {1, -1}
// clang-format on

#define AOC_IS_DIGIT(c) (c >= '0' && c <= '9')

#ifdef DEBUG
#define aoc_debug(arg, ...)                                                    \
    printf("AOC_DEBUG(%s:%d): " arg, __func__, __LINE__, ##__VA_ARGS__)
#define aoc_debug_s(arg, ...) printf(arg, ##__VA_ARGS__)
#else
#define aoc_debug(arg, ...)
#define aoc_debug_s(arg, ...)
#endif /* DEBUG */

enum aoc_dir
{
    AOC_DIR_RIGHT_ENUM = 0,
    AOC_DIR_LEFT_ENUM,
    AOC_DIR_DOWN_ENUM,
    AOC_DIR_UP_ENUM,
    AOC_DIR_RIGHT_UP_ENUM,
    AOC_DIR_RIGHT_DOWN_ENUM,
    AOC_DIR_LEFT_UP_ENUM,
    AOC_DIR_LEFT_DOWN_ENUM,
    AOC_DIR_MAX_ENUM
};

enum aoc_err
{
    AOC_SUCCESS = 0,
    AOC_INVALID_ARGS,
    AOC_INPUT_FILE_NOT_FOUND,
    AOC_TOO_MANY_INPUT_LINES
};

enum aoc_err
day_01();

enum aoc_err
day_02();

enum aoc_err
day_03();

enum aoc_err
day_04();

enum aoc_err
day_05();

enum aoc_err
day_06();

enum aoc_err
day_07();

enum aoc_err
day_08();

enum aoc_err
day_09();

enum aoc_err
day_10();

enum aoc_err
day_11();

enum aoc_err
day_12();

enum aoc_err
day_13();

typedef enum aoc_err (*solution)();

#endif /* __LIB_AOC_H__ */
