#ifndef _SINGLEMODE_H_
#define _SINGLEMODE_H_
#include <lcom/lcf.h>
#include <stddef.h>
#include <math.h>
#include "player.h"
#include "bomb.h"
#include "wall.h"
#include "spriteLoader.h"
#include "animatedSprite.h"
#include "sprite.h"
#include "cursor.h"
#include "explosion.h"
#include "menu.h"


struct singleMode_imp;
typedef struct singleMode_imp SingleMode;

/**
 * @brief Creates a new SingleMode object, which contains a player and a grid of walls
 * 
 * @param loader Pointer to the SpriteLoader object
 * @return Pointer to the created SingleMode object, or NULL if the creation failed
 */
SingleMode *create_singleMode(SpriteLoader *loader);

/**
 * @brief Destroys a SingleMode object, freeing all allocated memory
 * 
 * @param sm Pointer to the SingleMode object to be destroyed
 */
void destroy_singleMode(SingleMode *sm);

/**
 * @brief Draws the SingleMode object on the screen
 * 
 * @param sm Pointer to the SingleMode object to be drawn
 */
void draw_singleMode(SingleMode *sm);

/**
 * @brief Processes the input from the keyboard
 * 
 * @param sm Pointer to the SingleMode object
 * @param keys Array of boolean values representing the state of the keys
 * @return 0 if the game should continue, 1 go back to the menu
 */
int process_single_mode_kbd(SingleMode *sm, bool* keys);

/**
 * @brief Processes the input from the mouse
 * 
 * @param sm Pointer to the SingleMode object
 * @param c Pointer to the Cursor object
 * @return 0 if the game should continue, 1 go back to the menu
 */
int process_single_mode_mouse(SingleMode *sm, Cursor *c);

/**
 * @brief Checks if the bomb has exploded and if the player is in the same position, destroys wall if it is destroyable
 * 
 * @param sm Pointer to the SingleMode object
 * @return 0 if the game should continue, 1 go back to the menu
 */
int check_bomb_exploded(SingleMode *sm);

#endif /* _SINGLEMODE_H_ */

