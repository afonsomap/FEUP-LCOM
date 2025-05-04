#include "cursor.h"
#include "mouse.h"

struct cursor {
  uint8_t x, y; // position in the game grid
  AnimSprite* img; // pointer to the animated sprite
  bool visible; // whether the cursor is visible
  uint8_t grid_width, grid_height; // dimensions of the game grid
  uint8_t initial_x, initial_y; // initial position of the cursor
  enum { ACTIVE, INACTIVE, SELECTED } state; // state of the cursor
  void* interacting_object; // pointer to the object being interacted with
};

uint8_t get_cursor_Xpos(Cursor *c) {
  if (c == NULL) {
    return 0;
  }
  return c->x;
}

uint8_t get_cursor_Ypos(Cursor *c) {
  if (c == NULL) {
    return 0;
  }
  return c->y;
}

Cursor *create_cursor(uint8_t x, uint8_t y, AnimSprite *img, uint8_t grid_width, uint8_t grid_height) {
  Cursor *c = malloc(sizeof(Cursor));
  if (c == NULL) {
    return NULL;
  }
  c->x = x;
  c->y = y;
  c->img = img;
  c->visible = true;
  c->grid_width = grid_width;
  c->grid_height = grid_height;
  c->state = ACTIVE; 
  c->interacting_object = NULL; 
  c->current_frame = 0;
  c->current_image = 0;

  return c;
}

void destroy_cursor(Cursor *c) {
  if (c == NULL) return;
  free(c);
}

void update_cursor_with_mouse(Cursor *cursor, struct packet *mouse_packet) {
  if (cursor == NULL || mouse_packet == NULL) return;

  // Ignore overflow
  if (mouse_packet->x_ov || mouse_packet->y_ov) return;

  int16_t new_x = cursor->x + mouse_packet->delta_x;
  int16_t new_y = cursor->y - mouse_packet->delta_y; 

  if (new_x >= 0 && new_x < cursor->grid_width) cursor->x = new_x;
  if (new_y >= 0 && new_y < cursor->grid_height) cursor->y = new_y;
}

void draw_cursor(Cursor *c) {
  if (c == NULL || !c->visible) return;

  uint16_t x = c->x_initial_grid + c->x * get_anim_sprite_width(c->img);
  uint16_t y = c->y_initial_grid + c->y * get_anim_sprite_height(c->img);

  draw_anim_sprite(c->img, x, y, c->current_image);
  update_cursor_with_mouse(c, get_packet());
}