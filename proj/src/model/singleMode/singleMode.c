#include "singleMode.h"


#define GRID_WIDTH 15
#define GRID_HEIGHT 13

struct singleMode_imp {
  Player *player1;
  Bomb *bomb_matrix[GRID_WIDTH][GRID_HEIGHT]; // Matrix of bomb pointers
  Wall *wall_matrix[GRID_WIDTH][GRID_HEIGHT]; // Matrix of wall pointers
  Explosion *explosion_matrix[GRID_WIDTH][GRID_HEIGHT]; // Matrix of explosion pointers
  uint16_t grid_square_width; // Width of each grid square
  uint16_t x_initial_grid; // X coordinate of the initial grid
  uint16_t y_initial_grid; // Y coordinate of the initial grid
  Sprite *grid_background; // Background sprite
};


SingleMode *create_singleMode(SpriteLoader *loader) {
  SingleMode *sm = (SingleMode *) malloc(sizeof(SingleMode));
  if (sm == NULL) {
    return NULL;
  }

  sm->x_initial_grid = 268; // Initialize grid position
  sm->y_initial_grid = 80; // Initialize grid position
  sm->grid_square_width = get_sprite_width(get_wall(loader)); // Get the width of the grid square
  sm->grid_background = get_grid_background(loader); // Get the background sprite

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
      destroy_explosion(sm->explosion_matrix[j][i]);
    }
  }
  destroy_sprite(sm->grid_background); // Destroy background sprite

  free(sm);
}

