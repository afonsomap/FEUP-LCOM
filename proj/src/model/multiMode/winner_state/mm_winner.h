#ifndef MM_WINNER_H
#define MM_WINNER_H

#include <lcom/lcf.h>

#include "spriteLoader.h"
#include "cursor.h"
#include "key_pressed.h"

struct mm_winner_imp;
typedef struct mm_winner_imp MmWinner;

MmWinner *create_mm_winner(SpriteLoader *loader, int winner);
void destroy_mm_winner(MmWinner *mm_winner);
void draw_mm_winner(MmWinner *mm_winner);
int process_mm_winner_mouse(MmWinner *mm_winner, Cursor *c);
int process_mm_winner_kbd(MmWinner *mm_winner, KeyPressed *kp);

#endif // MM_WINNER_H
