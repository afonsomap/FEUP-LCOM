#include "score.h"

struct score_imp {
  uint16_t x; // X coordinate of the score
  uint16_t y; // Y coordinate of the score
  uint8_t score; // Current score
  uint8_t score_rate; // Rate at which the score increases
  Sprite *number_sprites[10]; // Array of sprites for digits 0-9
};

Score *create_score(uint16_t x, uint16_t y, SpriteLoader *loader) {
  Score *score = (Score *) malloc(sizeof(Score));
  if (score == NULL) {
    return NULL; // Memory allocation failed
  }

  score->x = x;
  score->y = y;
  score->score = 0; // Initialize score to 0
  score->score_rate = 60; // Initialize score rate
  for (int i = 0; i < 10; i++) {
    score->number_sprites[i] = get_number_sprite(i, loader); // Load sprites for digits 0-9
    if (score->number_sprites[i] == NULL) {
      destroy_score(score); // Clean up if sprite loading fails
      return NULL;
    }
  }

  return score;
}

void destroy_score(Score *score) {
  if (score == NULL) {
    return; // Nothing to destroy
  }

  free(score); // Free the allocated memory for the score
}

int increment_score(Score *score) {
  if (score == NULL) {
    return -1; // Invalid score pointer
  }

  score->score += 1; // Increment the score by 1
  score->score_rate = 60; // Reset the score rate to 60
  return score->score; // Return the updated score
}

int decrease_score_rate(Score *score) {
  if (score == NULL) {
    return -1; // Invalid score pointer
  }

  if (score->score_rate > 0) {
    score->score_rate--; // Decrease the score rate
    return score->score_rate; // Return the updated score rate
  }

  return 0; // Score rate is already at minimum
}

uint8_t get_score_value(Score *score) {
  if (score == NULL) {
    return 0; // Invalid score pointer, return 0
  }

  return score->score; // Return the current score value
}

void draw_score(Score *score) {
  if (score == NULL) {
    printf("Score is NULL\n");
    return; // Nothing to draw
  }

  uint8_t score_value = get_score_value(score);
  printf("Score value: %d\n", score_value);  // Debug print to check the score

  uint16_t x = get_score_Xposition(score);   
  uint16_t y = get_score_Yposition(score);

  if (score_value == 0) {
    // If score is 0, draw the digit 0
    draw_sprite(score->number_sprites[0], x, y);
    return;
  }

  while (score_value > 0) {
    uint8_t digit = score_value % 10; // Get the last digit
    score_value /= 10; // Remove the last digit

    Sprite *digit_sprite = score->number_sprites[digit]; // Get the sprite for the digit
    if (digit_sprite != NULL) {
      draw_sprite(digit_sprite, x, y); // Draw the digit sprite at the specified position
    }
    x -= get_sprite_width(digit_sprite); // Move the x position to the left for the next digit
  }
}

uint16_t get_score_Xposition(Score *score) {
  if (score == NULL) {
    return 0; // Invalid score pointer, return 0
  }

  return score->x; // Return the x-coordinate of the score
}

uint16_t get_score_Yposition(Score *score) {
  if (score == NULL) {
    return 0; // Invalid score pointer, return 0
  }

  return score->y; // Return the y-coordinate of the score
}

uint8_t get_score_rate(Score *score) {
  if (score == NULL) {
    return 0; // Invalid score pointer, return 0
  }

  return score->score_rate; // Return the current score rate
}
