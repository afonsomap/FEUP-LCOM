#ifndef MM_GAME_H
#define MM_GAME_H

#include <lcom/lcf.h>
#include "sprite_loader.h"
#include "cursor.h"
#include "key_pressed.h"
#include "serial_port.h"

struct mm_game_imp;
typedef struct mm_game_imp MmGame;

MmGame *create_mm_game(SpriteLoader *loader, uint8_t player_number);
void destroy_mm_game(MmGame *mm_game);
void draw_mm_game(MmGame *mm_game);
int process_mm_game_mouse(MmGame *mm_game, Cursor *c);
int process_mm_game_kbd(MmGame *mm_game, KeyPressed *kp);
int process_mm_game_timer(MmGame *mm_game);
int process_mm_game_sp(MmGame *mm_game, uint8_t byte);
bool is_current_winner(MmGame *mm_game);