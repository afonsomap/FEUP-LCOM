#include "sprite.h"

struct sprite_imp {
  uint16_t width, height; // dimensions
  uint8_t *map; // the pixmap
  SpriteType type; // type of sprite (FULL_IMAGE, BY_LINE, NORMAL)
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

SpriteType get_sprite_type(Sprite *sp) {
  if (sp == NULL) {
    return BY_PIXEL; // Default type if sprite is NULL
  }
  return sp->type;
}

Sprite *create_sprite(const xpm_map_t pic, SpriteType type) {
  //allocate space for the "object"
  Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
  xpm_image_t img;
  if( sp == NULL ){
    return NULL;
  }

  // read the sprite pixmap

  sp->map = xpm_load(pic, XPM_8_8_8, &img);

  if( sp->map == NULL ) {
    free(sp);
    return NULL;
  }

  sp->width = img.width; 
  sp->height=img.height;
  sp->type = type;
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

  if (sp->type == BY_LINE) {
    // If the sprite is of type BY_LINE, we can use a more efficient drawing method
    if (vg_draw_xpm_by_line(sp->map, x, y, sp->width, sp->height) != 0) {
      return; // Handle error if needed
    }
  } else if (sp->type == FULL_IMAGE) {
    // If the sprite is of type FULL_IMAGE, we can use a different drawing method
    if (vg_draw_xpm_by_image(sp->map, x, y, sp->width, sp->height) != 0) {
      return; // Handle error if needed
    }
  }
  else 
    vg_draw_xpm(sp->map, x, y, sp->width, sp->height);
}
