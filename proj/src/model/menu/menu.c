#include "menu.h"

struct menu_imp {
  Sprite *background;     // Background image of the menu
  Sprite *menu_title;   // Title image of the menu
  Sprite *single_mode_button;  // "Single mode" button sprite
  Sprite *multi_mode_button;   // "Multiplayer mode" button sprite
  Sprite *exit_button;    // "Exit" button sprite
};

uint16_t center_x = 1280 / 2;
uint16_t center_y = 50; 

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
  draw_sprite(m->menu_title, center_x - 406 / 2, center_y + 50); // Draw the title at (100, 50)

  draw_sprite(m->single_mode_button, center_x - 356 / 2, center_y + 300); // Draw the "Single Mode" button below the title
  draw_sprite(m->multi_mode_button, center_x - 356 / 2, center_y + 450); // Draw the "Multiplayer Mode" button below the title
  draw_sprite(m->exit_button, center_x - 356 / 2, center_y + 600);   
}


// 0 NO ACTION
// 1 Leave game  
// 2 Single mode game
int process_menu_input(Cursor *cursor) {
  if (get_cursor_button_pressed(cursor, 0)) { // Left mouse button pressed
    uint16_t cursor_x = get_cursor_Xpos(cursor);
    uint16_t cursor_y = get_cursor_Ypos(cursor);

    // Check if the cursor is over the "Single Mode" button
    if (cursor_x >= center_x - 356 / 2 && cursor_x <= center_x + 356 / 2 &&
        cursor_y >= center_y + 300 && cursor_y <= center_y + 300 + 200) {
      return 2; // Goes to single mode
    }

    // Check if the cursor is over the "Exit" button
    if (cursor_x >= center_x - 356 / 2 && cursor_x <= center_x + 356 / 2 &&
        cursor_y >= center_y + 600 && cursor_y <= center_y + 600 + 200) {
      return 1; // Exit the game
    }
  }

  return 0; // Continue the game
}
