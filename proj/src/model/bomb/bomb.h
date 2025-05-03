#ifndef __BOMB_H
#define __BOMB_H

#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "animatedSprite.h"

struct bomb_imp;
typedef struct bomb_imp Bomb;


/**
 * @brief Returns the X coordinate of the bomb
 * 
 * @param b Pointer to the
  * @return The X coordinate of the bomb
  */
uint8_t get_bomb_Xpos(Bomb *b);

/**
 * @brief Returns the Y coordinate of the bomb
 * 
 * @param b Pointer to the
 * @return The Y coordinate of the bomb
 */
uint8_t get_bomb_Ypos(Bomb *b);

/**
 * @brief Checks if the bomb has exploded
 *
 * @param b Pointer to the bomb to be checked
 * @return true if the bomb has exploded, false otherwise
 */
bool is_bomb_exploded(Bomb *b);

/**
 * @brief Creates a new bomb with the specified sprite
 *
 * @param x The x-coordinate of the bomb in the game grid
 * @param y The y-coordinate of the bomb in the game grid
 * @param img The sprite for the bomb
 * @return Pointer to the created bomb, or NULL if the pixmap is invalid
 */
Bomb *create_bomb(uint8_t x, uint8_t y, AnimSprite *img);


/**
 * @brief Frees the memory allocated for the bomb
 *
 * @param b Pointer to the bomb to be destroyed
 */
void destroy_bomb(Bomb *b); 

/**
 * @brief Draws the bomb on the screen
 *
 * @param b Pointer to the bomb to be drawn
 * @param x_initial_grid The initial X coordinate of the grid
 * @param y_initial_grid The initial Y coordinate of the grid
 */
void draw_bomb(Bomb *b, uint16_t x_initial_grid, uint16_t y_initial_grid);

#endif /* __BOMB_H */

