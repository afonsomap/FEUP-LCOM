#ifndef SCORE_H
#define SCORE_H

#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "sprite.h"
#include "spriteLoader.h"

struct score_imp;
typedef struct score_imp Score;

/**
 * @brief Creates a new Score object
 * 
 * @param x The x-coordinate of the score
 * @param y The y-coordinate of the score
 * @return Pointer to the created Score object, or NULL if the creation failed
 */

Score *create_score(uint16_t x, uint16_t y, SpriteLoader *loader);

void destroy_score(Score *score);

int increment_score(Score *score);

int decrease_score_rate(Score *score);

uint8_t get_score_value(Score *score);

void draw_score(Score *score);

uint16_t get_score_Xposition(Score *score);

uint16_t get_score_Yposition(Score *score);

uint8_t get_score_rate(Score *score);

void draw_score_at(Score *score, uint16_t x, uint16_t y);

#endif // SCORE_H

