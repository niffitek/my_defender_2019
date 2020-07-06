/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/game.h"

double main_buttons[4][4] = {
    {200, 300, 80, 160},
    {200, 400, 80, 450},
    {200, 500, 80, 160},
    {700, 150, 200, 0}
};

int display_help(int ac, char **av)
{
    char buffer[500];
    int fd = 0;
    int size = 0;

    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        if ((fd = open("help", O_RDONLY)) == -1)
            return (2);
        if ((size = read(fd, buffer, 500)) == -1)
            return (2);
        buffer[size] = '\0';
        write(1, buffer, size);
        return (1);
    }
    else if (ac != 1) {
        write(1, "Retry with -h\n", 14);
        return (2);
    }
    return (0);
}

int game_loop(objects *object)
{
    rebuild_game(object);
    int selected = -1;
    int go = 0;
    while (sfRenderWindow_isOpen(object->window)) {
        if ((go = check_game_over(object)) != -1)
            return (go);
        while (sfRenderWindow_pollEvent(object->window, &object->event)) {
            sfVector2i m_pos = sfMouse_getPositionRenderWindow(object->window);
            int choice = game_events(object, 4, selected);
            if (choice == 22 || choice == 23) return (choice);
            if (choice == 0 || choice == 1 || choice == 2 || choice == 3)
                selected = choice;
            if (choice == -2) {
                deploy_tower(object, m_pos.x, m_pos.y, selected + 1);
                selected = -1;
                choice = -1;
            }
        }
        display_game(object, selected);
    }
    return (0);
}

void how_to_play(objects *object)
{
    int choice = 0;
    double buttons[3][4] = {{20, 0, 100, 700}, {50, 850, 80, 160}, {100, 100,
100, 0}};
    while (sfRenderWindow_isOpen(object->window)) {
        while (sfRenderWindow_pollEvent(object->window, &object->event)) {
            choice = menu_button(object, buttons, 2);
            if (choice == 1)
                return;
        }
        sfRenderWindow_clear(object->window, sfBlack);
        set_text(object, buttons[0], "How to Play:", 0);
        set_text(object, buttons[2], "Defend the Castle of Naboo "
"by\nbuilding Towers on empty "
"places!\nYou gain money for defeat "
"enemys.\nIf your lives reach 0 you "
"loose!\nTower 1 & 2 will just damage "
"your enemys\nwhile 3 & 4 will also "
"slow them.\nTry it out!", 0);
        set_text(object, buttons[1], "Back", 1);
        sfRenderWindow_display(object->window);
    }
}

void display_main_menu(objects *object)
{
    sfRenderWindow_clear(object->window, sfBlack);
    set_text(object, main_buttons[0], "Play", 1);
    set_text(object, main_buttons[1], "How to Play", 1);
    set_text(object, main_buttons[2], "Quit", 1);
    set_text(object, main_buttons[3], "STAR WARS:\nBattle of\nNaboo", 0);
    sfRenderWindow_display(object->window);
}

int main(int ac, char **av)
{
    int error = display_help(ac, av);
    int choice = -1;

    if (error == 2)
        return (84);
    objects object = build_game();
    sfMusic_play(object.musics[0]);
    srand(random_seed());
    while (sfRenderWindow_isOpen(object.window) && !error) {
        while (sfRenderWindow_pollEvent(object.window, &object.event)) {
            choice = menu_button(&object, main_buttons, 4);
            if (choice == 2)
                return (end_game(&object, 0));
            if (choice == 1)
                how_to_play(&object);
            if (choice == 0 && game_loop(&object) == 23)
                return (end_game(&object, 0));
        }
        display_main_menu(&object);
    }
    return (end_game(&object, 0));
}