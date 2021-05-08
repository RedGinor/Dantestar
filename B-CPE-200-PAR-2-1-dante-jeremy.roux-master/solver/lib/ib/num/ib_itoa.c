/*
** EPITECH PROJECT, 2020
** ib_itoa
** File description:
** transforms an int into a char *
*/

#include <stdlib.h>
#include "../ib.h"

char *ib_itoa(int num)
{
    char *result = NULL;
    int size = 0;
    int negative = 0;
    int i = 0;

    if (num < 0) {
        num *= -1;
        negative = 1;
    }
    for (int tmp = num; tmp > 0; tmp /= 10)
        size++;
    result = malloc(sizeof(char) * (size + 1 + negative));
    for (; num > 0; num /= 10, i++)
        result[i] = num % 10 + '0';
    if (negative == 1)
        result[i] = '-';
    result = ib_revstr(result);
    return (result);
}