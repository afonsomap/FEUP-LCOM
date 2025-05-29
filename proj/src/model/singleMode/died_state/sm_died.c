#include "sm_died.h"

struct SmDied_imp {
  Sprite *background;
  Sprite *SmDied_title;
  Sprite *exit_button;
  uint16_t xPos_title;
  uint16_t xPos_button;
  uint16_t yPos_button;
};

SmDied* create_sm_died(SpriteLoader *loader) {
  SmDied *d = (SmDied *) malloc(sizeof(SmDied));
  if (d == NULL) {
    return NULL;
  }

  d->background = get_menu_background(loader);
  d->SmDied_title = get_died_title(loader);
  d->exit_button = get_exit_button(loader);

  if (d->background == NULL || d->exit_button == NULL) {
    destroy_sm_died(d);
    return NULL;
  }

  d->xPos_title = (get_mode_info().XResolution - get_sprite_width(d->SmDied_title)) / 2;
  d->xPos_button = (get_mode_info().XResolution - get_sprite_width(d->exit_button)) / 2;
  d->yPos_button = 700; // Fixed position for the button

  return d;
}

void destroy_sm_died(SmDied *d) {
  if (d == NULL) {
    return;
  }
  free(d);
}

void draw_sm_died(SmDied *d) {
  if (d == NULL) {
    return;
  }

  draw_sprite(d->background, 0, 0);
  draw_sprite(d->SmDied_title, d->xPos_title, 100);
  draw_sprite(d->exit_button, d->xPos_button, d->yPos_button);  
}

// 0 Continue game
// 1 Go back to menu
int process_sm_died_mouse(SmDied *d, Cursor *cursor) {
  if (d == NULL || cursor == NULL) {
    return 1; 
  }

  // Left mouse button pressed
  if (get_cursor_button_pressed(cursor, 0)) {
    uint16_t cursor_x = get_cursor_Xpos(cursor);
    uint16_t cursor_y = get_cursor_Ypos(cursor);

    if (cursor_x >= d->xPos_button && cursor_x <= d->xPos_button + get_sprite_width(d->exit_button) && cursor_y >=  d->yPos_button && cursor_y <= d->yPos_button + get_sprite_height(d->exit_button)) {
      return 1;
    }
  }

  return 0; 
}

// 0 Continue in the died state
// 1 Exit to menu
int process_sm_died_kbd(SmDied *d, KeyPressed *key) {
  if (d == NULL || key == NULL) {
    return 1
  }

  if (is_esc_pressed(key)) {
    return 1; 
  }

  return 0;
}
