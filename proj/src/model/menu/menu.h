#ifndef MENU_H
#define MENU_H


#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "sprite.h"

struct menu_imp;
typedef struct menu_imp Menu;

typedef enum {
  GAME_PLAYING,
  GAME_MENU
} GameState;



extern GameState current_state; // Declare it as an external variable



Menu* create_menu();
void destroy_menu(Menu *m);
void draw_menu(Menu *m);



#endif

