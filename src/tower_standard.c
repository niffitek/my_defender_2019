/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

void projectile_standard_controller(projectiles *projectile)
{
    if (projectile->target != NULL) {
        projectile->direction.x = (projectile->target->pos.x -
            projectile->pos.x) * projectile->speed;
        projectile->direction.y = (projectile->target->pos.y -
            projectile->pos.y) * projectile->speed;
        if (projectile->pos.x < projectile->target->pos.x + 20
            && projectile->pos.x > projectile->target->pos.x - 20 &&
            projectile->pos.y < projectile->target->pos.y + 20 &&
            projectile->pos.y > projectile->target->pos.y - 20) {
            projectile->target->health -= projectile->damage;
            projectile->target->speed -= projectile->slow;
            projectile->damage = 0;
        }
        if (projectile->target->speed <= 0)
            projectile->target->speed = 0.1;
    } else
        projectile->damage = 0;
}

void play_sound(objects *object)
{
    if (object->tower->type == 1) {
        sfMusic_stop(object->musics[3]);
        sfMusic_play(object->musics[3]);
    }
    else if (object->tower->type == 2) {
        sfMusic_stop(object->musics[2]);
        sfMusic_play(object->musics[2]);
    } else {
        sfMusic_stop(object->musics[4]);
        sfMusic_play(object->musics[4]);
    }
}

void tower_standard_controller(objects *object)
{
    double time = object->gametime.microseconds / 1000000.0;
    enemys *enemy = get_enemy(object->enemy, object->tower->pos,
        object->tower->range);
    projectiles *head = object->projectile;
    if (enemy != NULL && time - object->tower->tmptime > object->tower->speed) {
        play_sound(object);
        if (head == NULL)
            object->projectile = instantiate_projectile(object->tower, enemy);
        else {
            for (;object->projectile->next != NULL; object->projectile = object
                ->projectile->next);
            object->projectile->next = instantiate_projectile(object->tower,
                enemy);
        }
        object->tower->tmptime = time;
    }
    if (head != NULL)
        object->projectile = head;
}