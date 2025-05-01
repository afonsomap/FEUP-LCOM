#ifndef _SPRITELOADER_H_
#define _SPRITELOADER_H_

#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "sprite.h"
#include "animatedSprite.h"
#include "images/player.xpm"
#include "images/bomb.xpm"
#include "images/wall.xpm"


struct sprite_loader_imp;
typedef struct sprite_loader_imp SpriteLoader;

SpriteLoader* load_sprites();

void destroy_sprites(SpriteLoader *loader);

Sprite* get_player1_standing(SpriteLoader *loader);
Sprite* get_player2_standing(SpriteLoader *loader);
AnimSprite* get_player1_left(SpriteLoader *loader);
AnimSprite* get_player1_right(SpriteLoader *loader);
AnimSprite* get_player1_up(SpriteLoader *loader);
AnimSprite* get_player1_down(SpriteLoader *loader);
AnimSprite* get_player2_left(SpriteLoader *loader);
AnimSprite* get_player2_right(SpriteLoader *loader);
AnimSprite* get_player2_up(SpriteLoader *loader);
AnimSprite* get_player2_down(SpriteLoader *loader);
AnimSprite* get_bomb(SpriteLoader *loader);
Sprite* get_wall(SpriteLoader *loader);

#endif
