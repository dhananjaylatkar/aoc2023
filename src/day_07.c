#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "07"

#define CARDS_IN_A_HAND 5

enum card_type
{
    CARD_2 = 0,
    CARD_3 = 1,
    CARD_4 = 2,
    CARD_5 = 3,
    CARD_6 = 4,
    CARD_7 = 5,
    CARD_8 = 6,
    CARD_9 = 7,
    CARD_T = 8,
    CARD_J = 9,
    CARD_Q = 10,
    CARD_K = 11,
    CARD_A = 12,
    CARD_MAX
};

enum hand_type
{
    HAND_HIGH_CARD = 0,
    HAND_ONE_PAIR = 1,
    HAND_TWO_PAIR = 2,
    HAND_THREE_OF_A_KIND = 3,
    HAND_FULL_HOUSE = 4,
    HAND_FOUR_OF_A_KIND = 5,
    HAND_FIVE_OF_A_KIND = 6,
    HAND_MAX
};

struct hand {
    int bid;
    enum hand_type type1;
    enum hand_type type2;
    enum card_type cards[CARDS_IN_A_HAND];
};

static enum card_type
get_card_type(char c)
{
    const char card_map[] = { '2', '3', '4', '5', '6', '7', '8',
                              '9', 'T', 'J', 'Q', 'K', 'A' };

    for (int i = CARD_2; i < CARD_MAX; i++)
    {
        if (c == card_map[i])
            return i;
    }

    return CARD_MAX;
}

static enum hand_type
get_hand_type1(enum card_type cards[CARDS_IN_A_HAND])
{
    int card_cnt[CARD_MAX] = { 0 };
    int kinds[6] = { 0 };

    for (int i = 0; i < CARDS_IN_A_HAND; i++)
    {
        card_cnt[cards[i]]++;
    }

    for (int i = 0; i < CARD_MAX; i++)
    {
        if (card_cnt[i])
        {
            kinds[card_cnt[i]]++;
        }
    }

    if (kinds[5] == 1)
        return HAND_FIVE_OF_A_KIND;

    if (kinds[4] == 1)
        return HAND_FOUR_OF_A_KIND;

    if (kinds[3] == 1 && kinds[2] == 1)
        return HAND_FULL_HOUSE;

    if (kinds[3] == 1 && kinds[1] == 2)
        return HAND_THREE_OF_A_KIND;

    if (kinds[2] == 2)
        return HAND_TWO_PAIR;

    if (kinds[2] == 1 && kinds[1] == 3)
        return HAND_ONE_PAIR;

    return HAND_HIGH_CARD;
}

static int
hand_comparator(const void* _h1, const void* _h2)
{
    struct hand* h1 = (struct hand*)_h1;
    struct hand* h2 = (struct hand*)_h2;

    if (h1->type1 < h2->type1)
    {
        return -1;
    }

    if (h1->type1 > h2->type1)
    {
        return 1;
    }

    /* hand type1 is same */

    for (int i = 0; i < CARDS_IN_A_HAND; i++)
    {
        if (h1->cards[i] < h2->cards[i])
            return -1;

        if (h1->cards[i] > h2->cards[i])
            return 1;
    }

    return 0;
}

enum aoc_err
day_07()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    unsigned int res[2] = { 0, 0 };
    struct hand hands[1001];
    int hands_cnt;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        int i = 0;
        struct hand new_hand;

        if (line[i] == '\n')
            continue;

        while (i < CARDS_IN_A_HAND)
        {
            new_hand.cards[i] = get_card_type(line[i]);
            i++;
        }

        new_hand.bid = atoi(&line[i]);
        new_hand.type1 = get_hand_type1(new_hand.cards);

        hands[hands_cnt++] = new_hand;
    }

    fclose(fp);

    qsort((void*)hands, hands_cnt, sizeof(struct hand), hand_comparator);

    for (int i = 0; i < hands_cnt; i++)
    {
        aoc_debug("cards: %d %d %d %d %d type1: %d bid: %d\n",
                  hands[i].cards[0],
                  hands[i].cards[1],
                  hands[i].cards[2],
                  hands[i].cards[3],
                  hands[i].cards[4],
                  hands[i].type1,
                  hands[i].bid);
        res[0] += (unsigned int)(i + 1) * hands[i].bid;
    }

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
