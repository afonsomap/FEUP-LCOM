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
};

SpriteLoader* load_sprites() {
  SpriteLoader *loader = (SpriteLoader *) malloc(sizeof(SpriteLoader));
  if (loader == NULL) {
    return NULL;
  }

  // Load player sprites
  loader->player1_standing = create_sprite((xpm_map_t)player_xpm);
  loader->player2_standing = create_sprite((xpm_map_t)player_xpm);
  loader->player1_left = create_anim_sprite(2, (xpm_map_t)player_xpm, (xpm_map_t)player_xpm);
  loader->player1_right = create_anim_sprite(2, (xpm_map_t)player_xpm, (xpm_map_t)player_xpm);
  loader->player1_up = create_anim_sprite(2, (xpm_map_t)player_xpm, (xpm_map_t)player_xpm);
  loader->player1_down = create_anim_sprite(2, (xpm_map_t)player_xpm, (xpm_map_t)player_xpm);
  loader->player2_left = create_anim_sprite(2, (xpm_map_t)player_xpm, (xpm_map_t)player_xpm);
  loader->player2_right = create_anim_sprite(2, (xpm_map_t)player_xpm, (xpm_map_t)player_xpm);
  loader->player2_up = create_anim_sprite(2, (xpm_map_t)player_xpm, (xpm_map_t)player_xpm);
  loader->player2_down = create_anim_sprite(2, (xpm_map_t)player_xpm, (xpm_map_t)player_xpm);
  loader->bomb = create_anim_sprite(2, (xpm_map_t)bomb_xpm, (xpm_map_t)bomb_xpm);
  loader->wall = create_sprite( (xpm_map_t)wall_xpm);
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

