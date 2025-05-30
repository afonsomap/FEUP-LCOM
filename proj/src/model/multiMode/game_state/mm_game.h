#ifndef MM_GAME_H
#define MM_GAME_H

#include <lcom/lcf.h>
#include "spriteLoader.h"
#include "cursor.h"
#include "key_pressed.h"
#include "serial_port.h"
#include "player.h"
#include "bomb.h"
#include "wall.h"
#include "explosion.h"
#include "bomb_options.h"
#include "sprite.h"
#include "animatedSprite.h"

struct mm_game_imp;
typedef struct mm_game_imp MmGame;

#define BIT(n) (1 << (n))

#define GRID_WIDTH 17
#define GRID_HEIGHT 15
#define EXIT_BTN_X_MM 20
#define EXIT_BTN_Y_MM 20
#define BOMB_TYPE_NONE        0x00
#define BOMB_TYPE_NORMAL      0x01
#define BOMB_TYPE_FULL_LINE   0x02
#define BOMB_TYPE_CONSTRUCTIVE 0x03

MmGame *create_mm_game(SpriteLoader *loader, uint8_t player_number);
void destroy_mm_game(MmGame *mm_game);
void draw_mm_game(MmGame *mm_game);
int process_mm_game_mouse(MmGame *mm_game, Cursor *c);
int process_mm_game_kbd(MmGame *mm_game, KeyPressed *kp);
int process_mm_game_timer(MmGame *mm_game);
int process_mm_game_sp(MmGame *mm_game, uint8_t byte);
int get_winner(MmGame *mm_game);

#endif // MM_GAME_H
