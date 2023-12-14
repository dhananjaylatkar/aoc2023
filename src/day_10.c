#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "10"

#define VALID_COORD(x, y) (x >= 0 && x < m && y >= 0 && y < n)

enum pipe_t
{
    PIPE_VERTICAL = 0,
    PIPE_HORIZONTAL = 1,
    PIPE_BOT_LEFT = 2,
    PIPE_BOT_RIGHT = 3,
    PIPE_TOP_RIGHT = 4,
    PIPE_TOP_LEFT = 5,
    PIPE_S = 6,
    PIPE_NONE = 7,
    PIPE_MAX
};

int dirs[PIPE_MAX - 2][2][2] = {
    { AOC_DIR_UP, AOC_DIR_DOWN },   { AOC_DIR_RIGHT, AOC_DIR_LEFT },
    { AOC_DIR_UP, AOC_DIR_RIGHT },  { AOC_DIR_UP, AOC_DIR_LEFT },
    { AOC_DIR_DOWN, AOC_DIR_LEFT }, { AOC_DIR_DOWN, AOC_DIR_RIGHT }
};

static enum pipe_t
get_pipe_type(char p)
{
    const char pipes[] = "|-LJ7FS.";

    for (int i = 0; i < PIPE_MAX; i++)
    {
        if (p == pipes[i])
            return i;
    }
    return PIPE_MAX;
}

int p1 = 0;
bool path[AOC_ARR_LEN][AOC_ARR_LEN];

void
dfs(enum pipe_t ground[AOC_ARR_LEN][AOC_ARR_LEN],
    bool visited[AOC_ARR_LEN][AOC_ARR_LEN],
    int m,
    int n,
    int x,
    int y,
    int curr_dist)
{
    if (ground[x][y] == PIPE_S)
    {
        int prev = p1;
        p1 = AOC_MAX(p1, curr_dist);
        if (prev != p1)
        {
            memcpy(path, visited, sizeof(path));
        }
        return;
    }

    for (int i = 0; i < 2; i++)
    {
        int new_x = x + dirs[ground[x][y]][i][0];
        int new_y = y + dirs[ground[x][y]][i][1];

        if (!VALID_COORD(new_x, new_y) || visited[new_x][new_y] ||
            ground[new_x][new_y] >= PIPE_NONE)
            continue;

        visited[new_x][new_y] = true;
        dfs(ground, visited, m, n, new_x, new_y, curr_dist + 1);
        visited[new_x][new_y] = false;
    }
}

