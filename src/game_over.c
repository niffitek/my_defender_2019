/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

int reached_end(char **map, sfVector2f pos)
{
    sfVector2f map_pos = {(int) (pos.x / 100), (int) (pos.y / 100)};

    if (map[(int) map_pos.y][(int) map_pos.x] == 'C')
        return (1);
    return (0);
}

int game_over(objects *object)
{
    double buttons[4][4] = {{400, 200, 200, 0}, {700, 400, 80, 320},
                            {700, 500, 80, 360}, {700, 600, 80, 160}};
    int choice = 0;

    sfMusic_stop(object->musics[1]);
    sfMusic_play(object->musics[0]);
    while (sfRenderWindow_isOpen(object->window)) {
        while (sfRenderWindow_pollEvent(object->window, &object->event)) {
            choice = menu_button(object, buttons, 4);
            if (choice == 1 || choice == 2 || choice == 3)
                return (choice);
        }
        sfRenderWindow_clear(object->window, sfBlack);
        set_text(object, buttons[0], "Game Over", 0);
        set_text(object, buttons[1], "Try again", 1);
        set_text(object, buttons[2], "Main Menu", 1);
        set_text(object, buttons[3], "Quit", 1);
        display_score(object);
        sfRenderWindow_display(object->window);
    }
}

int check_game_over(objects *object)
{
    int choice = -1;

    if (object->lives <= 0) {
        choice = game_over(object);
        if (choice == 1)
            return (game_loop(object));
        if (choice == 2)
            return (0);
        if (choice == 3)
            return (23);
    }
    return (choice);
}