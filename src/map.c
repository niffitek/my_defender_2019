/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/


#include "../include/game.h"

int count_rows(char *map)
{
    int counter = 0;

    for (int i = 0; map[i] != '\0'; i += 1)
        if (map[i] == '\n')
            counter += 1;
    return (counter);
}

char **map_to_array(char *buffer)
{
    int rows = count_rows(buffer);
    int col = 0;
    int tmp = 0;
    int i = 0;
    char **map = NULL;

    if ((map = malloc(sizeof(char *) * (rows + 1))) == NULL)
        return (NULL);
    map[rows] = NULL;
    for (int r = 0; r < rows; r += 1, i += 1) {
        tmp = i;
        for (col = 0; buffer[tmp] != '\n' && buffer[tmp] != '\0'; tmp += 1,
            col += 1);
        if ((map[r] = malloc(sizeof(char) * (col + 2))) == NULL)
            return (NULL);
        for (int c = 0; buffer[i] != '\n'; i += 1, c += 1)
            map[r][c] = buffer[i];
        map[r][col] = '\n';
        map[r][col + 1] = '\0';
    }
    return (map);
}

tile create_tile_sprite(tile new)
{
    sfVector2f scale = {5, 5};
    if (new.type == '1')
        new.texture = sfTexture_createFromFile("assets/grass.png", NULL);
    if (new.type == '2' || new.type == 'S' || new.type == 'C')
        new.texture = sfTexture_createFromFile("assets/way1.png", NULL);
    if (new.type == '3')
        new.texture = sfTexture_createFromFile("assets/way1_1.png", NULL);
    if (new.type == '4')
        new.texture = sfTexture_createFromFile("assets/way2.png", NULL);
    if (new.type == '5')
        new.texture = sfTexture_createFromFile("assets/way2_1.png", NULL);
    if (new.type == '6')
        new.texture = sfTexture_createFromFile("assets/way2_2.png", NULL);
    if (new.type == '7')
        new.texture = sfTexture_createFromFile("assets/way2_3.png", NULL);
    if (new.type == '8')
        new.texture = sfTexture_createFromFile("assets/towerplace.png", NULL);
    sfSprite_setTexture(new.sprite, new.texture, sfFalse);
    sfSprite_setScale(new.sprite, scale);
    sfSprite_setPosition(new.sprite, new.pos);
    return (new);
}

tile *create_tiles(objects *object)
{
    int r = 0;
    int c = 0;
    int i = 0;
    tile *tiles;

    if ((tiles = malloc(sizeof(tile) * (object->tile_count + 1))) == NULL)
        return (NULL);
    for (r = 0; object->map[r] != NULL; r += 1) {
        for (c = 0; object->map[r][c] != '\0'; c += 1) {
            if (object->map[r][c] != ' ' && object->map[r][c] != '\n') {
                tiles[i].type = object->map[r][c];
                tiles[i].sprite = sfSprite_create();
                tiles[i].pos.x = c * 100;
                tiles[i].pos.y = r * 100;
                tiles[i] = create_tile_sprite(tiles[i]);
                i += 1;
            }
        }
    }
    return (tiles);
}