#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "15"

#define TOTAL_BOXES 256

struct lens {
    char lable[8];
    int focal_len;
    struct lens* next;
};

static struct lens*
ll_add(struct lens* head, struct lens* node)
{
    if (node == NULL)
        return head;

    if (head == NULL)
    {
        return node;
    }

    struct lens* tmp = head;
    while (tmp->next != NULL)
    {
        if (strcmp(&tmp->lable[0], &node->lable[0]) == 0)
        {
            tmp->focal_len = node->focal_len;
            return head;
        }
        tmp = tmp->next;
    }

    if (strcmp(&tmp->lable[0], &node->lable[0]) == 0)
    {
        tmp->focal_len = node->focal_len;
        return head;
    }
    tmp->next = node;
    return head;
}

static struct lens*
ll_remove(struct lens* head, char lable[8])
{
    if (head == NULL)
        return NULL;

    if (strcmp(&head->lable[0], &lable[0]) == 0)
    {
        struct lens* tmp = head->next;

        free(head);
        head = NULL;

        return tmp;
    }

    struct lens* prev = head;
    struct lens* curr = head->next;

    while (curr)
    {
        if (strcmp(&curr->lable[0], &lable[0]) == 0)
            break;

        prev = prev->next;
        curr = curr->next;
    }

    if (curr != NULL)
    {
        struct lens* next = curr->next;
        prev->next = next;

        free(curr);
        curr = NULL;
    }
    return head;
}

enum aoc_err
day_15()
{
    FILE* fp;
    int res[2] = { 0, 0 };

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    struct lens* boxes[TOTAL_BOXES] = { NULL };

    int curr_val1 = 0;
    int curr_val2 = 0;
    char c;
    char seq[8];

    while (1)
    {
        int seq_len = 0;
        int i = 0;

        /* collect the sequence */
        while ((c = fgetc(fp)) != EOF)
        {
            if (c == '\0' || c == '\n' || c == ',')
                break;
            seq[seq_len++] = c;
        }

        /*
         * part 1
         * hash all of the sequence and add it up
         */
        curr_val1 = 0;
        i = 0;
        while (i < seq_len)
        {
            aoc_debug_s("%c", seq[i]);
            curr_val1 += seq[i];
            curr_val1 *= 17;
            curr_val1 %= 256;
            i++;
        }
        aoc_debug_s(" curr_val1=%d\n", curr_val1);
        res[0] += curr_val1;

        /*
         * part 2
         * hash label part of sequence to get box position
         * add/remove based on remaining sequence
         */
        curr_val2 = 0;
        i = 0;
        while (i < seq_len && seq[i] != '-' && seq[i] != '=')
        {
            curr_val2 += seq[i];
            curr_val2 *= 17;
            curr_val2 %= 256;
            i++;
        }

        if (seq[i] == '=')
        {
            int focal_len = seq[i + 1] - '0';
            seq[i] = '\0';
            struct lens* node = malloc(sizeof(struct node*));
            memcpy(node->lable, seq, i + 1);
            node->focal_len = focal_len;
            node->next = NULL;

            boxes[curr_val2] = ll_add(boxes[curr_val2], node);
        }
        else if (seq[i] == '-')
        {
            seq[i] = '\0';

            boxes[curr_val2] = ll_remove(boxes[curr_val2], seq);
        }

        if (c == '\0' || c == '\n')
            break;
    }
    fclose(fp);

    /*
     * part 2
     * calculate power of each boxes and add them up
     */
    for (int b = 0; b < TOTAL_BOXES; b++)
    {
        struct lens* tmp = boxes[b];
        int power = 0;
        int slot = 1;

        if (tmp)
            aoc_debug("BOX: %d\n", b);

        while (tmp)
        {
            aoc_debug("lable=%s focal_len=%d\n", tmp->lable, tmp->focal_len);
            power += (b + 1) * slot * tmp->focal_len;
            slot++;

            struct lens* used = tmp;
            tmp = tmp->next;

            free(used);
            used = NULL;
        }
        res[1] += power;
    }

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
