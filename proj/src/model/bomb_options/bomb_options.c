#include "bomb_options.h"

struct bomb_options_imp {
  Sprite* options[3];
  Sprite* selected_option[3];
  uint16_t options_x_initial;
  uint16_t options_x_final;
  uint16_t options_y_initial[3]; 
  uint16_t options_y_final[3];
  uint8_t number_of_options;
  uint8_t availability_counter[3]; // 0: available, 1: unavailable
  uint8_t spawn_counter;
  BombType selectedBomb;
};

uint16_t get_options_x_initial(BombOptions *b) {
  if (b == NULL) {
    return 0;
  }
  return b->options_x_initial;
}

uint16_t get_options_x_final(BombOptions *b) {
  if (b == NULL) {
    return 0;
  }
  return b->options_x_final;
}

uint16_t get_options_y_initial(BombOptions *b, int index) {
  if (b == NULL || index < 0 || index > b->number_of_options-1) {
    return 0;
  }
  return b->options_y_initial[index];
}

uint16_t get_options_y_final(BombOptions *b, int index) {
  if (b == NULL || index < 0 || index > b->number_of_options-1) {
    return 0;
  }
  return b->options_y_final[index];
}

uint8_t get_number_of_options(BombOptions *b) {
  if (b == NULL) {
    return 0;
  }
  return b->number_of_options;
}


BombOptions *create_bomb_options(Sprite** options, Sprite** selected_option) {

  BombOptions *bomb_options = (BombOptions *) malloc(sizeof(BombOptions));
  if (bomb_options == NULL) {
    return NULL;
  }

  for (int i = 0; i < 3; i++) {
    bomb_options->options[i] = options[i];
    bomb_options->selected_option[i] = selected_option[i];
  }
  uint16_t sprite_width = get_sprite_width(options[0]);
  uint16_t sprite_height = get_sprite_height(options[0]);

  bomb_options->options_x_initial = 10; // Initial x position
  bomb_options->options_x_final = 10 + sprite_width; // Final x position

  bomb_options->options_y_initial[0] = 200; // Initial y position
  bomb_options->options_y_initial[1] = 400;
  bomb_options->options_y_initial[2] = 600;
  
  bomb_options->options_y_final[0] = 200 + sprite_height; // Final y position
  bomb_options->options_y_final[1] = 400 + sprite_height;
  bomb_options->options_y_final[2] = 600 + sprite_height;

  bomb_options->number_of_options = 3; // Number of options

  return bomb_options;
}

void destroy_bomb_options(BombOptions *b) {
  if (b == NULL) {
    return;
  }

  free(b);
  b = NULL;
}

void draw_bomb_options(BombOptions *b, int selected_option) {
  if (b == NULL || selected_option < 0 || selected_option > b->number_of_options-1) {
    return;
  }

  for (int i = 0; i < b->number_of_options; i++) {
    if (i == selected_option) {
      draw_sprite(b->selected_option[i], b->options_x_initial, b->options_y_initial[i]);
    } else {
      draw_sprite(b->options[i], b->options_x_initial, b->options_y_initial[i]);
    }
  }
}

void set_bomb_unavailable(BombOptions *b, BombType type) {
  if (b == NULL) {
    return;
  }
  if (type == NORMAL) {
    b->availability_counter[0] = 180; 
  }
  else if (type == CONSTRUCTIVE) {
    b->availability_counter[1] = 180; 
  }
  else if (type == FULL_LINE) {
    b->availability_counter[2] = 180; 
  }
}

bool isBombAvailable(BombOptions *b, BombType type) {
  if (b == NULL) {
    return false;
  }

  if (type == NORMAL) {
    return b->availability_counter[0] == 0;
  }
  else if (type == CONSTRUCTIVE) {
    return b->availability_counter[1] == 0;
  }
  else if (type == FULL_LINE) {
    return b->availability_counter[2] == 0;
  }
  
  return false; // Default case
}

void decrease_time_availability(BombOptions *b) {
  if (b == NULL) {
    return;
  }

  for (int i = 0; i < b->number_of_options; i++) {
    if (b->availability_counter[i] > 0) {
      b->availability_counter[i]--;
    }
  }
}

void decrease_time_spawning(BombOptions *b) {
  if (b == NULL) {
    return;
  }

  if (b->spawn_counter > 0) {
    b->spawn_counter--;
  }
}

bool is_spawning(BombOptions *b) {
  if (b == NULL) {
    return false;
  }
  return b->spawn_counter == 0;
}

void set_spawn_rate(BombOptions *b) {
  if (b == NULL) {
    return;
  }
  b->spawn_counter = 60; 
}

BombType get_random_bomb() {
  int r = rand() % 3; // generates 0, 1, or 2
  if (r == 0) return NORMAL;
  else if (r == 1) return FULL_LINE;
  else return CONSTRUCTIVE;
}

