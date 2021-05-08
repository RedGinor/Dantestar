/*
** EPITECH PROJECT, 2021
** ib_isnum
** File description:
** returns 1 if the string is a number 0 if not
*/

#include "../ib.h"

bool ib_isnum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return (0);
    return (1);
}