#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "04"

enum aoc_err
day_04()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    int res[2] = { 0, 0 };
    int num_of_cards[AOC_ARR_LEN] = { 0 };
    int card = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        int len = 0;
        int i = 0;
        int points = 0;
        int winning_nums[AOC_ARR_LEN];

        aoc_debug("%s\n", &line);

        /* go to the start of winning numbers */
        while (line[i] != ':')
        {
            i++;
        }
        i++;
        while (line[i] == ' ')
        {
            i++;
        }

        card++;
        num_of_cards[card] += 1;

        /* get winning numbers */
        while (1)
        {
            winning_nums[len++] = atoi(&line[i]);

            while (line[i] != ' ')
            {
                i++;
            }
            while (line[i] == ' ')
            {
                i++;
            }

            if (line[i] == '|')
            {
                i++;
                break;
            }
        }

        aoc_debug("winning nums \n");
        for (int i_win = 0; i_win < len; i_win++)
        {
            aoc_debug_s("%d ", winning_nums[i_win]);
        }
        aoc_debug_s("\n");

        while (line[i] == ' ')
        {
            i++;
        }

        /* calculate card points */
        aoc_debug("ours winning nums \n");
        int wins = 0;
        while (line[i] != '\n' && line[i] != '\0')
        {
            aoc_debug("i=%d line=%s\n", i, &line[i]);
            int num = atoi(&line[i]);
            for (int j = 0; j < len; j++)
            {
                if (num == winning_nums[j])
                {
                    aoc_debug_s("%d ", num);
                    wins++;
                    break;
                }
            }

            while (line[i] != ' ' && line[i] != '\n')
            {
                i++;
            }
            while (line[i] == ' ')
            {
                i++;
            }
        }
        aoc_debug_s("\n");

        /*
         * part 1
         * calculate points
         */
        if (wins)
            points = 1 << (wins - 1);
        aoc_debug("wins=%d points=%d\n", wins, points);

        /*
         * part 2
         * increment num of cards
         */
        aoc_debug("card=%d n1=%d n2=%d\n", card, card + 1, card + wins);
        for (int k = 1; k <= wins; k++)
        {
            num_of_cards[card + k] += num_of_cards[card];
            aoc_debug("cards[%d]=%d\n", card + k, num_of_cards[card + 1]);
        }

        res[0] += points;
    }

    fclose(fp);

    /*
     * part 2
     * add up all cards
     */
    for (int i = 1; i <= card; i++)
    {
        aoc_debug("card[%d]=%d\n", i, num_of_cards[i]);
        res[1] += num_of_cards[i];
    }

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
