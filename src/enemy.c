/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

void instantiate_enemy_type(enemys *new)
{
    new->speed = 1.5;
    new->og_speed = 1.5;
    new->type = rand() % 2 + 1;
    if (new->type == 1)
        new->texture = sfTexture_createFromFile("assets/enemy_1.png", NULL);
    if (new->type == 2) {
        new->speed = 0.5;
        new->og_speed = 0.5;
        new->anim.width = 55;
        new->anim.height = 56;
        new->scale.x = 30;
        new->scale.y = 28;
        new->max_health = 50;
        new->health = new->max_health;
        new->texture = sfTexture_createFromFile("assets/enemy_2.png", NULL);
    }
    sfSprite_setTexture(new->sprite, new->texture, sfFalse);
    new->move = get_spawn_move(new->pos, new->speed);
}

enemys *instantiate_enemy(char **map)
{
    enemys *new = malloc(sizeof(enemys));
    new->sprite = sfSprite_create();
    new->anim.top = 0;
    new->anim.left = 0;
    new->anim.width = 36;
    new->anim.height = 53;
    new->pos = get_spawn(map);
    new->scale.x = 18;
    new->scale.y = 22;
    new->tmptime = 0.0;
    new->max_health = 10;
    new->health = new->max_health;
    new->next = NULL;
    instantiate_enemy_type(new);
    sfSprite_setOrigin(new->sprite, new->scale);
    sfSprite_setTextureRect(new->sprite, new->anim);
    sfSprite_setPosition(new->sprite, new->pos);
    return (new);
}

void animate_enemy(enemys *enemy)
{
    enemy->scale.y = 0.8;
    if (enemy->move.x >= 0) {
        enemy->scale.x = -0.8;
    } else
        enemy->scale.x = 0.8;
    if (enemy->type == 1) {
        if (enemy->anim.left < 320)
            enemy->anim.left += 40;
        else
            enemy->anim.left = 0;
    }
    else if (enemy->type == 2) {
        if (enemy->anim.left < 406)
            enemy->anim.left += 58;
        else
            enemy->anim.left = 0;
    }
    sfSprite_setTextureRect(enemy->sprite, enemy->anim);
    sfSprite_setScale(enemy->sprite, enemy->scale);
    sfSprite_setPosition(enemy->sprite, enemy->pos);
}

void show_lifebar(sfRenderWindow *window, int health, sfVector2f pos_e)
{
    sfVector2f scale = {health, 3};
    sfVector2f pos = {pos_e.x - 18, pos_e.y + 30};
    sfSprite *lifebar = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile("assets/lifebar.png", NULL);

    sfSprite_setScale(lifebar, scale);
    sfSprite_setPosition(lifebar, pos);
    sfSprite_setTexture(lifebar, texture, sfFalse);
    sfRenderWindow_drawSprite(window, lifebar, NULL);
    sfSprite_destroy(lifebar);
    sfTexture_destroy(texture);
}

void enemy_controller(enemys *enemy, sfRenderWindow *window, char **map,
    sfTime gametime)
{
    double seconds = gametime.microseconds / 1000000.0;
    sfVector2i cur_pos = {(int) (enemy->pos.x / 100), (int) (enemy->pos.y /
100)};

    enemy->pos = sfSprite_getPosition(enemy->sprite);
    if (enemy->health > 0) {
        if (seconds - enemy->tmptime > 0.15) {
            animate_enemy(enemy);
            enemy->tmptime = seconds;
        }
        show_lifebar(window, enemy->health, enemy->pos);
        sfRenderWindow_drawSprite(window, enemy->sprite, NULL);
        sfSprite_move(enemy->sprite, enemy->move);
        get_move(enemy, map);
    }
}