/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    while (str[i] != '\0')
        i++;
    return (i);
}

char *my_strcat(char *dest, char const *src)
{
    int len = my_strlen(dest);
    int i = 0;

    while (src[i] != '\0') {
        dest[len + i] = src[i];
        i += 1;
    }
    dest[len + i] = '\0';
    return (dest);
}

int pre_loop(char const *str, int i)
{
    while (str[i] != '\0' && (str[i] < '0' || str[i] > '9'))
        i++;
    return (i);
}

int my_getnbr(char const *str)
{
    long nb = 0;
    int i = pre_loop(str, 0);
    int begin = i;
    int counter = 2;

    while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9')) {
        nb = nb * 10;
        nb = nb + str[i] - 48;
        if (nb > 2147483647 || nb < -2147483647)
            return (0);
        i++;
    }
    while (begin != 0 && str[begin - 1] == '-') {
        counter++;
        begin--;
    }
    if (counter % 2 == 1)
        nb = nb * -1;
    return (nb);
}

int random_seed(void)
{
    int fd = 0;
    char buffer[5] = "";
    int size = 0;

    if ((fd = open("seed", O_RDONLY)) == -1)
        return (-1);
    if ((size = read(fd, buffer, 500)) == -1)
        return (-1);
    buffer[size] = '\0';
    return (my_getnbr(buffer));
}