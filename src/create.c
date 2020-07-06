/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

int count_map(char *map)
{
    int counter = 0;

    for (int i = 0; map[i] != '\0'; i += 1) {
        if (map[i] != '\n' && map[i] != ' ')
            counter += 1;
    }
    return (counter);
}

sfRenderWindow *create_window(void)
{
    sfRenderWindow *window = NULL;
    sfVideoMode video_mode = {1920, 1080, 32};

    window = sfRenderWindow_create(video_mode, "my_defender", sfDefaultStyle,
    NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    return (window);
}

sfSprite *create_sprite(char *path)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(path, NULL);
    sfSprite_setTexture(sprite, texture, sfFalse);
    return (sprite);
}

objects build_game(void)
{
    int fd = 0;
    char buffer[500];
    int len = 0;

    objects object;
    if ((fd = open("map", O_RDONLY)) == -1)
        return (object);
    if ((len = read(fd, buffer, 500)) == -1)
        return (object);
    buffer[len] = '\0';
    object.window = create_window();
    object.clock = sfClock_create();
    object.map = map_to_array(buffer);
    object.tile_count = count_map(buffer);
    object.tiles = create_tiles(&object);
    object.enemy = NULL;
    object.enemy_spawm = 0.0;
    object.tower = NULL;
    object.projectile = NULL;
    build_texts(&object);
    return (object);
}