/*
** EPITECH PROJECT, 2021
** generator
** File description:
** generates mazes
*/

#include <generator.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ib.h>

bool init_lab(generator_s *lab, char **av)
{
    lab->x = ib_atoi(av[2]);
    lab->y = ib_atoi(av[1]);
    if (lab->x < 1 || lab->y < 1)
        return (false);
    lab->grid = malloc(sizeof(int *) * lab->x);
    if (lab->grid == NULL)
        return (false);
    for (int x = 0; x < lab->x; x++) {
        lab->grid[x] = malloc(sizeof(int) * lab->y);
        if (lab->grid[x] == NULL)
            return (false);
    }
    lab->grid[0][0] = 1;
    lab->grid[lab->x - 1][lab->y - 1] = 1;
    return (true);
}

void print_lab(generator_s *lab)
{
    for (int x = 0; x < lab->x; x++) {
        for (int y = 0; y < lab->y; y++)
            printf((lab->grid[x][y])?("*"):("X"));
        printf("%s", (x != lab->x - 1)?("\n"):(""));
    }
}

void make_clusters(generator_s *lab, bool is_odd)
{
    int clusters = 2;

    for (int x = is_odd; x < lab->x; x += 2)
        for (int i = 0; i < clusters; i++)
            lab->grid[x][rand() % (lab->y / 4) * 2] = 1;
}

void launch_generation(generator_s *lab, bool is_perfect)
{
    bool is_odd = lab->x % 2;
    int randomizer = 3 + rand() % 3 * 2;
    int path = 0;
    int tmp = 0;

    for (int y = 0; y < lab->y; y++)
        lab->grid[!is_odd][y] = 1;
    for (int x = 1 + is_odd; x < lab->x; x += 2)
        for (int y = 0, rdm = 1; y < lab->y; y++, rdm = 1) {
            rdm += rand() % randomizer * 2;
            for (tmp = y; tmp < lab->y && tmp < y + rdm; tmp++)
                lab->grid[x][tmp] = 1;
            path = rand() % (1 + rdm / 2);
            for (; y + path * 2 >= lab->y;)
                path = rand() % (1 + rdm / 2);
            lab->grid[x - 1][y + path * 2] = 1;
            y = tmp;
        }
    if (!is_perfect)
        make_clusters(lab, is_odd);
}

int main(int ac, char **av)
{
    generator_s lab;

    if ((ac != 3 && ac != 4) || !ib_isnum(av[1]) || !ib_isnum(av[2]))
        return (84);
    if (!init_lab(&lab, av) || (ac == 4 && !ib_strcmp(av[3], "perfect")))
        return (84);
    srand(time(NULL));
    if (lab.x < 4 || lab.y < 4) {
        for (int x = 0; x < lab.x; x++)
            for (int y = 0; y < lab.y; y++)
                lab.grid[x][y] = 1;
    } else
        launch_generation(&lab, (ac == 4));
    print_lab(&lab);
    for (int x = 0; x < lab.x; x++)
        free(lab.grid[x]);
    free(lab.grid);
}