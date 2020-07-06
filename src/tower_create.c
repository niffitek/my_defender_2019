/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

towers *tower_create_1(towers *new, sfVector2f pos, int price)
{
    if ((new = malloc(sizeof(towers))) == NULL)
        return (NULL);
    new->type = 1;
    new->range = 200;
    new->damage = 100;
    new->slow = 0;
    new->sprite = sfSprite_create();
    new->texture = sfTexture_createFromFile("assets/tower_1.png", NULL);
    new->pos = pos;
    new->next = NULL;
    new->price = price;
    new->tmptime = 5;
    new->speed = 5;
    sfVector2f scale = {3, 3};
    sfVector2f origin = {13, 33};

    sfSprite_setOrigin(new->sprite, origin);
    sfSprite_setScale(new->sprite, scale);
    sfSprite_setTexture(new->sprite, new->texture, sfFalse);
    sfSprite_setPosition(new->sprite, pos);
    return (new);
}

towers *tower_create_2(towers *new, sfVector2f pos, int price)
{
    if ((new = malloc(sizeof(towers))) == NULL)
        return (NULL);
    new->type = 2;
    new->range = 150;
    new->damage = 10;
    new->slow = 0;
    new->price = price;
    new->sprite = sfSprite_create();
    new->texture = sfTexture_createFromFile("assets/tower_2.png", NULL);
    new->pos = pos;
    new->next = NULL;
    new->tmptime = 2;
    new->speed = 2;
    sfVector2f scale = {3, 3};
    sfVector2f origin = {13, 33};

    sfSprite_setPosition(new->sprite, pos);
    sfSprite_setTexture(new->sprite, new->texture, sfFalse);
    sfSprite_setOrigin(new->sprite, origin);
    sfSprite_setScale(new->sprite, scale);
    return (new);
}

towers *tower_create_3(towers *new, sfVector2f pos, int price)
{
    if ((new = malloc(sizeof(towers))) == NULL)
        return (NULL);
    new->type = 3;
    new->range = 150;
    new->damage = 1;
    new->slow = 1.5;
    new->speed = 3;
    new->price = price;
    new->sprite = sfSprite_create();
    new->texture = sfTexture_createFromFile("assets/tower_3.png", NULL);
    new->pos = pos;
    new->tmptime = 3;
    new->next = NULL;
    sfVector2f scale = {3, 3};
    sfVector2f origin = {13, 33};

    sfSprite_setOrigin(new->sprite, origin);
    sfSprite_setTexture(new->sprite, new->texture, sfFalse);
    sfSprite_setScale(new->sprite, scale);
    sfSprite_setPosition(new->sprite, pos);
    return (new);
}

towers *tower_create_4(towers *new, sfVector2f pos, int price)
{
    if ((new = malloc(sizeof(towers))) == NULL)
        return (NULL);
    new->type = 4;
    new->range = 200;
    new->damage = 1;
    new->slow = 0.1;
    new->speed = 0.5;
    new->price = price;
    new->sprite = sfSprite_create();
    new->texture = sfTexture_createFromFile("assets/tower_4.png", NULL);
    new->pos = pos;
    new->tmptime = 0.5;
    new->next = NULL;
    sfVector2f scale = {3, 3};
    sfVector2f origin = {13, 33};

    sfSprite_setPosition(new->sprite, pos);
    sfSprite_setOrigin(new->sprite, origin);
    sfSprite_setTexture(new->sprite, new->texture, sfFalse);
    sfSprite_setScale(new->sprite, scale);
    return (new);
}

towers *create_tower(int type, sfVector2f pos, int money, int prices[4])
{
    towers *new = NULL;

    if (type == 1 && money >= prices[0])
        new = tower_create_1(new, pos, prices[0]);
    if (type == 2 && money >= prices[1])
        new = tower_create_2(new, pos, prices[1]);
    if (type == 3 && money >= prices[2])
        new = tower_create_3(new, pos, prices[2]);
    if (type == 4 && money >= prices[3])
        new = tower_create_4(new, pos, prices[3]);
    return (new);
}