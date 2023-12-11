#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aoc.h>

#define DAY "05"

struct map {
    unsigned int dst;
    unsigned int src;
    unsigned int range;
};

static struct map
parse_map(char line[])
{

    struct map m = { 0 };
    int i = 0;
    m.dst = strtoull(&line[i], NULL, 10);

    while (line[i] != ' ' && line[i] != '\n')
        i++;
    while (line[i] == ' ')
        i++;
    m.src = strtoull(&line[i], NULL, 10);

    while (line[i] != ' ' && line[i] != '\n')
        i++;
    while (line[i] == ' ')
        i++;
    m.range = strtoull(&line[i], NULL, 10);

    aoc_debug("dst=%u src=%u range=%u\n", m.dst, m.src, m.range);
    return m;
}

static unsigned int
get_next_category(unsigned int category, struct map m[], int m_cnt)
{
    for (int i = 0; i < m_cnt; i++)
    {
        if (category >= m[i].src && category <= m[i].src + m[i].range)
        {
            return (m[i].dst + category - m[i].src);
        }
    }
    return category;
}

enum aoc_err
day_05()
{
    FILE* fp;
    char line[AOC_STR_LEN];
    unsigned int res[2] = { 0, 0 };

    unsigned int seeds[AOC_ARR_LEN];
    struct map seed_soil[AOC_ARR_LEN];
    struct map soil_fert[AOC_ARR_LEN];
    struct map fert_water[AOC_ARR_LEN];
    struct map water_light[AOC_ARR_LEN];
    struct map light_temp[AOC_ARR_LEN];
    struct map temp_humidity[AOC_ARR_LEN];
    struct map humidity_location[AOC_ARR_LEN];

    int cnt_seeds = 0;
    int cnt_seed_soil = 0;
    int cnt_soil_fert = 0;
    int cnt_fert_water = 0;
    int cnt_water_light = 0;
    int cnt_light_temp = 0;
    int cnt_temp_humidity = 0;
    int cnt_humidity_location = 0;

    fp = fopen(INPUT_F(DAY), "r");

    if (fp == NULL)
        return AOC_INPUT_FILE_NOT_FOUND;

    while (fgets(line, AOC_STR_LEN, fp) != NULL)
    {
        /* seeds */
        if (line[0] == 's' && line[1] == 'e' && line[2] == 'e' &&
            line[3] == 'd' && line[4] == 's')
        {
            int i = 7;
            while (line[i] != '\n')
            {
                seeds[cnt_seeds++] = strtoull(&line[i], NULL, 10);

                while (line[i] != ' ' && line[i] != '\n')
                    i++;
                while (line[i] == ' ')
                    i++;
            }
            aoc_debug("seeds: ");
            for (int i = 0; i < cnt_seeds; i++)
                aoc_debug_s("%u ", seeds[i]);
            aoc_debug_s("\n");
        }
        /* seed-to-soil map */
        else if (line[0] == 's' && line[1] == 'e')
        {
            aoc_debug("seed_soil: \n");
            while (fgets(line, AOC_STR_LEN, fp) != NULL)
            {
                if (line[0] == '\n')
                    break;
                seed_soil[cnt_seed_soil++] = parse_map(line);
            }
        }
        /* soil-to-fertilizer map */
        else if (line[0] == 's' && line[1] == 'o')
        {
            aoc_debug("soil_fert: \n");
            while (fgets(line, AOC_STR_LEN, fp) != NULL)
            {
                if (line[0] == '\n')
                    break;
                soil_fert[cnt_soil_fert++] = parse_map(line);
            }
        }
        /* fertilizer-to-water map */
        else if (line[0] == 'f')
        {
            aoc_debug("fert_water: \n");
            while (fgets(line, AOC_STR_LEN, fp) != NULL)
            {
                if (line[0] == '\n')
                    break;
                fert_water[cnt_fert_water++] = parse_map(line);
            }
        }
        /* water-to-light map */
        else if (line[0] == 'w')
        {
            aoc_debug("water_light: \n");
            while (fgets(line, AOC_STR_LEN, fp) != NULL)
            {
                if (line[0] == '\n')
                    break;
                water_light[cnt_water_light++] = parse_map(line);
            }
        }
        /* light-to-temperature map */
        else if (line[0] == 'l')
        {
            aoc_debug("light_temp: \n");
            while (fgets(line, AOC_STR_LEN, fp) != NULL)
            {
                if (line[0] == '\n')
                    break;
                light_temp[cnt_light_temp++] = parse_map(line);
            }
        }
        /* temperature-to-humidity map */
        else if (line[0] == 't')
        {
            aoc_debug("temp_humidity: \n");
            while (fgets(line, AOC_STR_LEN, fp) != NULL)
            {
                if (line[0] == '\n')
                    break;
                temp_humidity[cnt_temp_humidity++] = parse_map(line);
            }
        }
        /* humidity-to-location map */
        else if (line[0] == 'h')
        {
            aoc_debug("humidity_location: \n");
            while (fgets(line, AOC_STR_LEN, fp) != NULL)
            {
                if (line[0] == '\n')
                    break;
                humidity_location[cnt_humidity_location++] = parse_map(line);
            }
        }
    }

    fclose(fp);

    res[0] = AOC_INT_MAX;
    for (int i = 0; i < cnt_seeds; i++)
    {
        aoc_debug("seed=%u\n", seeds[i]);
        unsigned int tmp =
          get_next_category(seeds[i], seed_soil, cnt_seed_soil);
        aoc_debug("soil=%u\n", tmp);
        tmp = get_next_category(tmp, soil_fert, cnt_soil_fert);
        aoc_debug("fert=%u\n", tmp);
        tmp = get_next_category(tmp, fert_water, cnt_fert_water);
        aoc_debug("water=%u\n", tmp);
        tmp = get_next_category(tmp, water_light, cnt_water_light);
        aoc_debug("light=%u\n", tmp);
        tmp = get_next_category(tmp, light_temp, cnt_light_temp);
        aoc_debug("temp=%u\n", tmp);
        tmp = get_next_category(tmp, temp_humidity, cnt_temp_humidity);
        aoc_debug("humidity=%u\n", tmp);
        tmp = get_next_category(tmp, humidity_location, cnt_humidity_location);
        aoc_debug("location=%u\n", tmp);

        res[0] = AOC_MIN(res[0], tmp);
    }

    res[1] = AOC_INT_MAX;
    for (int i = 0; i < cnt_seeds - 1; i += 2)
    {
        for (int j = 0; j < seeds[i + 1]; j++)
        {

            aoc_debug("seed=%u\n", seeds[i] + j);
            unsigned int tmp =
              get_next_category(seeds[i] + j, seed_soil, cnt_seed_soil);
            aoc_debug("soil=%u\n", tmp);
            tmp = get_next_category(tmp, soil_fert, cnt_soil_fert);
            aoc_debug("fert=%u\n", tmp);
            tmp = get_next_category(tmp, fert_water, cnt_fert_water);
            aoc_debug("water=%u\n", tmp);
            tmp = get_next_category(tmp, water_light, cnt_water_light);
            aoc_debug("light=%u\n", tmp);
            tmp = get_next_category(tmp, light_temp, cnt_light_temp);
            aoc_debug("temp=%u\n", tmp);
            tmp = get_next_category(tmp, temp_humidity, cnt_temp_humidity);
            aoc_debug("humidity=%u\n", tmp);
            tmp =
              get_next_category(tmp, humidity_location, cnt_humidity_location);
            aoc_debug("location=%u\n", tmp);

            res[1] = AOC_MIN(res[1], tmp);
        }
    }

    printf("D" DAY "P1: %u\n", res[0]);
    printf("D" DAY "P2: %u\n", res[1]);

    return AOC_SUCCESS;
}
