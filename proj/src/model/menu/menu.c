#include "menu.h"

struct menu_imp {
  Sprite *background;     // Background image of the menu
  Sprite *menu_title;   // Title image of the menu
  Sprite *single_mode_button;  // "Single mode" button sprite
  Sprite *multi_mode_button;   // "Multiplayer mode" button sprite
  Sprite *exit_button;    // "Exit" button sprite
};


Menu* create_menu(SpriteLoader *loader) {
  Menu *m = (Menu *) malloc(sizeof(Menu));
  if (m == NULL) {
    return NULL;
  }

  m->background = get_menu_background(loader);
  m->menu_title = get_menu_title(loader);
  m->single_mode_button = get_single_mode_button(loader);
  m->multi_mode_button = get_multi_mode_button(loader);
  m->exit_button = get_exit_button(loader);

  if (m->background == NULL || m->single_mode_button == NULL || m->exit_button == NULL) {
    destroy_menu(m);
    return NULL;
  }

  return m;
}

void destroy_menu(Menu *m) {
  if (m == NULL) {
    return;
  }

  free(m);
}

void draw_menu(Menu *m) {
  if (m == NULL) {
    return;
  }

  draw_sprite(m->background, 0, 0);

  draw_sprite(m->menu_title, TITLE_X_POSITION, TITLE_Y_POSITION);

  draw_sprite(m->single_mode_button, BUTTONS_X_POSITION, SINGLE_MODE_BUTTON_Y_POSITION); 
  draw_sprite(m->multi_mode_button, BUTTONS_X_POSITION, MULTI_MODE_BUTTON_Y_POSITION); 
  draw_sprite(m->exit_button, BUTTONS_X_POSITION, EXIT_BUTTON_Y_POSITION);   
}


// 0 NO ACTION
// 1 Leave game  
// 2 Single mode game
int process_menu_input(Cursor *cursor) {
  if (get_cursor_button_pressed(cursor, 0)) { // Left mouse button pressed
    uint16_t cursor_x = get_cursor_Xpos(cursor);
    uint16_t cursor_y = get_cursor_Ypos(cursor);

    // Check if the cursor is over the "Single Mode" button
    if (cursor_x >= SCREEN_CENTER_X - 240 / 2 && cursor_x <= SCREEN_CENTER_X + 210 / 2 &&
        cursor_y >= SCREEN_STARTING_Y + 400 && cursor_y <= SCREEN_STARTING_Y + 400 + 90) {
      return 2; // Goes to single mode
    }

    // Check if the cursor is over the "Exit" button
    if (cursor_x >= SCREEN_CENTER_X - 240 / 2 && cursor_x <= SCREEN_CENTER_X + 210 / 2 &&
        cursor_y >= SCREEN_STARTING_Y + 700 && cursor_y <= SCREEN_STARTING_Y + 700 + 90) {
      return 1; // Exit the game
    }
  }

  return 0; // Continue the game
}