void draw_singleMode(SingleMode *sm) {
  if (sm == NULL) {
    return;
  }
  // Draw background
  draw_sprite(sm->grid_background, sm->x_initial_grid+30, sm->y_initial_grid+50);

  // Draw walls
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {

      draw_wall(sm->wall_matrix[j][i], sm->x_initial_grid, sm->y_initial_grid, sm->grid_square_width);
      draw_bomb(sm->bomb_matrix[j][i], sm->x_initial_grid, sm->y_initial_grid, sm->grid_square_width);
      draw_explosion(sm->explosion_matrix[j][i], sm->x_initial_grid, sm->y_initial_grid, sm->grid_square_width);
    }
    if ( get_player_Ypos(sm->player1)/sm->grid_square_width == i) {
      draw_player(sm->player1, sm->x_initial_grid, sm->y_initial_grid);
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

bool process_input_kbd(SingleMode *sm, bool* keys) {
  if (sm == NULL) {
    return true;
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
  if (keys[4]){ 
    return true; // Opens Menu
  }
  return false; // Continue game
}


bool process_input_mouse(SingleMode *sm, Cursor *c) {
  if (sm == NULL || c == NULL) {
    return true;
  }
  
  // Rigth mouse button pressed
  if (get_cursor_button_pressed(c, 2)) {
    

    uint16_t grid_x =  (get_player_Xpos(sm->player1)+30) / sm->grid_square_width;
    uint16_t grid_y =  (get_player_Ypos(sm->player1)+30) / sm->grid_square_width;

    if (!is_bomb_active(sm->bomb_matrix[grid_x][grid_y])) {
      set_bomb_active(sm->bomb_matrix[grid_x][grid_y], true); // Activate the bomb
    }
  }
  // Left mouse button pressed
  if (get_cursor_button_pressed(c, 0)) {
    return true; // Exit game
  }

  return false; // Continue game
}

bool process_menu_input(Cursor *cursor) {
  if (get_cursor_button_pressed(cursor, 0)) { // Left mouse button pressed
    uint16_t cursor_x = get_cursor_Xpos(cursor);
    uint16_t cursor_y = get_cursor_Ypos(cursor);

    // Check if the cursor is over the "Resume" button
    if (cursor_x >= 100 && cursor_x <= 300 && cursor_y >= 100 && cursor_y <= 150) {
      current_state = GAME_PLAYING; // Resume the game
      return false; // Continue the game
    }

    // Check if the cursor is over the "Exit" button
    if (cursor_x >= 100 && cursor_x <= 300 && cursor_y >= 200 && cursor_y <= 250) {
      return true; // Exit the game
    }
  }
  return false: // Continue the game
}

bool check_bomb_exploded(SingleMode *sm) {
  if (sm == NULL) {
    return false;
  }

  for (int i = 1; i < GRID_HEIGHT-1; i++) {
    for (int j = 1; j < GRID_WIDTH-1; j++) {
      if (is_bomb_exploded(sm->bomb_matrix[j][i])) {

        //calculate the grids positions of the 2 diagonal corners of the player
        uint16_t grid_x_top_left = get_player_Xpos(sm->player1) / sm->grid_square_width;
        uint16_t grid_y_top_left = get_player_Ypos(sm->player1) / sm->grid_square_width;
        
        uint16_t grid_x_bottom_right = (get_player_Xpos(sm->player1) + (sm->grid_square_width-1)) / sm->grid_square_width;
        uint16_t grid_y_bottom_right = (get_player_Ypos(sm->player1) + (sm->grid_square_width-1)) / sm->grid_square_width;

        if (grid_x_top_left == j && grid_y_top_left == i) {
          return true; // Player is in the same position as the bomb, exit game
        }else if( grid_x_top_left == j+1 && grid_y_top_left == i) {
          return true; // In the right square
        }else if( grid_x_top_left == j && grid_y_top_left == i+1) {
          return true; // In the bottom square
        }else if( grid_x_top_left == j-1 && grid_y_top_left == i) {
          return true; // In the left square
        }else if( grid_x_top_left == j && grid_y_top_left == i-1) {
          return true; // In the top square
        }else if( grid_x_bottom_right == j && grid_y_bottom_right == i) {
          return true; // Player is in the same position as the bomb, exit game
        }else if( grid_x_bottom_right == j+1 && grid_y_bottom_right == i) {
          return true; // In the right square
        }else if( grid_x_bottom_right == j && grid_y_bottom_right == i+1) {
          return true; // In the bottom square
        }else if( grid_x_bottom_right == j-1 && grid_y_bottom_right == i) {
          return true; // In the left square
        }else if( grid_x_bottom_right == j && grid_y_bottom_right == i-1) {
          return true; // In the top square
        }

        
        if ( is_wall_destroyable(sm->wall_matrix[j+1][i]) && is_wall_active(sm->wall_matrix[j+1][i])) {
          set_wall_active(sm->wall_matrix[j+1][i], false); // Deactivate the wall, bomb destroyed it
        }
        if ( is_wall_destroyable(sm->wall_matrix[j][i+1]) && is_wall_active(sm->wall_matrix[j][i+1])) {
          set_wall_active(sm->wall_matrix[j][i+1], false); // Deactivate the wall, bomb destroyed it
        }
        if ( is_wall_destroyable(sm->wall_matrix[j-1][i]) && is_wall_active(sm->wall_matrix[j-1][i])) {
          set_wall_active(sm->wall_matrix[j-1][i], false); // Deactivate the wall, bomb destroyed it
        }
        if ( is_wall_destroyable(sm->wall_matrix[j][i-1]) && is_wall_active(sm->wall_matrix[j][i-1])) {
          set_wall_active(sm->wall_matrix[j][i-1], false); // Deactivate the wall, bomb destroyed it
        }

        set_explosion_active(sm->explosion_matrix[j][i], true); // Activate the explosion, in the bomb position
        if (is_wall_destroyable(sm->wall_matrix[j+1][i])) {
          set_explosion_active(sm->explosion_matrix[j+1][i], true); // Activate the explosion, if it is not a solid wall
        }
        if (is_wall_destroyable(sm->wall_matrix[j][i+1])) {
          set_explosion_active(sm->explosion_matrix[j][i+1], true); // Activate the explosion, if it is not a solid wall
        }
        if (is_wall_destroyable(sm->wall_matrix[j-1][i])) {
          set_explosion_active(sm->explosion_matrix[j-1][i], true); // Activate the explosion, if it is not a solid wall
        }
        if (is_wall_destroyable(sm->wall_matrix[j][i-1])) {
          set_explosion_active(sm->explosion_matrix[j][i-1], true); // Activate the explosion, if it is not a solid wall
        }
      }
    }
  }
  return false;
}

