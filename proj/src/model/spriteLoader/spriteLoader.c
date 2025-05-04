#include "spriteLoader.h"

struct sprite_loader_imp {
  Sprite *player1_standing;
  AnimSprite *player1_left;
  AnimSprite *player1_right;
  AnimSprite *player1_up;
  AnimSprite *player1_down;
  Sprite *player2_standing;
  AnimSprite *player2_left;
  AnimSprite *player2_right;
  AnimSprite *player2_up;
  AnimSprite *player2_down;
  AnimSprite *bomb;
  Sprite *wall;
  Sprite *solid_wall;
  Sprite *grid_background;
};

SpriteLoader* load_sprites() {
  SpriteLoader *loader = (SpriteLoader *) malloc(sizeof(SpriteLoader));
  if (loader == NULL) {
    return NULL;
  }

  // Load player sprites
  loader->player1_standing = create_sprite((xpm_map_t)p1_front_1);
  loader->player2_standing = create_sprite((xpm_map_t)p1_front_1);
  loader->player1_left = create_anim_sprite(2, 8, (xpm_map_t)p1_left_1, (xpm_map_t)p1_left_2,
                                           (xpm_map_t)p1_left_3, (xpm_map_t)p1_left_2,
                                           (xpm_map_t)p1_left_1, (xpm_map_t)p1_left_4,
                                           (xpm_map_t)p1_left_5, (xpm_map_t)p1_left_4);
                                          
  loader->player1_right = create_anim_sprite(2, 8, (xpm_map_t)p1_right_1, (xpm_map_t)p1_right_2,
                                            (xpm_map_t)p1_right_3, (xpm_map_t)p1_right_2,
                                            (xpm_map_t)p1_right_1, (xpm_map_t)p1_right_4,
                                            (xpm_map_t)p1_right_5, (xpm_map_t)p1_right_4);

  loader->player1_up = create_anim_sprite(2, 8, (xpm_map_t)p1_back_1, (xpm_map_t)p1_back_2,
                                          (xpm_map_t)p1_back_3, (xpm_map_t)p1_back_2,
                                          (xpm_map_t)p1_back_1, (xpm_map_t)p1_back_4,
                                          (xpm_map_t)p1_back_5, (xpm_map_t)p1_back_4);  

  loader->player1_down = create_anim_sprite(2, 8, (xpm_map_t)p1_front_1, (xpm_map_t)p1_front_2,
                                            (xpm_map_t)p1_front_3, (xpm_map_t)p1_front_2,
                                            (xpm_map_t)p1_front_1, (xpm_map_t)p1_front_4,
                                            (xpm_map_t)p1_front_5, (xpm_map_t)p1_front_4);
      
  // Load player 2 sprites
  loader->player2_left = create_anim_sprite(2, 8, (xpm_map_t)p1_left_1, (xpm_map_t)p1_left_2,
                                           (xpm_map_t)p1_left_3, (xpm_map_t)p1_left_2,
                                           (xpm_map_t)p1_left_1, (xpm_map_t)p1_left_4,
                                           (xpm_map_t)p1_left_5, (xpm_map_t)p1_left_4);
                                          
  loader->player2_right = create_anim_sprite(2, 8, (xpm_map_t)p1_right_1, (xpm_map_t)p1_right_2,
                                            (xpm_map_t)p1_right_3, (xpm_map_t)p1_right_2,
                                            (xpm_map_t)p1_right_1, (xpm_map_t)p1_right_4,
                                            (xpm_map_t)p1_right_5, (xpm_map_t)p1_right_4);

  loader->player2_up = create_anim_sprite(2, 8, (xpm_map_t)p1_back_1, (xpm_map_t)p1_back_2,
                                          (xpm_map_t)p1_back_3, (xpm_map_t)p1_back_2,
                                          (xpm_map_t)p1_back_1, (xpm_map_t)p1_back_4,
                                          (xpm_map_t)p1_back_5, (xpm_map_t)p1_back_4);  

  loader->player2_down = create_anim_sprite(2, 8, (xpm_map_t)p1_front_1, (xpm_map_t)p1_front_2,
                                            (xpm_map_t)p1_front_3, (xpm_map_t)p1_front_2,
                                            (xpm_map_t)p1_front_1, (xpm_map_t)p1_front_4,
                                            (xpm_map_t)p1_front_5, (xpm_map_t)p1_front_4);
  // Load bomb and wall sprites
  loader->bomb = create_anim_sprite(12, 5, (xpm_map_t)bomb_xpm_1, (xpm_map_t)bomb_xpm_2, 
                                    (xpm_map_t)bomb_xpm_3, (xpm_map_t)bomb_xpm_4,
                                    (xpm_map_t)bomb_xpm_5);
  loader->wall = create_sprite( (xpm_map_t)wall_xpm);
  loader->solid_wall = create_sprite( (xpm_map_t)solid_wall_xpm);
  loader->grid_background = create_sprite((xpm_map_t)grid_background);
  return loader;
}

void destroy_sprites(SpriteLoader *loader) {
  if (loader == NULL) {
    return;
  }

  destroy_anim_sprite(loader->player1_left);
  destroy_anim_sprite(loader->player1_right);
  destroy_anim_sprite(loader->player1_up);
  destroy_anim_sprite(loader->player1_down);
  destroy_anim_sprite(loader->player2_left);
  destroy_anim_sprite(loader->player2_right);
  destroy_anim_sprite(loader->player2_up);
  destroy_anim_sprite(loader->player2_down);
  destroy_anim_sprite(loader->bomb);
  destroy_sprite(loader->wall);
  destroy_sprite(loader->solid_wall);
  destroy_sprite(loader->grid_background);

  free(loader);
}

Sprite* get_player1_standing(SpriteLoader *loader) {
  return loader->player1_standing;
}

Sprite* get_player2_standing(SpriteLoader *loader) {
  return loader->player2_standing;
}

AnimSprite* get_player1_left(SpriteLoader *loader) {
  return loader->player1_left;
}
AnimSprite* get_player1_right(SpriteLoader *loader) {
  return loader->player1_right;
}
AnimSprite* get_player1_up(SpriteLoader *loader) {
  return loader->player1_up;
}
AnimSprite* get_player1_down(SpriteLoader *loader) {
  return loader->player1_down;
}
AnimSprite* get_player2_left(SpriteLoader *loader) {
  return loader->player2_left;
}
AnimSprite* get_player2_right(SpriteLoader *loader) {
  return loader->player2_right;
}
AnimSprite* get_player2_up(SpriteLoader *loader) {
  return loader->player2_up;
}
AnimSprite* get_player2_down(SpriteLoader *loader) {
  return loader->player2_down;
}
AnimSprite* get_bomb(SpriteLoader *loader) {
  return loader->bomb;
}
Sprite* get_wall(SpriteLoader *loader) {
  return loader->wall;
}
Sprite* get_solid_wall(SpriteLoader *loader) {
  return loader->solid_wall;
}
Sprite* get_grid_background(SpriteLoader *loader) {
  return loader->grid_background;
}

