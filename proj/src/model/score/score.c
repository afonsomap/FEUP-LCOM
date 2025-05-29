#include "score.h"

struct score_imp {
  uint16_t x; // X coordinate of the score
  uint16_t y; // Y coordinate of the score
  uint8_t score; // Current score
  uint8_t score_rate; // Rate at which the score increases
};

Score *create_score(uint16_t x, uint16_t y) {
  Score *score = (Score *) malloc(sizeof(Score));
  if (score == NULL) {
    return NULL; // Memory allocation failed
  }

  score->x = x;
  score->y = y;
  score->score = 0; // Initialize score to 0
  score->score_rate = 60; // Initialize score rate

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
    return; // Nothing to draw
  }

  uint8_t score_value = get_score_value(score);
  uint16_t x = score->x;   
  uint16_t y = score->y;

  while (score_value > 0) {
    uint8_t digit = score_value % 10; // Get the last digit
    score_value /= 10; // Remove the last digit

    // Draw the digit at the specified position
    draw_sprite(get_number_sprite(digit), x, y);
    x -= get_sprite_width(get_number_sprite(digit)); // Move left for the next digit
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


