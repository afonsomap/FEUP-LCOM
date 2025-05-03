#ifndef __CURSOR_H
#define __CURSOR_H

#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "animatedSprite.h"

struct cursor_imp;
typedef struct cursor_imp Cursor;

/**
 * @brief Returns the X coordinate of the cursor
 *
 * @param c Pointer to the cursor
 * @return The X coordinate of the cursor
 */
uint8_t get_cursor_Xpos(Cursor *c);
/**
 * @brief Returns the Y coordinate of the cursor
 *
 * @param c Pointer to the cursor
 * @return The Y coordinate of the cursor
 */
uint8_t get_cursor_Ypos(Cursor *c);
/**
 * @brief Creates a new cursor with the specified sprite
 *
 * @param x The x-coordinate of the cursor in the game grid
 * @param y The y-coordinate of the cursor in the game grid
 * @param img The sprite for the cursor
 * @return Pointer to the created cursor, or NULL if the pixmap is invalid
 */
Cursor *create_cursor(uint8_t x, uint8_t y, AnimSprite *img);
/**
 * @brief Frees the memory allocated for the cursor
 *
 * @param c Pointer to the cursor to be destroyed
 */
void destroy_cursor(Cursor *c);
/**
 * @brief Draws the cursor on the screen
 *
 * @param c Pointer to the cursor to be drawn
 * @param x_initial_grid The initial X coordinate of the grid
 * @param y_initial_grid The initial Y coordinate of the grid
 */
void draw_cursor(Cursor *c, uint8_t x_initial_grid, uint8_t y_initial_grid);

/**
 * @brief Updates the cursor position based on mouse input
 *
 * @param cursor Pointer to the cursor to be updated
 * @param mouse_packet Pointer to the mouse packet containing the movement data
 */
void update_cursor_with_mouse(Cursor *cursor, struct packet *mouse_packet);


 #endif
 
