/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

void destroy_projectile(projectiles *node)
{
    sfSprite_destroy(node->sprite);
    sfTexture_destroy(node->texture);
    free(node);
}

void destroy_enemy(enemys *node, objects *object, int simple)
{
    if (!simple) {
        if (reached_end(object->map, node->pos))
            object->lives -= node->type;
        if (node->type == 1 && !reached_end(object->map, node->pos)) {
            object->money += 2;
            object->score += 5;
        }
        if (node->type == 2 && !reached_end(object->map, node->pos)) {
            object->money += 5;
            object->score += 10;
        }
    }
    sfSprite_destroy(node->sprite);
    sfTexture_destroy(node->texture);
    node = NULL;
    free(node);
}

void destroy_tower(towers *node)
{
    sfSprite_destroy(node->sprite);
    sfTexture_destroy(node->texture);
    free(node);
}

int end_game(objects *object, int exitstatus)
{
    projectiles *tmp_p = NULL;
    destroy_texts(object);
    free(object->tiles);
    for (int i = 0; object->map[i]; i += 1)
        free(object->map[i]);
    free(object->map);
    if (object->enemy != NULL)
        for (enemys *tmp_e = NULL; (tmp_e = object->enemy) != NULL; object
        ->enemy = object->enemy->next, destroy_enemy(tmp_e, object, 1));
    if (object->tower != NULL)
        for (towers *tmp_t = NULL; (tmp_t = object->tower) != NULL; object
        ->tower = object->tower->next, destroy_tower(tmp_t));
    if (object->projectile != NULL)
        for (; (tmp_p = object->projectile) != NULL; object->projectile = object
            ->projectile->next, destroy_projectile(tmp_p));
    sfClock_destroy(object->clock);
    sfRenderWindow_destroy(object->window);
    return (exitstatus);
}

void rebuild_game(objects *object)
{
    projectiles *tmp_p = NULL;
    enemys *tmp_e = NULL;
    if (object->enemy != NULL)
        for (; (tmp_e = object->enemy) != NULL; object->enemy = object
            ->enemy->next, destroy_enemy(tmp_e, object, 1));
    if (object->tower != NULL)
        for (towers *tmp_t = NULL; (tmp_t = object->tower) != NULL; object
        ->tower = object->tower->next, destroy_tower(tmp_t));
    if (object->projectile != NULL)
        for (; (tmp_p = object->projectile) != NULL; object->projectile = object
            ->projectile->next, destroy_projectile(tmp_p));
    object->enemy_spawm = 0.0;
    object->enemy = NULL;
    object->tower = NULL;
    object->projectile = NULL;
    object->money = 150;
    object->score = 0;
    object->lives = 25;
    sfMusic_stop(object->musics[0]);
    sfMusic_play(object->musics[1]);
    sfClock_restart(object->clock);
}