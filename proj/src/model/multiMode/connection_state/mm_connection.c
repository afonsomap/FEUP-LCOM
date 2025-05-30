#include "mm_connection.h"  

struct mm_connection_imp {
  SpriteLoader *loader; // Pointer to the sprite loader
  Sprite *background; // Background image for the connection state
  Sprite *leave_button;
  uint16_t leave_button_x; // X coordinate of the leave button
  uint16_t leave_button_y; // Y coordinate of the leave button
  bool received_hello;
  int time_until_failure; // Time until the connection fails
};

MmConnection *create_mm_connection(SpriteLoader *loader) {
  MmConnection *mm_connection = (MmConnection *) malloc(sizeof(MmConnection));
  if (mm_connection == NULL) {
    return NULL;
  }

  sp_clear_buffers(); // Clear the serial port buffer
  mm_connection->loader = loader;
  mm_connection->background = get_menu_background(loader);
  mm_connection->leave_button = get_exit_button(loader);
  mm_connection->received_hello = false;
  mm_connection->time_until_failure = 300; //10 seconds until failure
  return mm_connection;
}

void destroy_mm_connection(MmConnection *mm_connection) {
  if (mm_connection == NULL) {
    return;
  }
  free(mm_connection);
}

void draw_mm_connection(MmConnection *mm_connection) {
  if (mm_connection == NULL) {
    return;
  }
  
  draw_sprite(mm_connection->background, 0, 0);
  draw_sprite(mm_connection->leave_button, mm_connection->leave_button_x, mm_connection->leave_button_y);
}

int process_mm_connection_mouse(MmConnection *mm_connection, Cursor *c) {
  if (mm_connection == NULL || c == NULL) {
    return 1; // Go back to menu
  }

  if (get_cursor_button_pressed(c, 0)) { // Left mouse button pressed
    uint16_t x = get_cursor_Xpos(c);
    uint16_t y = get_cursor_Ypos(c);

    if (x >= mm_connection->leave_button_x && x <= mm_connection->leave_button_x + get_sprite_width(mm_connection->leave_button) && 
        y >= mm_connection->leave_button_y && y <= mm_connection->leave_button_y + get_sprite_height(mm_connection->leave_button)) {
      return 1; // Leave game 
    }
  }

  return 0; // Continue connection state
}

int process_mm_connection_timer(MmConnection *mm_connection) {
  if (mm_connection == NULL || mm_connection->time_until_failure <= 0) {
    return 1; // Go back to menu
  }

  if (!mm_connection->received_hello) {
    send_byte(0xFF);
  }
  mm_connection->time_until_failure--;
  return 0; 
}

int process_mm_connection_sp(MmConnection *mm_connection, uint8_t byte) {
  if (mm_connection == NULL) {
    return -1; // Go back to menu
  }

  if (byte == 0xFF) {
    mm_connection->received_hello = true; 
    send_byte(0xAA); 
    return 1; // Player 1
  }else if(byte == 0xAA) {
    return 2; // Player 2
  }
  return 0; 
}

