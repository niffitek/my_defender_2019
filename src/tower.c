/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

enemys *get_enemy(enemys *enemy, sfVector2f pos, double range)
{
    double diff = 0;

    for (; enemy != NULL; enemy = enemy->next) {
        diff = (enemy->pos.x - pos.x) * (enemy->pos.x -
            pos.x);
        diff += (enemy->pos.y - pos.y) * (enemy->pos.y -
            pos.y);
        if (diff < (range * range)) {
            return (enemy);
        }
    }
    return (NULL);
}

void pop_enemy(objects *object)
{
    enemys *head = object->enemy;
    enemys *pre = NULL;
    enemys *tmp = head;
    if (head != NULL && head->next == NULL && (head->health <= 0 || reached_end
    (object->map, head->pos))) {
        destroy_enemy(head, object, 0);
        object->enemy = NULL;
    } else {
        for (; tmp != NULL; pre = tmp, tmp = tmp->next) {
            if ((tmp->health <= 0 || reached_end(object->map, tmp->pos)) &&
            pre != NULL) {
                pre->next = tmp->next;
                destroy_enemy(tmp, object, 0);
                break;
            }
            if ((tmp->health <= 0 || reached_end(object->map, tmp->pos)) && pre
            == NULL) {
                head = head->next;
                destroy_enemy(tmp, object, 0);
                break;
            }
        }
        object->enemy = head;
    }
}

void pop_projectile(objects *object)
{
    projectiles *head = object->projectile;
    projectiles *pre = NULL;
    if (head != NULL && head->next == NULL && (head->damage == 0 ||
    !head->target)) {
        destroy_projectile(head);
        head = NULL;
    } else {
        for (projectiles *tmp = head; tmp != NULL; pre = tmp, tmp = tmp->next) {
            if ((tmp->damage == 0 || !tmp->target) && pre != NULL) {
                pre->next = tmp->next;
                destroy_projectile(tmp);
                break;
            }
            if ((tmp->damage == 0 || !tmp->target) && pre == NULL) {
                head = head->next;
                destroy_projectile(tmp);
                break;
            }
        }
    }
    object->projectile = head;
}

void projectile_controller(objects *object)
{
    projectiles *head = object->projectile;

    if (head == NULL)
        return;
    else {
        for (; object->projectile != NULL;
        object->projectile = object->projectile->next) {
            projectile_standard_controller(object->projectile);
            object->projectile->pos = sfSprite_getPosition(object
                ->projectile->sprite);
            sfRenderWindow_drawSprite(object->window,
                object->projectile->sprite,
                NULL);
            sfSprite_move(object->projectile->sprite, object
            ->projectile->direction);
        }
        object->projectile = head;
    }
}

void tower_controller(objects *object)
{
    towers *head = object->tower;

    if (head == NULL)
        return;
    else {
        for (; object->tower != NULL; object->tower = object->tower->next) {
            sfRenderWindow_drawSprite(object->window, object->tower->sprite,
                NULL);
            tower_standard_controller(object);
        }
    }
    object->tower = head;
}