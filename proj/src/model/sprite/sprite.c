#include "sprite.h"

struct sprite_imp {
  uint16_t width, height; // dimensions
  uint8_t *map; // the pixmap
};

uint16_t get_sprite_width(Sprite *sp) {
  if (sp == NULL) {
    return 0;
  }
  return sp->width;
}

uint16_t get_sprite_height(Sprite *sp) {
  if (sp == NULL) {
    return 0;
  }
  return sp->height;
}

Sprite *create_sprite(const xpm_map_t pic) {
  //allocate space for the "object"
  Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
  xpm_image_t img;
  if( sp == NULL ){
    return NULL;
  }

  // read the sprite pixmap

  sp->map = xpm_load(pic, XPM_INDEXED, &img);

  if( sp->map == NULL ) {
    free(sp);
    return NULL;
  }

  sp->width = img.width; 
  sp->height=img.height;
  return sp;
}

void destroy_sprite(Sprite *sp) {
  if( sp == NULL ){
    return;
  }
  if( sp ->map ){
    free(sp->map);
  }

  free(sp);
  sp = NULL; 
}

void draw_sprite(Sprite *sp, uint16_t x, uint16_t y) {
  if (sp == NULL) {
    return;
  }

  // Draw the sprite at the specified coordinates
  vg_draw_xpm(sp->map, x, y, sp->width, sp->height);
}
