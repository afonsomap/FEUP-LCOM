#ifndef _SINGLEMODE_H_
#define _SINGLEMODE_H_
#include <lcom/lcf.h>
#include <stddef.h>
#include "player.h"
#include "bomb.h"
#include "wall.h"
#include "spriteLoader.h"
#include "animatedSprite.h"
#include "sprite.h"


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
 */
void process_input(SingleMode *sm, bool* keys);

#endif /* _SINGLEMODE_H_ */

