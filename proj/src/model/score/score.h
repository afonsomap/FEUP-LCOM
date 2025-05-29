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
Score *create_score(uint16_t x, uint16_t y);

#endif // SCORE_H