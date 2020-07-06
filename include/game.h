/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#ifndef MUL_MY_DEFENDER_2019_GAME_H
#define MUL_MY_DEFENDER_2019_GAME_H

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct text_s
{
    sfFont *font;
    sfVector2f pos;
    sfText *text;
    int size;
} ui_text;

typedef struct tile_s
{
    sfVector2f pos;
    int type;
    sfSprite *sprite;
    sfTexture *texture;
} tile;

typedef struct enemy_s
{
    sfVector2f pos;
    sfVector2f move;
    sfVector2f scale;
    sfIntRect anim;
    sfSprite *sprite;
    sfTexture *texture;
    int type;
    double tmptime;
    int max_health;
    int health;
    double speed;
    double og_speed;
    struct enemy_s *next;
} enemys;

typedef struct projectile_s
{
    int type;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f direction;
    enemys *target;
    int damage;
    double slow;
    double speed;
    struct projectile_s *next;
} projectiles;

typedef struct tower_s
{
    int type;
    double range;
    int damage;
    double slow;
    double tmptime;
    double speed;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    int price;
    struct tower_s *next;
} towers;

typedef struct objects_s
{
    sfRenderWindow *window;
    ui_text text;
    sfEvent event;
    sfClock *clock;
    sfTime gametime;
    tile *tiles;
    int tile_count;
    char **map;
    enemys *enemy;
    towers *tower;
    projectiles *projectile;
    double enemy_spawm;
    int money;
    int score;
    int lives;
    int prices[4];
    sfMusic **musics;
    sfSound **sounds;
    sfSoundBuffer **buffer;
} objects;

objects build_game(void);
void build_texts(objects *object);

int game_loop(objects *object);

ui_text create_text(void);
void set_text(objects *object, double const values[], char *str, int isButton);

int menu_button(objects *object, double buttons[][4], int len);
int game_events(objects *object, int len, int selected);

char **map_to_array(char *buffer);
int count_map(char *map);
tile *create_tiles(objects *object);

enemys *instantiate_enemy(char **map);
void enemy_controller(enemys *enemy, sfRenderWindow *window, char **map,
    sfTime gametime);
void get_move(enemys *enemy, char **map);
sfVector2f get_spawn(char **map);
sfVector2f get_spawn_move(sfVector2f spawn, double speed);
void spawn_enemy(objects *object);
int reached_end(char **map, sfVector2f pos);
void pop_enemy(objects *object);
void destroy_enemy(enemys *node, objects *object, int simple);

int random_seed(void);

towers *create_tower(int type, sfVector2f pos, int money, int prices[4]);

void display_sprite(sfRenderWindow *window);
void set_mouse(sfRenderWindow *window, int tower);
void deploy_tower(objects *object, int x, int y, int type);

enemys *get_enemy(enemys *enemy, sfVector2f pos, double range);
void tower_controller(objects *object);
void tower_standard_controller(objects *object);

projectiles *instantiate_projectile(towers *tower, enemys *enemy);
void projectile_controller(objects *object);
void projectile_standard_controller(projectiles *projectile);
void pop_projectile(objects *object);
void destroy_projectile(projectiles *node);

void display_game(objects *object, int selected);
void display_score(objects *object);
char *prep_price_string(char **prices);
int end_game(objects *object, int exitstatus);
void rebuild_game(objects *object);
int check_game_over(objects *object);

void destroy_texts(objects *object);

int my_getnbr(char const *str);
char *my_strcat(char *dest, char const *src);

#endif //MUL_MY_DEFENDER_2019_GAME_H
