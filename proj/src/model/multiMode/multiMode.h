#ifndef _MULTIMODE_H_
#define _MULTIMODE_H_

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
#include "bomb_options.h"
#include "key_pressed.h"

struct multiMode_imp;
typedef struct multiMode_imp MultiMode;

/**
 * @brief Creates a new MultiMode object, which contains multiple players and a grid of walls
 * 
 * @param loader Pointer to the SpriteLoader object
 * @return Pointer to the created MultiMode object, or NULL if the creation failed
 */
MultiMode *create_multiMode(SpriteLoader *loader);

/**
 * @brief Destroys a MultiMode object, freeing all allocated memory
 * 
 * @param mm Pointer to the MultiMode object to be destroyed
 */
void destroy_multiMode(MultiMode *mm);

/**
 * @brief Draws the MultiMode object on the screen, including all players
 * 
 * @param mm Pointer to the MultiMode object to be drawn
 */
void draw_multiMode(MultiMode *mm);

/**
 * @brief Processes the input from the keyboard for multiplayer
 * 
 * @param mm Pointer to the MultiMode object
 * @param key Pointer to the KeyPressed object containing the state of the keys
 * @return 0 if the game should continue, 1 to go back to the menu
 */
int process_multi_mode_kbd(MultiMode *mm, KeyPressed *key);

/**
 * @brief Processes the input from the mouse for multiplayer
 * 
 * @param mm Pointer to the MultiMode object
 * @param c Pointer to the Cursor object
 * @return 0 if the game should continue, 1 to go back to the menu
 */
int process_multi_mode_mouse(MultiMode *mm, Cursor *c);

/**
 * @brief Checks if any bomb has exploded and if any player is in the same position, destroys wall if it is destroyable
 * 
 * @param mm Pointer to the MultiMode object
 * @return 0 if the game should continue, 1 to go back to the menu
 */
int check_bomb_exploded_multi(MultiMode *mm);

int process_bomb_spawning_multi(MultiMode *mm);

#endif /* _MULTIMODE_H_ */
