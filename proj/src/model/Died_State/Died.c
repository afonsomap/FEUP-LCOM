#include "Died.h"

uint16_t center2_x = 1280 / 2;
uint16_t center2_y = 50; 

struct died_imp {
  Sprite *background;
  Sprite *died_title;
  Sprite *exit_button;
};

Died* create_Died_Page(SpriteLoader *loader) {
  Died *d = (Died *) malloc(sizeof(Died));
  if (d == NULL) {
    return NULL;
  }

  d->background = get_menu_background(loader);
  d->died_title = get_died_title(loader);
  d->exit_button = get_exit_button(loader);

  if (d->background == NULL || d->exit_button == NULL) {
    destroy_died(d);
    return NULL;
  }

  return d;
}

void destroy_died(Died *d) {
  if (d == NULL) {
    return;
  }

  free(d);
}

void draw_died(Died *d) {
  if (d == NULL) {
    return;
  }

  draw_sprite(d->background, 0, 0);
  draw_sprite(d->died_title, center2_x - 250 / 2, center2_y); // Draw the title at (100, 50)
  draw_sprite(d->exit_button, center2_x - 200 / 2, center2_y + 500);   
}

int process_died_input(Cursor *cursor) {
  if (get_cursor_button_pressed(cursor, 0)) { // Left mouse button pressed
    uint16_t cursor_x = get_cursor_Xpos(cursor);
    uint16_t cursor_y = get_cursor_Ypos(cursor);

    // Check if the cursor is over the "Exit" button
    if (cursor_x >= center2_x - 200 / 2 && cursor_x <= center2_x + 200 / 2 &&
        cursor_y >= center2_y + 500 && cursor_y <= center2_y + 500 + 200) {
      return 1; // Exit the game
    }
  }

  return 0; // Continue the game
}
