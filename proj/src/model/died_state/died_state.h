#ifndef DIED_H
#define DIED_H


#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "sprite.h"
#include "spriteLoader.h"
#include "cursor.h"

struct died_imp;
typedef struct died_imp Died;

/**
 * @brief Creates a new Died object
 * 
 * @param loader Pointer to the SpriteLoader object
 * @return Pointer to the created Died object, or NULL if the creation failed
 */
Died* create_died_page(SpriteLoader *loader);

/**
 * @brief Destroys a Died object, freeing all allocated memory
 * 
 * @param d Pointer to the Died object to be destroyed
 */
void destroy_died(Died *d);

/**
 * @brief Draws the Died screen
 * 
 * @param d Pointer to the Died object to be drawn
 */
void draw_died(Died *d);

/**
 * @brief Processes the input from the cursor in the Died state
 * 
 * @param c Pointer to the Cursor object
 * @return 1 if the game should exit, 0 otherwise
 */
int process_died_input(Cursor *c);

#endif
