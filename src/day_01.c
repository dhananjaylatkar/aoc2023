#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "01"

#define INVALID_DIGIT -1
const char* numbers_s[10] = { "zero", "one", "two",   "three", "four",
                              "five", "six", "seven", "eight", "nine" };

/*
 * Converts string representation of number to integer
 */
static int
get_num(char* str)
{
    for (int i = 1; i < 10; i++)
    {
        if (0 == strncmp(str, numbers_s[i], strlen(numbers_s[i])))
            return i;
    }
    return -1;
}

static int
find_digit_1(char* str)
{
    if (*str >= '0' && *str <= '9')
        return *str - '0';

    return -1;
}

static int
find_digit_2(char* str)
{
    int num = get_num(str);

    if (num != -1)
        return num;
    else if (*str >= '0' && *str <= '9')
        return *str - '0';

    return -1;
}

static int
create_num_from_digits(int digits[])
{
    if (digits[1] == INVALID_DIGIT)
        digits[1] = digits[0];

    return 10 * digits[0] + digits[1];
}

static void
update_digit(int digits[], int val)
{
    if (-1 != val)
    {
        if (digits[0] == INVALID_DIGIT)
            digits[0] = val;
        else
            digits[1] = val;
    }
}

enum aoc_err
day_01()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    int res[2] = { 0, 0 };

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        int i = 0;
        int digits_1[] = { INVALID_DIGIT, INVALID_DIGIT };
        int digits_2[] = { INVALID_DIGIT, INVALID_DIGIT };

        while (line[i] != '\0')
        {
            int tmp_1 = find_digit_1(&line[i]);
            int tmp_2 = find_digit_2(&line[i]);
            update_digit(digits_1, tmp_1);
            update_digit(digits_2, tmp_2);
            i++;
        }
        res[0] += create_num_from_digits(digits_1);
        res[1] += create_num_from_digits(digits_2);
    }

    fclose(fp);

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
