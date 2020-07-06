/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

int check_button(objects *object, double buttons[][4], int len)
{
    sfVector2i m_pos = sfMouse_getPositionRenderWindow(object->window);

    for (int i = 0; i < len; i += 1) {
        if ((m_pos.x >= buttons[i][0] && m_pos.x <=
        buttons[i][0] + buttons[i][3]) && (m_pos.y >=
        buttons[i][1] && m_pos.y <= buttons[i][1] + buttons[i][2])) {
            return (i);
        }
    }
    return (-1);
}

int menu_button(objects *object, double buttons[][4], int len)
{
    if (object->event.type == sfEvtClosed)
        sfRenderWindow_close(object->window);
    if (object->event.type == sfEvtMouseButtonReleased) {
        if (object->event.mouseButton.button == sfMouseLeft)
            return (check_button(object, buttons, len));
    }
    return (-1);
}

int pause_menu(objects *object, double buttons[][4], int len)
{
    int choice = 0;
    sfMusic_stop(object->musics[1]);
    sfMusic_play(object->musics[0]);
    while (sfRenderWindow_isOpen(object->window)) {
        while (sfRenderWindow_pollEvent(object->window, &object->event)) {
            choice = menu_button(object, buttons, len) + 20;
            if (choice == 21) {
                sfMusic_stop(object->musics[0]);
                sfMusic_play(object->musics[1]);
            }
            if (choice != 19)
                return (choice);
        }
        sfRenderWindow_clear(object->window, sfBlack);
        set_text(object, buttons[0], "Game Paused", 0);
        set_text(object, buttons[1], "Continue", 1);
        set_text(object, buttons[2], "Main Menu", 1);
        set_text(object, buttons[3], "Quit", 1);
        sfRenderWindow_display(object->window);
    }
    return (0);
}

int check_tower(objects *object, double buttons[][4], int len, int selected)
{
    sfVector2i m_pos = sfMouse_getPositionRenderWindow(object->window);
    sfVector2i map_pos = {(int) (m_pos.x / 100), (int) (m_pos.y / 100)};
    if (selected == -1)
        return (check_button(object, buttons, len));
    else if (object->map[map_pos.y][map_pos.x] == '8')
        return (-2);
    else
        return (selected);
}

int game_events(objects *object, int len, int selected)
{
    double pause_buttons[4][4] = {{400, 200, 200, 0}, {700, 400, 80,
320}, {700, 500, 80, 360}, {700, 600, 80, 160}};
    double buttons[4][4] = {{369, 940, 66, 80}, {753, 940, 66, 88},
                            {1137, 940, 66, 80}, {1521, 940, 66, 80}};

    if (object->event.type == sfEvtClosed)
        sfRenderWindow_close(object->window);
    if (object->event.type == sfEvtMouseButtonReleased) {
        if (object->event.mouseButton.button == sfMouseLeft)
            return (check_tower(object, buttons, len, selected));
    }
    if (object->event.type == sfEvtKeyPressed)
        if (object->event.key.code == sfKeyP || object->event.key.code ==
        sfKeyEscape)
            return (pause_menu(object, pause_buttons, 4));
    return (-1);
}