#include "mm_game.h"

struct mm_game_imp {
  int player_number; // Player number (1 or 2)
  bool current_player_wins;
  SpriteLoader *loader; // Pointer to the sprite loader
};

MmGame *create_mm_game(SpriteLoader *loader, uint8_t player_number) {
  MmGame *mm_game = (MmGame *) malloc(sizeof(MmGame));
  if (mm_game == NULL) {
    return NULL;
  }
  
  mm_game->loader = loader;
  mm_game->player_number = player_number;
  mm_game->current_player_wins = false; // Initialize current player wins to false
  
  return mm_game;
}

void destroy_mm_game(MmGame *mm_game) {
  if (mm_game == NULL) {
    return;
  }
  free(mm_game);
}

void draw_mm_game(MmGame *mm_game) {
  if (mm_game == NULL) {
    return;
  }
  printf("Drawing MM Game for player %d\n", mm_game->player_number);
}

int process_mm_game_mouse(MmGame *mm_game, Cursor *c) {
  if (mm_game == NULL || c == NULL) {
    return -1; // Error
  }
  
  return 0; // Continue game
}
int process_mm_game_kbd(MmGame *mm_game, KeyPressed *kp) {
  if (mm_game == NULL || kp == NULL) {
    return -1; // Error
  }

  if (is_up_pressed(kp)) {
    mm_game->current_player_wins = true; // Set current player as winner
  }
  return 0; // Continue game
}
int process_mm_game_timer(MmGame *mm_game) {
  if (mm_game == NULL) {
    return -1; // Error
  }

  if (mm_game->current_player_wins) {
    printf("win");
    return 1; // Go to winner state
  }
  
  send_byte(0xFF); // Example of sending a byte, replace with actual game logic
  
  return 0; // Continue game
}
int process_mm_game_sp(MmGame *mm_game, uint8_t byte) {
  if (mm_game == NULL) {
    return -1; // Error
  }
  
  printf("Processing special input byte: %02X\n", byte);
  
  return 0; // Continue game
}

bool is_current_winner(MmGame *mm_game) {
  if (mm_game == NULL) {
    return false; // Error case
  }
  
  return mm_game->current_player_wins; // Return the current player's win status
}