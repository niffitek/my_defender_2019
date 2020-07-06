/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/


#include "../include/game.h"

void display_money(objects *object)
{
    double money[1][4] = {{5, 5, 70, 0}};
    char *money_text = NULL;

    if ((money_text = malloc(sizeof(char) * 12)) == NULL)
        return;
    if (object->money > 999)
        object->money = 999;
    money_text[0] = 'M';
    money_text[1] = 'O';
    money_text[2] = 'N';
    money_text[3] = 'E';
    money_text[4] = 'Y';
    money_text[5] = ':';
    money_text[6] = ' ';
    money_text[7] = object->money / 100 + 48;
    money_text[8] = object->money / 10 % 10 + 48;
    money_text[9] = object->money % 10 + 48;
    money_text[10] = '$';
    money_text[11] = '\0';
    set_text(object, money[0], money_text, 0);
    free(money_text);
}

void display_score(objects *object)
{
    double money[1][4] = {{5, 50, 70, 0}};
    char *money_text = NULL;

    if ((money_text = malloc(sizeof(char) * 11)) == NULL)
        return;
    if (object->score > 999)
        object->score = 999;
    money_text[0] = 'S';
    money_text[1] = 'C';
    money_text[2] = 'O';
    money_text[3] = 'R';
    money_text[4] = 'E';
    money_text[5] = ':';
    money_text[6] = ' ';
    money_text[7] = object->score / 100 + 48;
    money_text[8] = object->score / 10 % 10 + 48;
    money_text[9] = object->score % 10 + 48;
    money_text[10] = '\0';
    set_text(object, money[0], money_text, 0);
    free(money_text);
}

void display_lives(objects *object)
{
    double money[1][4] = {{5, 95, 70, 0}};
    char *money_text = NULL;

    if ((money_text = malloc(sizeof(char) * 11)) == NULL)
        return;
    if (object->lives > 999)
        object->lives = 999;
    money_text[0] = 'L';
    money_text[1] = 'I';
    money_text[2] = 'V';
    money_text[3] = 'E';
    money_text[4] = 'S';
    money_text[5] = ':';
    money_text[6] = ' ';
    money_text[7] = object->lives / 100 + 48;
    money_text[8] = object->lives / 10 % 10 + 48;
    money_text[9] = object->lives % 10 + 48;
    money_text[10] = '\0';
    set_text(object, money[0], money_text, 0);
    free(money_text);
}

void display_price(objects *object)
{
    double price[1][4] = {{440, 940, 70, 0}};
    char **str = NULL;
    if ((str = malloc(sizeof(char *) * 5)) == NULL)
        return;
    for (int i = 0; i < 4; i += 1) {
        if ((str[i] = malloc(sizeof(char) * 5)) == NULL)
            return;
        str[i][0] = object->prices[i] / 100 + 48;
        str[i][1] = object->prices[i] / 10 % 10 + 48;
        str[i][2] = object->prices[i] % 10 + 48;
        str[i][3] = '$';
        str[i][4] = '\0';
    }
    str[4] = prep_price_string(str);
    set_text(object, price[0], str[4], 0);
    for (int i = 0; i < 3; free(str[i]), i += 1);
    free(str);
}

void display_game(objects *object, int selected)
{
    object->gametime = sfClock_getElapsedTime(object->clock);
    sfRenderWindow_clear(object->window, sfBlack);
    for (int i = 0; i < object->tile_count; i += 1)
        sfRenderWindow_drawSprite(object->window, object->tiles[i].sprite,
            NULL);
    spawn_enemy(object);
    tower_controller(object);
    projectile_controller(object);
    pop_enemy(object);
    pop_projectile(object);
    display_sprite(object->window);
    display_money(object);
    display_score(object);
    display_lives(object);
    display_price(object);
    if (selected != -1)
        set_mouse(object->window, selected + 1);
    sfRenderWindow_display(object->window);
}