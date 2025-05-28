#include "died_state.h"

struct died_imp {
  Sprite *background;
  Sprite *died_title;
  Sprite *exit_button;
  uint16_t xPos_title;
  uint16_t xPos_button;
  uint16_t yPos_button;
};

Died* create_died_page(SpriteLoader *loader) {
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

  d->xPos_title = (get_mode_info().XResolution - get_sprite_width(d->died_title)) / 2;
  d->xPos_button = (get_mode_info().XResolution - get_sprite_width(d->exit_button)) / 2;
  d->yPos_button = 700; // Fixed position for the button

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
  draw_sprite(d->died_title, d->xPos_title, 100);
  draw_sprite(d->exit_button, d->xPos_button, d->yPos_button);  
}

int process_died_input(Died *d, Cursor *cursor) {
  if (get_cursor_button_pressed(cursor, 0)) { // Left mouse button pressed
    uint16_t cursor_x = get_cursor_Xpos(cursor);
    uint16_t cursor_y = get_cursor_Ypos(cursor);

    // Check if the cursor is over the "Exit" button
    if (cursor_x >= d->xPos_button && cursor_x <= d->xPos_button + get_sprite_width(d->exit_button) &&
        cursor_y >=  d->yPos_button && cursor_y <= d->yPos_button + get_sprite_height(d->exit_button)) {
      return 1; // Exit the game
    }
  }

  return 0; // Continue the game
}
