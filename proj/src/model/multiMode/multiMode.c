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
  SingleMode *sm = (SingleMode *) malloc(sizeof(SingleMode));
  if (sm == NULL) {
    return NULL;
  }
  
  sm->x_initial_grid = 208; // Initialize grid position
  sm->y_initial_grid = 52; // Initialize grid position
  sm->grid_square_width = get_sprite_width(get_wall(loader)); // Get the width of the grid square
  sm->grid_background = get_grid_background(loader); // Get the background sprite
  sm->game_background = get_game_background(loader); // Get the game background sprite
  sm->exit_button_sprite = get_exit(loader);

  sm->player1 = create_player(1* sm->grid_square_width, 1 * sm->grid_square_width, get_player1_left(loader), get_player1_right(loader), get_player1_up(loader), get_player1_down(loader), get_player1_standing(loader));

  sm->player2 = create_player(15* sm->grid_square_width, 13 * sm->grid_square_width, get_player2_left(loader), get_player2_right(loader), get_player2_up(loader), get_player2_down(loader), get_player2_standing(loader));

  if (sm->player1 == NULL) {
    free(sm);
    return NULL;
  }

  // Initialize wall matrix
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {

      if (i == 0 || i == GRID_HEIGHT - 1 || j == 0 || j == GRID_WIDTH - 1) {
        // Create indestructible walls at the borders
        sm->wall_matrix[j][i] = create_wall(j, i, get_solid_wall(loader), 0, 1);
      } else if (i % 2 == 0 && j % 2 == 0) {
        // Create indestructible walls in the center
        sm->wall_matrix[j][i] = create_wall(j, i, get_solid_wall(loader), 0, 1);
      }else if (i == 5 || j == 3) {
        // Create destructible walls in the center
        sm->wall_matrix[j][i] = create_wall(j, i, get_wall(loader), 1, 1);
      }else {
        // Create desctuctible walls in the center, but inactive
        sm->wall_matrix[j][i] = create_wall(j, i, get_wall(loader), 1, 0);
      }


      sm->bomb_matrix[j][i] = create_bomb(j, i, get_bomb(loader), 0);
      sm->explosion_matrix[j][i] = create_explosion(j, i, get_explosion(loader));
    }
  }

  sm->bomb_options = create_bomb_options(get_bomb_options(loader), get_selected_options(loader));
  sm->player1_bomb_option = NORMAL;

  return sm;
}