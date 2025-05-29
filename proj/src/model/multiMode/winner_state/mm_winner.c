#include "mm_winner.h"

struct mm_winner_imp {
  bool current_player_winner; // Winner player number (1 or 2)
};

MmWinner *create_mm_winner(SpriteLoader *loader, bool current_player_wins) {
  MmWinner *mm_winner = (MmWinner *) malloc(sizeof(MmWinner));
  if (mm_winner == NULL) {
    return NULL;
  }
  mm->current_player_winner = current_player_wins;
  
  return mm_winner;
}

void destroy_mm_winner(MmWinner *mm_winner) {
  if (mm_winner == NULL) {
    return;
  }
  free(mm_winner);
}

void draw_mm_winner(MmWinner *mm_winner) {
  if (mm_winner == NULL) {
    return;
  }
  if (mm_winner->current_player_winner) {
    printf("Current player wins!\n");
  } else {
    printf("Other player wins!\n");
  }
}

int process_mm_winner_mouse(MmWinner *mm_winner, Cursor *c) {
  if (mm_winner == NULL || c == NULL) {
    return -1; // Error
  }
  
  if (get_cursor_button_pressed(c, 0)) { // Check if left button is pressed
    reset_cursor_button_pressed(c); // Reset button state
    printf("Left button pressed on MM Winner screen\n");
    return 1; // Go back to menu or next state
  }
  return 0; // Continue game
}

int process_mm_winner_kbd(MmWinner *mm_winner, KeyPressed *kp) {
  if (mm_winner == NULL || kp == NULL) {
    return -1; // Error
  }

  if (is_esc_pressed(kp)) {
    printf("ESC pressed on MM Winner screen\n");
    return 1; // Go back to menu
  }
  
  return 0; // Continue game
}