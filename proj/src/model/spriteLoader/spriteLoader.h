#ifndef _SPRITELOADER_H_
#define _SPRITELOADER_H_

#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "sprite.h"
#include "animatedSprite.h"

#include "images/player1/back/p1_back0.xpm"
#include "images/player1/back/p1_back1.xpm"
#include "images/player1/back/p1_back2.xpm"
#include "images/player1/back/p1_back3.xpm"
#include "images/player1/back/p1_back4.xpm"
#include "images/player1/back/p1_back5.xpm"
#include "images/player1/back/p1_back6.xpm"
#include "images/player1/back/p1_back7.xpm"
#include "images/player1/back/p1_back8.xpm"
#include "images/player1/back/p1_back9.xpm"

#include "images/player1/front/p1_front0.xpm"
#include "images/player1/front/p1_front1.xpm"
#include "images/player1/front/p1_front2.xpm" 
#include "images/player1/front/p1_front3.xpm"
#include "images/player1/front/p1_front4.xpm"
#include "images/player1/front/p1_front5.xpm"
#include "images/player1/front/p1_front6.xpm"
#include "images/player1/front/p1_front7.xpm"
#include "images/player1/front/p1_front8.xpm"
#include "images/player1/front/p1_front9.xpm"

#include "images/player1/left/p1_left0.xpm"
#include "images/player1/left/p1_left1.xpm"
#include "images/player1/left/p1_left2.xpm"
#include "images/player1/left/p1_left3.xpm"
#include "images/player1/left/p1_left4.xpm"
#include "images/player1/left/p1_left5.xpm"
#include "images/player1/left/p1_left6.xpm"
#include "images/player1/left/p1_left7.xpm"
#include "images/player1/left/p1_left8.xpm"
#include "images/player1/left/p1_left9.xpm"

#include "images/player1/right/p1_right0.xpm"
#include "images/player1/right/p1_right1.xpm"
#include "images/player1/right/p1_right2.xpm"
#include "images/player1/right/p1_right3.xpm"
#include "images/player1/right/p1_right4.xpm"
#include "images/player1/right/p1_right5.xpm"
#include "images/player1/right/p1_right6.xpm"
#include "images/player1/right/p1_right7.xpm"
#include "images/player1/right/p1_right8.xpm"
#include "images/player1/right/p1_right9.xpm"

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
