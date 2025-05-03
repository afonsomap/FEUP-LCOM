#include "singleMode.h"

#define GRID_WIDTH 17
#define GRID_HEIGHT 15

struct singleMode_imp {
  Player *player1;
  Bomb *bomb_matrix[GRID_WIDTH][GRID_HEIGHT]; // Matrix of bomb pointers
  Wall *wall_matrix[GRID_WIDTH][GRID_HEIGHT]; // Matrix of wall pointers
  uint16_t grid_square_width; // Width of each grid square
  uint16_t x_initial_grid; // X coordinate of the initial grid
  uint16_t y_initial_grid; // Y coordinate of the initial grid
};


SingleMode *create_singleMode(SpriteLoader *loader) {
  SingleMode *sm = (SingleMode *) malloc(sizeof(SingleMode));
  if (sm == NULL) {
    return NULL;
  }

  sm->x_initial_grid = 0; // Initialize grid position
  sm->y_initial_grid = 0; // Initialize grid position
  sm->grid_square_width = get_sprite_width(get_wall(loader)); // Get the width of the grid square


  // Create player
  sm->player1 = create_player(1* sm->grid_square_width, 1 * sm->grid_square_width, get_player1_left(loader), get_player1_right(loader), get_player1_up(loader), get_player1_down(loader), get_player1_standing(loader));

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
      }else{
        // Create destructible walls in the center
        sm->wall_matrix[j][i] = create_wall(j, i, get_wall(loader), 1, 0);
      }

      sm->bomb_matrix[j][i] = create_bomb(j, i, get_bomb(loader), 0);
    }
  }

  return sm;
}

void destroy_singleMode(SingleMode *sm) {
  if (sm == NULL) {
    return;
  }

  // Destroy player
  destroy_player(sm->player1);

  // Destroy walls
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      destroy_wall(sm->wall_matrix[j][i]);
      destroy_bomb(sm->bomb_matrix[j][i]);
    }
  }

  free(sm);
}

void draw_singleMode(SingleMode *sm) {
  if (sm == NULL) {
    return;
  }

  // Draw walls
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {

      if ( get_player_Xpos(sm->player1)/sm->grid_square_width == j && get_player_Ypos(sm->player1)/sm->grid_square_width == i) {
        draw_player(sm->player1, sm->x_initial_grid, sm->y_initial_grid);
      }
      draw_wall(sm->wall_matrix[j][i], sm->x_initial_grid, sm->y_initial_grid, sm->grid_square_width);
      draw_bomb(sm->bomb_matrix[j][i], sm->x_initial_grid, sm->y_initial_grid);
    }
  }
}

static bool check_wall_collision(SingleMode *sm, uint16_t x, uint16_t y) {
  if (sm == NULL) {
    return true;
  }

  //calculate the grids positions of the 4 corners of the player
  uint16_t grid_x_top_left = x / sm->grid_square_width;
  uint16_t grid_y_top_left = y / sm->grid_square_width;
  
  uint16_t grid_x_bottom_right = (x + (sm->grid_square_width-1)) / sm->grid_square_width;
  uint16_t grid_y_bottom_right = (y + (sm->grid_square_width-1)) / sm->grid_square_width;

  uint16_t grid_x_top_right = (x + sm->grid_square_width -1) / sm->grid_square_width;
  uint16_t grid_y_top_right = y / sm->grid_square_width;

  uint16_t grid_x_bottom_left = x / sm->grid_square_width;
  uint16_t grid_y_bottom_left = (y + (sm->grid_square_width -1)) / sm->grid_square_width;
  // Check if the player is out of bounds

  if (grid_x_top_left < 0 || grid_x_bottom_right >= GRID_WIDTH || grid_y_top_left < 0 || grid_y_bottom_right >= GRID_HEIGHT) {
    return true; // Out of bounds
  }

  if (sm->wall_matrix[grid_x_top_left][grid_y_top_left] == NULL || is_wall_active(sm->wall_matrix[grid_x_top_left][grid_y_top_left])) {
    return true; // Wall at the position
  }
  if (sm->wall_matrix[grid_x_bottom_right][grid_y_bottom_right] == NULL || is_wall_active(sm->wall_matrix[grid_x_bottom_right][grid_y_bottom_right])) {
    return true; // Wall at the position
  }
  if (sm->wall_matrix[grid_x_top_right][grid_y_top_right] == NULL || is_wall_active(sm->wall_matrix[grid_x_top_right][grid_y_top_right])) {
    return true; // Wall at the position
  }
  if (sm->wall_matrix[grid_x_bottom_left][grid_y_bottom_left] == NULL || is_wall_active(sm->wall_matrix[grid_x_bottom_left][grid_y_bottom_left])) {
    return true; // Wall at the position
  }
  return false; // No wall collision
}

void process_input(SingleMode *sm, bool* keys) {
  if (sm == NULL) {
    return;
  }

  if (keys[0]){ // Up
    for (int i = 0; i < get_player_speed(sm->player1); i++) {
      if (!check_wall_collision(sm, get_player_Xpos(sm->player1), get_player_Ypos(sm->player1) - 1)){
        player_move_up(sm->player1);
      }else{
        break;
      }
    }
  }
  if (keys[1]){ // Down
    for (int i = 0; i < get_player_speed(sm->player1); i++) {
      if (!check_wall_collision(sm, get_player_Xpos(sm->player1), get_player_Ypos(sm->player1) + 1)){
        player_move_down(sm->player1);
      }else{
        break;
      }
    }
  }
  if (keys[2]){ // Left
    for (int i = 0; i < get_player_speed(sm->player1); i++) {
      if (!check_wall_collision(sm, get_player_Xpos(sm->player1) - 1, get_player_Ypos(sm->player1))){
        player_move_left(sm->player1);
      }else{
        break;
      }
    }
  }
  if (keys[3]){ // Right
    for (int i = 0; i < get_player_speed(sm->player1); i++) {
      if (!check_wall_collision(sm, get_player_Xpos(sm->player1) + 1, get_player_Ypos(sm->player1))){
        player_move_right(sm->player1);
      }else{
        break;
      }
    }
  }
  if (!keys[0] && !keys[1] && !keys[2] && !keys[3]){
    player_stand(sm->player1);
  }
}

