#include "sm_died.h"

struct SmDied_imp {
  Sprite *died_title;
  Sprite *died_background;
  Sprite *back_to_menu;
  Sprite *play_again;
  Sprite *your_score;
  uint16_t xPos_title;
  uint16_t xPos_button;
  uint16_t yPos_button;
  Score *score; 
};

SmDied* create_sm_died(SpriteLoader *loader, Score *score) {
  SmDied *d = (SmDied *) malloc(sizeof(SmDied));
  if (d == NULL) {
    return NULL;
  }

  d->died_background = get_died_background(loader);
  d->back_to_menu = get_back_to_menu(loader);
  d->play_again = get_play_again(loader);
  d->died_title = get_died_title(loader);
  d->your_score = get_your_score_text(loader);

  if (d->died_background == NULL) {
    destroy_sm_died(d);
    return NULL;
  }

  d->xPos_title = (get_mode_info().XResolution - get_sprite_width(d->died_title)) / 2;
  d->xPos_button = (get_mode_info().XResolution - get_sprite_width(d->back_to_menu)) / 2;
  d->yPos_button = 700; // Fixed position for the button
  d->score = score;

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

  int screen_center_x = get_mode_info().XResolution / 2;


  int your_score_width = get_sprite_width(d->your_score);
  int score_width = 14; 

  int total_width = your_score_width + 10 + score_width;

  int start_x = screen_center_x - total_width / 2;

  int y_title = 150;
  int y_your_score = y_title + get_sprite_height(d->died_title);
  int y_score_line = y_your_score + ((get_sprite_height(d->your_score)/2) - 20/2); //20/2 is the height / 2

  // Button Y positions
  int play_again_y = 700 - 200;
  int back_to_menu_y = 700;

  // Button X positions (centered)
  int play_again_x = screen_center_x - get_sprite_width(d->play_again) / 2;
  int back_to_menu_x = screen_center_x - get_sprite_width(d->back_to_menu) / 2;

  // Draw everything
  draw_sprite(d->died_background, 0, 0);
  draw_sprite(d->died_title, screen_center_x - get_sprite_width(d->died_title) / 2, y_title);
  draw_sprite(d->your_score, start_x, y_your_score);
  draw_score(d->score, start_x + total_width - score_width - 10, y_score_line);
  draw_sprite(d->play_again, play_again_x, play_again_y);
  draw_sprite(d->back_to_menu, back_to_menu_x, back_to_menu_y);
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

    if (cursor_x >= d->xPos_button && cursor_x <= d->xPos_button + get_sprite_width(d->back_to_menu) && cursor_y >=  d->yPos_button && cursor_y <= d->yPos_button + get_sprite_height(d->back_to_menu)) {
      return 1;
    }

    if (cursor_x >= d->xPos_button && cursor_x <= d->xPos_button + get_sprite_width(d->play_again) && cursor_y >=  d->yPos_button - 200 && cursor_y <= d->yPos_button - 200 + get_sprite_height(d->play_again)) {
      return 2; // Play again
    }
  }

  return 0; 
}

// 0 Continue in the died state
// 1 Exit to menu
int process_sm_died_kbd(SmDied *d, KeyPressed *key) {
  if (d == NULL || key == NULL) {
    return 1;
  }

  if (is_esc_pressed(key)) {
    return 1; 
  }

  return 0;
}
