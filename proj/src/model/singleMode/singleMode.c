#include "singleMode.h"


#define GRID_WIDTH 17
#define GRID_HEIGHT 15

struct singleMode_imp {
  Player *player1;
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
};


SingleMode *create_singleMode(SpriteLoader *loader) {
  SingleMode *sm = (SingleMode *) malloc(sizeof(SingleMode));
  if (sm == NULL) {
    return NULL;
  }
  
  sm->x_initial_grid = 208; // Initialize grid position
  sm->y_initial_grid = 52; // Initialize grid position
  sm->grid_square_width = get_sprite_width(get_wall(loader)); // Get the width of the grid square
  sm->grid_background = get_grid_background(loader); // Get the background sprite
  sm->game_background = get_game_background(loader); // Get the game background sprite

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

  sm->bomb_options = create_bomb_options(get_bomb_options(loader), get_selected_options(loader));
  sm->player1_bomb_option = NORMAL;

  return sm;
}

void destroy_singleMode(SingleMode *sm) {
  if (sm == NULL) {
    return;
  }

  // Destroy player
  destroy_player(sm->player1);

  // Destroy walls, bombs, and explosions
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      destroy_wall(sm->wall_matrix[j][i]);
      destroy_bomb(sm->bomb_matrix[j][i]);
      destroy_explosion(sm->explosion_matrix[j][i]);
    }
  }

  // Destroy bomb options
  destroy_bomb_options(sm->bomb_options);

  free(sm);
}

