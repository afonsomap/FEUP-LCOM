#include "mm_winner.h"

struct mm_winner_imp {
  Sprite *background; // Background sprite for the winner screen
  Sprite *you_won; // Sprite for "You Won" message
  Sprite *you_lost; // Sprite for "You Lost" message
  Sprite *draw; // Sprite for "Draw" message
  int winner; // 0 - No winner, 1 - Current player wins, 2 - Other player wins
};

MmWinner *create_mm_winner(SpriteLoader *loader, int winner) {
  MmWinner *mm_winner = (MmWinner *) malloc(sizeof(MmWinner));
  if (mm_winner == NULL) {
    return NULL;
  }
  mm_winner->winner = winner;
  mm_winner->background = get_winners_background(loader); // Load the background sprite
  mm_winner->you_won = get_winners_you_won(loader); // Load the "You Won" sprite
  mm_winner->you_lost = get_winners_you_lost(loader); // Load the "You Lost" sprite
  mm_winner->draw = get_winners_draw(loader); // Load the "Draw" sprite

  if (mm_winner->background == NULL || mm_winner->you_won == NULL || mm_winner->you_lost == NULL || mm_winner->draw == NULL) {
    destroy_mm_winner(mm_winner);
    return NULL; // Return NULL if any sprite loading fails
  }
  
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
    draw_sprite(mm_winner->draw, get_sprite_width(mm_winner->background) / 2, get_sprite_height(mm_winner->background) / 2); // Draw the background
    printf("Draw! \n");
  } else if (mm_winner->winner == 1) {
    draw_sprite(mm_winner->you_won, get_sprite_width(mm_winner->background) / 2, get_sprite_height(mm_winner->background) / 2); // Draw the "You Won" sprite
    printf("Current player wins!\n");
  } else if (mm_winner->winner == 2) {
    draw(mm_winner->you_lost, get_sprite_width(mm_winner->background) / 2, get_sprite_height(mm_winner->background) / 2); // Draw the "You Lost" sprite
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
