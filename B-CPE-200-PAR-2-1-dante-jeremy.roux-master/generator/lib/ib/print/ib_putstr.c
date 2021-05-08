/*
** EPITECH PROJECT, 2020
** ib_putstr
** File description:
** displays the string given as a parameter
*/

#include <unistd.h>
#include "../ib.h"

void ib_putstr(char const *str)
{
    write(1, str, ib_strlen(str));
}