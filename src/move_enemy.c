/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

sfVector2f get_spawn(char **map)
{
    sfVector2f spawn = {0, 0};

    for (int i = 0; map[i]; i += 1)
        for (int j = 0; map[i][j]; j += 1)
            if (map[i][j] == 'S') {
                spawn.x = j * 100 + 1;
                spawn.y = i * 100 + 50;
            }
    spawn.y += rand() % (10) - 5;
    return (spawn);
}

sfVector2f get_spawn_move(sfVector2f spawn, double speed)
{
    sfVector2f move = {0, 0};

    spawn.x = (int) (spawn.x / 100);
    spawn.y = (int) (spawn.y / 100);
    if (spawn.x == 0) {
        move.x = speed;
        return (move);
    } else if (spawn.x == 19) {
        move.x = -speed;
        return (move);
    }
    if (spawn.y == 0)
        move.y = -speed;
    else if (spawn.y == 10)
        move.y = speed;
    return (move);
}

void get_corner_move(char map, enemys *enemy)
{
    if (map == '4' && enemy->move.y < 0.0)
        enemy->move.x = enemy->speed;
    else if (map == '4' && enemy->move.y >= 0.0)
        enemy->move.y = enemy->speed;
    if (map == '5' && enemy->move.x > 0.0)
        enemy->move.y = enemy->speed;
    else if (map == '5' && enemy->move.x <= 0.0)
        enemy->move.x = -enemy->speed;
    if (map == '6' && enemy->move.y > 0.0)
        enemy->move.x = -enemy->speed;
    else if (map == '6' && enemy->move.y <= 0.0)
        enemy->move.y = -enemy->speed;
    if (map == '7' && enemy->move.y > 0.0)
        enemy->move.x = enemy->speed;
    else if (map == '7' && enemy->move.y <= 0.0)
        enemy->move.y = -enemy->speed;
}

void get_move(enemys *enemy, char **map)
{
    int x_pos = (int) (enemy->pos.x / 100);
    int y_pos = (int) (enemy->pos.y / 100);

    if (map[y_pos][x_pos] == 'S')
        return;
    if (map[y_pos][x_pos] == '2')
        enemy->move.y = 0;
    else if (map[y_pos][x_pos] == '3')
        enemy->move.x = 0;
    else
        get_corner_move(map[y_pos][x_pos], enemy);
    if (enemy->move.x > 0)
        enemy->move.x = enemy->speed;
    else if (enemy->move.x < 0)
        enemy->move.x = -enemy->speed;
    if (enemy->move.y > 0)
        enemy->move.y = enemy->speed;
    else if (enemy->move.y < 0)
        enemy->move.y = -enemy->speed;
}

void spawn_enemy(objects *object)
{
    double time = object->gametime.microseconds / 1000000.0;
    enemys *og = object->enemy;

    if (time - object->enemy_spawm > 2) {
        if (og == NULL)
            og = instantiate_enemy(object->map);
        else {
            for (; object->enemy->next != NULL; object->enemy =
                object->enemy->next);
            object->enemy->next = instantiate_enemy(object->map);
        }
        object->enemy_spawm = time;
    }
    for (object->enemy = og; object->enemy != NULL;
    object->enemy = object->enemy->next)
        enemy_controller(object->enemy, object->window,
            object->map, object->gametime);
    object->enemy = og;
}