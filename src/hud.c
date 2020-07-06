/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

void display_sprite(sfRenderWindow *window)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture **hud = malloc(sizeof(sfTexture *) * 5);
    //hud[0] = sfTexture_createFromFile("assets/hud.png", NULL);
    hud[1] = sfTexture_createFromFile("assets/tower_1.png", NULL);
    hud[2] = sfTexture_createFromFile("assets/tower_2.png", NULL);
    hud[3] = sfTexture_createFromFile("assets/tower_3.png", NULL);
    hud[4] = sfTexture_createFromFile("assets/tower_4.png", NULL);
    sfVector2f scale = {14.25, 2};
    sfVector2f scale_towers = {2, 2};
    sfVector2f pos[5] = {{0, 930}, {369, 940}, {753, 940}, {1137, 940},
{1521, 940}};
    sfSprite_setScale(sprite, scale);
    for (int i = 1; i < 5; i += 1) {
        sfSprite_setPosition(sprite, pos[i]);
        if (i > 0) sfSprite_setScale(sprite, scale_towers);
        sfSprite_setTexture(sprite, hud[i], sfFalse);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfTexture_destroy(hud[i]);
    }
    sfSprite_destroy(sprite);
    free(hud);
}

void set_mouse(sfRenderWindow *window, int tower)
{
    sfVector2i m_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f pos = {m_pos.x + 10, m_pos.y + 10};
    sfVector2f scale = {0.8, 0.8};
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = NULL;

    if (tower == 1)
        texture = sfTexture_createFromFile("assets/tower_1.png", NULL);
    if (tower == 2)
        texture = sfTexture_createFromFile("assets/tower_2.png", NULL);
    if (tower == 3)
        texture = sfTexture_createFromFile("assets/tower_3.png", NULL);
    if (tower == 4)
        texture = sfTexture_createFromFile("assets/tower_4.png", NULL);
    sfSprite_setTexture(sprite, texture, sfFalse);
    sfSprite_setScale(sprite, scale);
    sfSprite_setPosition(sprite, pos);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
}

void deploy_tower(objects *object, int x, int y, int type)
{
    x = ((int) (x / 100)) * 100;
    y = ((int) (y / 100)) * 100;
    towers *og = object->tower;
    sfVector2f pos = {(x + 40), (y + 50)};
    if (og == NULL) {
        og = create_tower(type, pos, object->money, object->prices);
        if (og != NULL)
            object->money -= og->price;
    }
    else {
        for (object->tower = og; object->tower->next != NULL;
object->tower = object->tower->next);
        object->tower->next = create_tower(type, pos, object->money, object
        ->prices);
        if (object->tower->next != NULL) {
            object->money -= object->tower->next->price;
        }
    }
    object->tower = og;
}

char *prep_price_string(char **prices)
{
    char *str = NULL;

    if ((str = malloc(sizeof(char) * 47)) == NULL)
        return (NULL);
    str[0] = '\0';
    str = my_strcat(str, prices[0]);
    str = my_strcat(str, "          ");
    str = my_strcat(str, prices[1]);
    str = my_strcat(str, "          ");
    str = my_strcat(str, prices[2]);
    str = my_strcat(str, "          ");
    str = my_strcat(str, prices[3]);
    str[46] = '\0';
    return (str);
}
