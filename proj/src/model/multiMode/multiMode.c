#include "multiMode.h"

#define GRID_WIDTH 17
#define GRID_HEIGHT 15

struct multiMode_imp{
  Player *player1;
  Player *player2;
  Bomb *bomb_matrix[GRID_WIDTH][GRID_HEIGHT]; // Matrix of bomb pointers
  Wall *wall_matrix[GRID_WIDTH][GRID_HEIGHT]; // Matrix of wall pointers
  Explosion *explosion_matrix[GRID_WIDTH][GRID_HEIGHT]; // Matrix of explosion pointers
  uint16_t grid_square_width; // Width of each grid square
  uint16_t x_initial_grid; // X coordinate of the initial grid
  uint16_t y_initial_grid; // Y coordinate of the initial grid
  Sprite *game_background; // Game background sprite
  Sprite *grid_background; // Background of the grid sprite
  BombOptions *bomb_options; // Bomb options
  BombType player1_bomb_option; // Bomb option for player 1
  BombType player2_bomb_option; // Bomb option for player 2
  Sprite* exit_button_sprite;
}

uint16_t EXIT_BTN_X = 20;
uint16_t EXIT_BTN_Y = 20;

MultiMode *create_multiMode(SpriteLoader *loader){
  MultiMode *mm = (MultiMode *) malloc(sizeof(MultiMode));
  if (mm == NULL) {
    return NULL;
  }
  
  mm->x_initial_grid = 208; // Initialize grid position
  mm->y_initial_grid = 52; // Initialize grid position
  mm->grid_square_width = get_sprite_width(get_wall(loader)); // Get the width of the grid square
  mm->grid_background = get_grid_background(loader); // Get the background sprite
  mm->game_background = get_game_background(loader); // Get the game background sprite
  mm->exit_button_sprite = get_exit(loader);

  mm->player1 = create_player(1* mm->grid_square_width, 1 * mm->grid_square_width, get_player1_left(loader), get_player1_right(loader), get_player1_up(loader), get_player1_down(loader), get_player1_standing(loader));

  mm->player2 = create_player(15* mm->grid_square_width, 13 * mm->grid_square_width, get_player2_left(loader), get_player2_right(loader), get_player2_up(loader), get_player2_down(loader), get_player2_standing(loader));

  if (mm->player1 == NULL || mm->player2 == NULL) {
    free(mm);
    return NULL;
  }

  // Initialize wall matrix
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {

      if (i == 0 || i == GRID_HEIGHT - 1 || j == 0 || j == GRID_WIDTH - 1) {
        // Create indestructible walls at the borders
        mm->wall_matrix[j][i] = create_wall(j, i, get_solid_wall(loader), 0, 1);
      } else if (i % 2 == 0 && j % 2 == 0) {
        // Create indestructible walls in the center
        mm->wall_matrix[j][i] = create_wall(j, i, get_solid_wall(loader), 0, 1);
      }else if (i == 5 || j == 3) {
        // Create destructible walls in the center
        mm->wall_matrix[j][i] = create_wall(j, i, get_wall(loader), 1, 1);
      }else {
        // Create desctuctible walls in the center, but inactive
        mm->wall_matrix[j][i] = create_wall(j, i, get_wall(loader), 1, 0);
      }


      mm->bomb_matrix[j][i] = create_bomb(j, i, get_bomb(loader), 0);
      mm->explosion_matrix[j][i] = create_explosion(j, i, get_explosion(loader));
    }
  }

  mm->bomb_options = create_bomb_options(get_bomb_options(loader), get_selected_options(loader));
  mm->player1_bomb_option = NORMAL;
  mm->player2_bomb_option = NORMAL;

  return mm;
}

