#include "died_state.h"

struct died_imp {
  Sprite *died_title;
  Sprite *died_background;
  Sprite *back_to_menu;
  Sprite *play_again;
  Sprite *exit_button;
  Sprite *your_score;
  uint16_t xPos_title;
  uint16_t xPos_button;
  uint16_t yPos_button;
  Score *score;
};

Died* create_died_page(SpriteLoader *loader, Score *score) {
  Died *d = (Died *) malloc(sizeof(Died));
  if (d == NULL) {
    return NULL;
  }

  d->died_background = get_died_background(loader);
  d->back_to_menu = get_back_to_menu(loader);
  d->play_again = get_play_again(loader);
  d->died_title = get_died_title(loader);
  d->your_score = get_your_score_text(loader);

  if (d->died_background == NULL || d->exit_button == NULL) {
    destroy_died(d);
    return NULL;
  }

  d->xPos_title = (get_mode_info().XResolution - get_sprite_width(d->died_title)) / 2;
  d->xPos_button = (get_mode_info().XResolution - get_sprite_width(d->exit_button)) / 2;
  d->yPos_button = 700; // Fixed position for the button

  d->score = score;

  return d;
}

void destroy_died(Died *d) {
  if (d == NULL) {
    return;
  }

  free(d);
}

void draw_died(Died *d, Score *score) {
  if (d == NULL) return;

  int screen_center_x = get_mode_info().XResolution / 2;

  // Get widths
  int your_score_width = get_sprite_width(d->your_score);
  int score_width = 14; // ← you must implement this

  // Combined width of "Your Score" + actual score
  int total_width = your_score_width + 10 + score_width;

  // X offset so the combined line is centered
  int start_x = screen_center_x - total_width / 2;

  // Y positions
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
  draw_score_at(score, start_x + total_width - score_width - 10, y_score_line);

  draw_sprite(d->play_again, play_again_x, play_again_y);
  draw_sprite(d->back_to_menu, back_to_menu_x, back_to_menu_y);
}

int process_died_input(Died *d, Cursor *cursor) {
  if (get_cursor_button_pressed(cursor, 0)) { // Left mouse button pressed

    // Check if the cursor is over the "Exit" button
    if (get_cursor_Xpos(cursor) >= d->xPos_button && get_cursor_Xpos(cursor) <= d->xPos_button + get_sprite_width(d->exit_button) &&
        get_cursor_Ypos(cursor) >=  d->yPos_button && get_cursor_Ypos(cursor) <= d->yPos_button + get_sprite_height(d->exit_button)) {
      return 1; // Exit the game
    }

    // Check if the cursor is over the "Play Again" button
    if (get_cursor_Xpos(cursor) >= d->xPos_button && get_cursor_Xpos(cursor) <= d->xPos_button + get_sprite_width(d->play_again) &&
        get_cursor_Ypos(cursor) >=  d->yPos_button - 200 && get_cursor_Ypos(cursor) <= d->yPos_button - 200 + get_sprite_height(d->play_again)) {
      return 2; // Play again
    }
  }

  return 0; // Continue the game
}