void draw_singleMode(SingleMode *sm) {
  if (sm == NULL) {
    return;
  }
  
  // Draw background
  draw_sprite(sm->grid_background, sm->x_initial_grid+33, sm->y_initial_grid+50);

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

  draw_bomb_options(sm->bomb_options, sm->player1_bomb_option);
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


// 0 Continue game
// 1 Goes back to menu
int process_single_mode_kbd(SingleMode *sm, bool* keys) {
  if (sm == NULL) {
    return 1; // Go back to menu
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
    return 1; // Goes back to menu
  }
  return 0; // Continue game, no action
}

// 0 Continue game
// 1 Goes back to menu
int process_single_mode_mouse(SingleMode *sm, Cursor *c) {
  if (sm == NULL || c == NULL) {
    return 1; // Goes back to menu
  }

  decrease_time_availability(sm->bomb_options); // Decrease the time of the bomb options
  printf("current unavailability array: [");
  for (int i = 0; i < sm->bomb_options->number_of_options; i++) {
      printf("%d", sm->bomb_options->availability_counter[i]);
      if (i < sm->bomb_options->number_of_options - 1) {
          printf(", ");
      }
  }
  printf("]\n");

  // Rigth mouse button pressed
  if (get_cursor_button_pressed(c, 2)) {
    

    uint16_t grid_x =  (get_player_Xpos(sm->player1)+30) / sm->grid_square_width;
    uint16_t grid_y =  (get_player_Ypos(sm->player1)+30) / sm->grid_square_width;

    if (!is_bomb_active(sm->bomb_matrix[grid_x][grid_y])) {
      printf("Selected bomb option: %d\n", sm->player1_bomb_option);
      if (!isBombAvailable(sm->bomb_options, sm->player1_bomb_option)) {
        printf("Bomb option %d is not available\n", sm->player1_bomb_option);
        return 0; // Continue game, no action
      }
      else {
        printf("Bomb option %d is available\n", sm->player1_bomb_option);
        set_bomb_active(sm->bomb_matrix[grid_x][grid_y], true, sm->player1_bomb_option); // Activate the bomb
        set_bomb_unavailable(sm->bomb_options, sm->player1_bomb_option); // Set the bomb option as unavailable
      }
    }
  }
  // Left mouse button pressed
  if (get_cursor_button_pressed(c, 0)) {
    
    // Check if the cursor is within the bomb options x range
    if ( get_cursor_Xpos(c) > get_options_x_initial(sm->bomb_options) && get_cursor_Xpos(c) < get_options_x_final(sm->bomb_options)) {

      if (get_cursor_Ypos(c) > get_options_y_initial(sm->bomb_options, 0) && get_cursor_Ypos(c) < get_options_y_final(sm->bomb_options, 0)) {
        sm->player1_bomb_option = NORMAL; // Set the bomb option for player 1
      }else if (get_cursor_Ypos(c) > get_options_y_initial(sm->bomb_options, 1) && get_cursor_Ypos(c) < get_options_y_final(sm->bomb_options, 1)) {
        sm->player1_bomb_option = FULL_LINE; // Set the bomb option for player 1
      }else if (get_cursor_Ypos(c) > get_options_y_initial(sm->bomb_options, 2) && get_cursor_Ypos(c) < get_options_y_final(sm->bomb_options, 2)) {
        sm->player1_bomb_option = CONSTRUCTIVE; // Set the bomb option for player 1
      }
    }  
  }

  return 0; // Continue game
  
}

int process_bomb_spawning(SingleMode *sm) {
  if (sm == NULL) {
    return 1; // Go back to menu
  }

  // Check if the bomb options are available
  if (is_spawning(sm->bomb_options)) {
    uint16_t randomX = (rand() % 16) + 1; 
    uint16_t randomY = (rand() % 14) + 1; 
    while (is_wall_active(sm->wall_matrix[randomX][randomY]) || is_bomb_active(sm->bomb_matrix[randomX][randomY])) {
      randomX = (rand() % 16) + 1; // Generate a random X coordinate
      randomY = (rand() % 14) + 1; // Generate a random Y coordinate
    }
    BombType random_bomb = get_random_bomb(); 
    set_bomb_active(sm->bomb_matrix[randomX][randomY], true, random_bomb); // Activate the bomb
    set_spawn_rate(sm->bomb_options); // Reset the spawn rate
  }
  else {
    decrease_time_spawning(sm->bomb_options); // Decrease the time of the bomb spawning
  }

  return 0; // Continue game
}

// 0 Continue game
// 1 Goes back to menu
int check_bomb_exploded(SingleMode *sm) {
  if (sm == NULL) {
    return 1;
  }

  for (int i = 1; i < GRID_HEIGHT-1; i++) {
    for (int j = 1; j < GRID_WIDTH-1; j++) {
      if (is_bomb_exploded(sm->bomb_matrix[j][i])) {

        //calculate the grids positions of the 2 diagonal corners of the player
        uint16_t grid_x_top_left = get_player_Xpos(sm->player1) / sm->grid_square_width;
        uint16_t grid_y_top_left = get_player_Ypos(sm->player1) / sm->grid_square_width;
        
        uint16_t grid_x_bottom_right = (get_player_Xpos(sm->player1) + (sm->grid_square_width-1)) / sm->grid_square_width;
        uint16_t grid_y_bottom_right = (get_player_Ypos(sm->player1) + (sm->grid_square_width-1)) / sm->grid_square_width;

        BombType bomb_type = get_bomb_type(sm->bomb_matrix[j][i]);
        if (bomb_type == NORMAL) {
          if (grid_x_top_left == j && grid_y_top_left == i) {
            return 1; // Player is in the same position as the bomb, go to menu
          }else if( grid_x_top_left == j+1 && grid_y_top_left == i) {
            return 1; // In the right square
          }else if( grid_x_top_left == j && grid_y_top_left == i+1) {
            return 1; // In the bottom square
          }else if( grid_x_top_left == j-1 && grid_y_top_left == i) {
            return 1; // In the left square
          }else if( grid_x_top_left == j && grid_y_top_left == i-1) {
            return 1; // In the top square
          }else if( grid_x_bottom_right == j && grid_y_bottom_right == i) {
            return 1; // Player is in the same position as the bomb, exit game
          }else if( grid_x_bottom_right == j+1 && grid_y_bottom_right == i) {
            return 1; // In the right square
          }else if( grid_x_bottom_right == j && grid_y_bottom_right == i+1) {
            return 1; // In the bottom square
          }else if( grid_x_bottom_right == j-1 && grid_y_bottom_right == i) {
            return 1; // In the left square
          }else if( grid_x_bottom_right == j && grid_y_bottom_right == i-1) {
            return 1; // In the top square
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

        }else if ( bomb_type == FULL_LINE) {

          bool up_collision = false;
          bool down_collision = false;
          bool left_collision = false;
          bool right_collision = false;

          // It is done in this way to check the closer positions to the explosion first
          for ( int k = 0; k < GRID_WIDTH - 2; k++) { // The -2 is to avoid the walls at the borders

            if ( j + k < GRID_WIDTH - 1 &&  !right_collision) { // Right direction

              if (grid_x_top_left == j + k && grid_y_top_left == i) {
                return 1; 
              }else if( grid_x_bottom_right == j + k && grid_y_bottom_right == i) {
                return 1;
              }

              if ( is_wall_destroyable(sm->wall_matrix[j + k][i])) {

                set_explosion_active(sm->explosion_matrix[j + k][i], true); // Activate the explosion

                if ( is_wall_active(sm->wall_matrix[j + k][i]) ){
                  set_wall_active(sm->wall_matrix[j + k][i], false); // Deactivate the wall, bomb destroyed
                  right_collision = true;
                }
              }else {
                right_collision = true; // It is a solid wall, stop the explosion in this direction
              }

            }

            if ( j - k > 0 && !left_collision) { // Left direction

              if (grid_x_top_left == j - k && grid_y_top_left == i) {
                return 1; 
              }else if( grid_x_bottom_right == j - k && grid_y_bottom_right == i) {
                return 1;
              }

              if ( is_wall_destroyable(sm->wall_matrix[j - k][i])) {

                set_explosion_active(sm->explosion_matrix[j - k][i], true); // Activate the explosion

                if ( is_wall_active(sm->wall_matrix[j - k][i]) ){
                  set_wall_active(sm->wall_matrix[j - k][i], false); // Deactivate the wall, bomb destroyed
                  left_collision = true;
                }
              }else {
                left_collision = true; // It is a solid wall, stop the explosion in this direction
              }
              
            }
            if ( i + k < GRID_HEIGHT - 1 && !down_collision) { // Down direction

              if (grid_x_top_left == j && grid_y_top_left == i + k) {
                return 1; 
              }else if( grid_x_bottom_right == j && grid_y_bottom_right == i + k) {
                return 1;
              }

              if ( is_wall_destroyable(sm->wall_matrix[j][i + k])) {

                set_explosion_active(sm->explosion_matrix[j][i + k], true); // Activate the explosion

                if ( is_wall_active(sm->wall_matrix[j][i + k]) ){
                  set_wall_active(sm->wall_matrix[j][i + k], false); // Deactivate the wall, bomb destroyed
                  down_collision = true;
                }
              }else {
                down_collision = true; // It is a solid wall, stop the explosion in this direction
              }
              
            }
            if ( i - k > 0 && !up_collision) { // Up direction

              if (grid_x_top_left == j && grid_y_top_left == i - k) {
                return 1; 
              }else if( grid_x_bottom_right == j && grid_y_bottom_right == i - k) {
                return 1;
              }

              if ( is_wall_destroyable(sm->wall_matrix[j][i - k])) {

                set_explosion_active(sm->explosion_matrix[j][i - k], true); // Activate the explosion

                if ( is_wall_active(sm->wall_matrix[j][i - k]) ){
                  set_wall_active(sm->wall_matrix[j][i - k], false); // Deactivate the wall, bomb destroyed
                  up_collision = true;
                }
              }else {
                up_collision = true; // It is a solid wall, stop the explosion in this direction
              }
            }

            if ( up_collision && down_collision && left_collision && right_collision) {
              break;
            }
          }

        }else if ( bomb_type == CONSTRUCTIVE) {

          if (grid_x_top_left == j && grid_y_top_left == i) {
            return 1; // Player is in the same position as the bomb, go to menu
          }else if( grid_x_top_left == j+1 && grid_y_top_left == i) {
            return 1; // In the right square
          }else if( grid_x_top_left == j && grid_y_top_left == i+1) {
            return 1; // In the bottom square
          }else if( grid_x_top_left == j-1 && grid_y_top_left == i) {
            return 1; // In the left square
          }else if( grid_x_top_left == j && grid_y_top_left == i-1) {
            return 1; // In the top square
          }else if( grid_x_bottom_right == j && grid_y_bottom_right == i) {
            return 1; // Player is in the same position as the bomb, exit game
          }else if( grid_x_bottom_right == j+1 && grid_y_bottom_right == i) {
            return 1; // In the right square
          }else if( grid_x_bottom_right == j && grid_y_bottom_right == i+1) {
            return 1; // In the bottom square
          }else if( grid_x_bottom_right == j-1 && grid_y_bottom_right == i) {
            return 1; // In the left square
          }else if( grid_x_bottom_right == j && grid_y_bottom_right == i-1) {
            return 1; // In the top square
          }
          
          if ( is_wall_destroyable(sm->wall_matrix[j][i]) && !is_wall_active(sm->wall_matrix[j][i])) {
            set_wall_active(sm->wall_matrix[j][i], true); // Activate the wall
            set_explosion_active(sm->explosion_matrix[j][i], true); // Activate the explosion,
          }
          if ( is_wall_destroyable(sm->wall_matrix[j+1][i]) && !is_wall_active(sm->wall_matrix[j+1][i])) {
            set_wall_active(sm->wall_matrix[j+1][i], true); // Activate the wall
            set_explosion_active(sm->explosion_matrix[j+1][i], true); // Activate the explosion
          }
          if ( is_wall_destroyable(sm->wall_matrix[j][i+1]) && !is_wall_active(sm->wall_matrix[j][i+1])) {
            set_wall_active(sm->wall_matrix[j][i+1], true); // Activate the wall
            set_explosion_active(sm->explosion_matrix[j][i+1], true); // Activate the explosion
          }
          if ( is_wall_destroyable(sm->wall_matrix[j-1][i]) && !is_wall_active(sm->wall_matrix[j-1][i])) {
            set_wall_active(sm->wall_matrix[j-1][i], true); // ACtivate the wall
            set_explosion_active(sm->explosion_matrix[j-1][i], true); // Activate the explosion
          }
          if ( is_wall_destroyable(sm->wall_matrix[j][i-1]) && !is_wall_active(sm->wall_matrix[j][i-1])) {
            set_wall_active(sm->wall_matrix[j][i-1], true); // Activate the wall
            set_explosion_active(sm->explosion_matrix[j][i-1], true); // Activate the explosion
          }
        }    
      }
    }
  }
  return 0;
}