void destroy_multiMode(MultiMode *mm) {
  if (mm == NULL) {
    return;
  }

  // Destroy players
  destroy_player(mm->player1);
  destroy_player(mm->player2);

  // Destroy walls, bombs, and explosions
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      destroy_wall(mm->wall_matrix[j][i]);
      destroy_bomb(mm->bomb_matrix[j][i]);
      destroy_explosion(mm->explosion_matrix[j][i]);
    }
  }

  // Destroy bomb options
  destroy_bomb_options(mm->bomb_options);

  free(mm);
}

void draw_multiMode(MultiMode *mm) {
  if (mm == NULL) {
    return;
  }
  
  // Draw background
  draw_sprite(mm->grid_background, mm->x_initial_grid + 33, mm->y_initial_grid + 50);

  //Draw Exit Button
  draw_sprite(mm->exit_button_sprite, EXIT_BTN_X, EXIT_BTN_Y);

  // Draw walls, bombs, explosions and player
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      draw_wall(mm->wall_matrix[j][i], mm->x_initial_grid, mm->y_initial_grid, mm->grid_square_width);
      draw_bomb(mm->bomb_matrix[j][i], mm->x_initial_grid, mm->y_initial_grid, mm->grid_square_width);
      draw_explosion(mm->explosion_matrix[j][i], mm->x_initial_grid, mm->y_initial_grid, mm->grid_square_width);
    }

    if (get_player_Ypos(mm->player1) / mm->grid_square_width == i) {
      draw_player(mm->player1, mm->x_initial_grid, mm->y_initial_grid);
    }

    if (get_player_Ypos(mm->player2) / mm->grid_square_width == i) {
      draw_player(mm->player2, mm->x_initial_grid, mm->y_initial_grid);
    }
  }

  draw_bomb_options(mm->bomb_options, mm->player1_bomb_option);
  draw_bomb_options(mm->bomb_options, mm->player2_bomb_option);
}

static bool check_wall_collision(MultiMode *mm, uint16_t x, uint16_t y) {
  if (mm == NULL) {
    return true;
  }

  //calculate the grids positions of the 4 corners of the player
  uint16_t grid_x_top_left = x / mm->grid_square_width;
  uint16_t grid_y_top_left = y / mm->grid_square_width;
  
  uint16_t grid_x_bottom_right = (x + (mm->grid_square_width-1)) / mm->grid_square_width;
  uint16_t grid_y_bottom_right = (y + (mm->grid_square_width-1)) / mm->grid_square_width;

  uint16_t grid_x_top_right = (x + mm->grid_square_width -1) / mm->grid_square_width;
  uint16_t grid_y_top_right = y / mm->grid_square_width;

  uint16_t grid_x_bottom_left = x / mm->grid_square_width;
  uint16_t grid_y_bottom_left = (y + (mm->grid_square_width -1)) / mm->grid_square_width;
  // Check if the player is out of bounds

  if (grid_x_top_left < 0 || grid_x_bottom_right >= GRID_WIDTH || grid_y_top_left < 0 || grid_y_bottom_right >= GRID_HEIGHT) {
    return true; // Out of bounds
  }

  if (mm->wall_matrix[grid_x_top_left][grid_y_top_left] == NULL || is_wall_active(mm->wall_matrix[grid_x_top_left][grid_y_top_left])) {
    return true; // Wall at the position
  }
  if (mm->wall_matrix[grid_x_bottom_right][grid_y_bottom_right] == NULL || is_wall_active(mm->wall_matrix[grid_x_bottom_right][grid_y_bottom_right])) {
    return true; // Wall at the position
  }
  if (mm->wall_matrix[grid_x_top_right][grid_y_top_right] == NULL || is_wall_active(mm->wall_matrix[grid_x_top_right][grid_y_top_right])) {
    return true; // Wall at the position
  }
  if (mm->wall_matrix[grid_x_bottom_left][grid_y_bottom_left] == NULL || is_wall_active(mm->wall_matrix[grid_x_bottom_left][grid_y_bottom_left])) {
    return true; // Wall at the position
  }
  return false; // No wall collision
}


// 0 Continue game
// 1 Goes back to menu  