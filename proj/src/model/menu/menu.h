#ifndef MENU_H
#define MENU_H


#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "sprite.h"
#include "spriteLoader.h"
#include "cursor.h"

#define SCREEN_CENTER_X 1280 / 2
#define SCREEN_STARTING_Y 50 // This is the Y position of the title, not the center of the screen

#define TITLE_WIDTH 406


#define TITLE_X_POSITION (SCREEN_CENTER_X - TITLE_WIDTH / 2)
#define TITLE_Y_POSITION SCREEN_STARTING_Y + 45

#define BUTTONS_WIDTH 356

#define BUTTONS_X_POSITION (SCREEN_CENTER_X - BUTTONS_WIDTH / 2)

#define SINGLE_MODE_BUTTON_Y_POSITION (SCREEN_STARTING_Y + 350)
#define MULTI_MODE_BUTTON_Y_POSITION (SCREEN_STARTING_Y + 500)
#define EXIT_BUTTON_Y_POSITION (SCREEN_STARTING_Y + 650)


#define CURSOR_BUTTON_X_POSITION (SCREEN_CENTER_X - 240 / 2)

#define CURSOR_BUTTON_TOP_SINGLE_Y_POSITION (SCREEN_STARTING_Y + 400)
#define CURSOR_BUTTON_TOP_MULTI_Y_POSITION (SCREEN_STARTING_Y + 500)
#define CURSOR_BUTTON_TOP_EXIT_Y_POSITION (SCREEN_STARTING_Y + 700)

#define 

struct menu_imp;
typedef struct menu_imp Menu;

/**
 * @brief Creates a menu object.
 * 
 * @param loader Pointer to the SpriteLoader object used to load sprites.
 * @return Pointer to the created Menu object, or NULL on failure.
 */
Menu* create_menu(SpriteLoader *loader);

/** 
  * @brief Destroys a menu object and frees its resources.
  * 
  * @param m Pointer to the Menu object to be destroyed.
  */
void destroy_menu(Menu *m);

/**
 * @brief Draws the menu on the screen.
 * 
 * @param m Pointer to the Menu object to be drawn.
 */
void draw_menu(Menu *m);

/**
 * @brief Processes the input from the cursor and determines the action to take.
 * 
 * @param c Pointer to the Cursor object used for input.
 * @return 0 if no action is taken, 1 if the game should exit, or 2 if single mode is selected.
 */
int process_menu_input(Cursor *c);

#endif