static void
print_path(enum pipe_t ground[AOC_ARR_LEN][AOC_ARR_LEN], int m, int n)
{
    for (int k = 0; k < m; k++)
    {
        for (int j = 0; j < n; j++)
        {
            if (path[k][j])
            {
                switch (ground[k][j])
                {
                    case PIPE_VERTICAL:
                        aoc_debug_s("|");
                        break;
                    case PIPE_HORIZONTAL:
                        aoc_debug_s("-");
                        break;
                    case PIPE_TOP_LEFT:
                        aoc_debug_s("┌");
                        break;
                    case PIPE_TOP_RIGHT:
                        aoc_debug_s("┐");
                        break;
                    case PIPE_BOT_LEFT:
                        aoc_debug_s("└");
                        break;
                    case PIPE_BOT_RIGHT:
                        aoc_debug_s("┘");
                        break;
                    case PIPE_S:
                        aoc_debug_s("S");
                        break;
                    case PIPE_NONE:
                        aoc_debug_s(".");
                        break;
                }
            }

            else
                aoc_debug_s(".");
        }
        aoc_debug_s("\n");
    }
}
enum aoc_err
day_10()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    int res[2] = { 0, 0 };

    enum pipe_t ground[AOC_ARR_LEN][AOC_ARR_LEN];
    int m = 0;
    int n = 0;
    int start[2] = { 0, 0 };
    int s_dirs[4][2] = { 0 };
    int s_dirs_cnt = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        int i = 0;
        while (line[i] != '\n' && line[i] != '\0')
        {
            ground[m][i] = get_pipe_type(line[i]);

            if (line[i] == 'S')
            {
                start[0] = m;
                start[1] = i;
            }

            i++;
        }
        if (n == 0)
            n = i;
        m++;
    }

    fclose(fp);
    aoc_debug("m=%d n=%d start=(%d, %d)\n", m, n, start[0], start[1]);

    int _x = start[0];
    int _y = start[1];
    if (VALID_COORD(_x + 1, _y))
    {
        int _g = ground[_x + 1][_y];
        if (_g == PIPE_VERTICAL || _g == PIPE_BOT_LEFT || _g == PIPE_BOT_RIGHT)
        {
            s_dirs[s_dirs_cnt][0] = 1;
            s_dirs_cnt++;
        }
    }
    if (VALID_COORD(_x - 1, _y))
    {
        int _g = ground[_x - 1][_y];
        if (_g == PIPE_VERTICAL || _g == PIPE_TOP_LEFT || _g == PIPE_TOP_RIGHT)
        {
            s_dirs[s_dirs_cnt][0] = -1;
            s_dirs_cnt++;
        }
    }
    if (VALID_COORD(_x, _y + 1))
    {
        int _g = ground[_x][_y + 1];
        if (_g == PIPE_HORIZONTAL || _g == PIPE_TOP_RIGHT ||
            _g == PIPE_BOT_RIGHT)
        {
            s_dirs[s_dirs_cnt][1] = 1;
            s_dirs_cnt++;
        }
    }
    if (VALID_COORD(_x, _y - 1))
    {
        int _g = ground[_x][_y - 1];
        if (_g == PIPE_HORIZONTAL || _g == PIPE_TOP_LEFT || _g == PIPE_BOT_LEFT)
        {
            s_dirs[s_dirs_cnt][1] = -1;
            s_dirs_cnt++;
        }
    }

    p1 = 0;
    for (int i = 0; i < s_dirs_cnt; i++)
    {
        bool visited[AOC_ARR_LEN][AOC_ARR_LEN] = { 0 };
        int _x = start[0] + s_dirs[i][0];
        int _y = start[1] + s_dirs[i][1];
        visited[_x][_y] = true;
        dfs(ground, visited, m, n, _x, _y, 1);

        if (p1)
        {
            print_path(ground, m, n);
            break;
        }
    }

    /* part 1 */
    res[0] = (p1 % 2 == 0) ? p1 / 2 : (p1 / 2) + 1;

    /* replace start with appropriate PIPE */
    ground[start[0]][start[1]] = PIPE_TOP_LEFT;

    /* part 2 */
    for (int i = 0; i < m; i++)
    {
        enum pipe_t prev_corner = PIPE_MAX;
        bool in = false;
        for (int j = 0; j < n; j++)
        {

            if (path[i][j] == false)
            {
                /* not part of path and position is inside loop */
                if (in)
                    res[1]++;
            }
            else
            {
                /* keep track of current position */
                switch (ground[i][j])
                {
                    case PIPE_VERTICAL:
                        in = !in;
                        break;
                    case PIPE_TOP_LEFT:
                    case PIPE_BOT_LEFT:
                        in = !in;
                        prev_corner = ground[i][j];
                        break;
                    case PIPE_TOP_RIGHT:
                        if (prev_corner != PIPE_BOT_LEFT)
                            in = !in;
                        prev_corner = ground[i][j];
                        break;
                    case PIPE_BOT_RIGHT:
                        if (prev_corner != PIPE_TOP_LEFT)
                            in = !in;
                        prev_corner = ground[i][j];
                        break;
                    case PIPE_HORIZONTAL:
                    case PIPE_S:
                    case PIPE_NONE:
                        break;
                }
            }
        }
    }

    printf("D" DAY "P1: %d\n", res[0]);
    printf("D" DAY "P2: %d\n", res[1]);

    return AOC_SUCCESS;
}
