/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

projectiles *projectile_create_1(projectiles *new, towers *tower, enemys *enemy)
{
    if ((new = malloc(sizeof(projectiles))) == NULL)
        return (NULL);
    new->type = 1;
    new->sprite = sfSprite_create();
    new->texture = sfTexture_createFromFile("assets/projectile_1.png", NULL);
    new->pos = sfSprite_getPosition(tower->sprite);
    new->pos.y -= 50;
    new->speed = 0.1;
    new->damage = tower->damage;
    new->slow = tower->slow;
    new->target = enemy;
    new->next = NULL;
    sfVector2f scale = {1.5, 1.5};

    sfSprite_setPosition(new->sprite, new->pos);
    sfSprite_setTexture(new->sprite, new->texture, sfFalse);
    sfSprite_setScale(new->sprite, scale);
    return (new);
}

projectiles *projectile_create_2(projectiles *new, towers *tower, enemys *enemy)
{
    if ((new = malloc(sizeof(projectiles))) == NULL)
        return (NULL);
    new->type = 2;
    new->sprite = sfSprite_create();
    new->texture = sfTexture_createFromFile("assets/projectile_2.png", NULL);
    new->pos = sfSprite_getPosition(tower->sprite);
    new->pos.y -= 50;
    new->speed = 0.2;
    new->slow = tower->slow;
    new->damage = tower->damage;
    new->target = enemy;
    new->next = NULL;
    sfVector2f scale = {1.5, 1.5};

    sfSprite_setPosition(new->sprite, new->pos);
    sfSprite_setTexture(new->sprite, new->texture, sfFalse);
    sfSprite_setScale(new->sprite, scale);
    return (new);
}

projectiles *projectile_create_3(projectiles *new, towers *tower, enemys *enemy)
{
    if ((new = malloc(sizeof(projectiles))) == NULL)
        return (NULL);
    new->type = 3;
    new->sprite = sfSprite_create();
    new->texture = sfTexture_createFromFile("assets/projectile_3.png", NULL);
    new->pos = sfSprite_getPosition(tower->sprite);
    new->pos.y -= 50;
    new->speed = 0.1;
    new->slow = tower->slow;
    new->damage = tower->damage;
    new->target = enemy;
    new->next = NULL;
    sfVector2f scale = {1.5, 1.5};

    sfSprite_setPosition(new->sprite, new->pos);
    sfSprite_setTexture(new->sprite, new->texture, sfFalse);
    sfSprite_setScale(new->sprite, scale);
    return (new);
}

projectiles *projectile_create_4(projectiles *new, towers *tower, enemys *enemy)
{
    if ((new = malloc(sizeof(projectiles))) == NULL)
        return (NULL);
    new->type = 4;
    new->sprite = sfSprite_create();
    new->texture = sfTexture_createFromFile("assets/projectile_4.png", NULL);
    new->pos = sfSprite_getPosition(tower->sprite);
    new->pos.y -= 50;
    new->speed = 0.2;
    new->slow = tower->slow;
    new->damage = tower->damage;
    new->target = enemy;
    new->next = NULL;
    sfVector2f scale = {0.8, 0.8};
    sfSprite_setPosition(new->sprite, new->pos);
    sfSprite_setTexture(new->sprite, new->texture, sfFalse);
    sfSprite_setScale(new->sprite, scale);
    return (new);
}

projectiles *instantiate_projectile(towers *tower, enemys *enemy)
{
    projectiles *new = NULL;

    if (tower->type == 1)
        new = projectile_create_1(new, tower, enemy);
    if (tower->type == 2)
        new = projectile_create_2(new, tower, enemy);
    if (tower->type == 3)
        new = projectile_create_3(new, tower, enemy);
    if (tower->type == 4)
        new = projectile_create_4(new, tower, enemy);
    return (new);
}
