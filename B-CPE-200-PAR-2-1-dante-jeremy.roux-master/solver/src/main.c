/*
** EPITECH PROJECT, 2021
** solver
** File description:
** solves laby
*/

#include <sys/stat.h>
#include <solver.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <ib.h>

bool init_lab(solver_s *lab, char *buf);

bool open_file(solver_s *lab, char *path)
{
    int fd = open(path, O_RDONLY);
    struct stat stats;
    char *buf = NULL;

    if (fd < 0)
        return (false);
    stat(path, &stats);
    buf = malloc(sizeof(char) * stats.st_size + 1);
    read(fd, buf, stats.st_size);
    if (!init_lab(lab, buf)) {
        free(buf);
        return (false);
    }
    free(buf);
    return (true);
}

bool init_lab(solver_s *lab, char *buf)
{
    for (lab->y = 0; buf[lab->y] != '\n'; lab->y++);
    for (lab->x = 1; buf[lab->x * lab->y + lab->x - 1] != '\0'; lab->x++);
    lab->grid = malloc(sizeof(int *) * lab->x);
    if (lab->grid == NULL)
        return (false);
    for (int x = 0; x < lab->x; x++) {
        lab->grid[x] = malloc(sizeof(int) * lab->y);
        if (lab->grid[x] == NULL)
            return (false);
    }
    for (int x = 0; x < lab->x; x++)
        for (int y = 0; y < lab->y; y++)
            lab->grid[x][y] = (buf[x * lab->y + y + x] == '*');
    return (true);
}

bool find_path(int x, int y, solver_s *lab, int last)
{
    int mem = 0;

    if (x + 1 == lab->x && y + 1 == lab->y)
        return (true);
    if (x < 0 || y < 0 || x >= lab->x || y >= lab->y || lab->grid[x][y] != 1)
        return (false);
    mem = lab->grid[x][y];
    if ((last != 1 && find_path(x, y + 1, lab, 3)) ||\
        (last != 2 && find_path(x + 1, y, lab, 4)) ||\
        (last != 3 && find_path(x, y - 1, lab, 1)) ||\
        (last != 4 && find_path(x - 1, y, lab, 2))) {
        lab->grid[x][y] = 2;
        return (true);
    } else
        lab->grid[x][y] = mem;
    return (false);
}

void print_lab(solver_s *lab)
{
    for (int x = 0, tmp = 0; x < lab->x; x++) {
        for (int y = 0; y < lab->y; y++) {
            tmp = lab->grid[x][y];
            if (tmp == 2)
                printf("o");
            else
                printf((tmp)?("*"):("X"));
        }
        printf("%s", (x != lab->x - 1)?("\n"):(""));
    }
}

int main(int ac, char **av)
{
    solver_s lab;

    if (ac != 2)
        return (84);
    if (!open_file(&lab, av[1]))
        return (84);
    if (lab.grid[0][0] == 0 || lab.grid[lab.x - 1][lab.y - 1] == 0 ||
        !find_path(0, 0, &lab, 0))
        printf("no solution found\n");
    else {
        lab.grid[lab.x - 1][lab.y - 1] = 2;
        print_lab(&lab);
    }
    for (int x = 0; x < lab.x; x++)
        free(lab.grid[x]);
    free(lab.grid);
}