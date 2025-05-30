#include "mm_winner.h"

struct mm_winner_imp {
  Sprite *background; // Background sprite for the winner screen
  int winner; // 0 - No winner, 1 - Current player wins, 2 - Other player wins
};

MmWinner *create_mm_winner(SpriteLoader *loader, int winner) {
  MmWinner *mm_winner = (MmWinner *) malloc(sizeof(MmWinner));
  if (mm_winner == NULL) {
    return NULL;
  }
  mm_winner->winner = winner;
  mm_winner->background = get_menu_background(loader); // Load the background sprite
  
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
  if (mm_winner->winner == 0) {
    printf("Draw! \n");
  } else if (mm_winner->winner == 1) {
    printf("Current player wins!\n");
  } else if (mm_winner->winner == 2) {
    printf("Other player wins!\n");
  } 
  draw_sprite(mm_winner->background, 0, 0); // Draw the background
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
