#ifndef _SPRITELOADER_H_
#define _SPRITELOADER_H_

#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "sprite.h"
#include "animatedSprite.h"

#include "images/player1/back/p1_back1.xpm"
#include "images/player1/back/p1_back2.xpm"
#include "images/player1/back/p1_back3.xpm"
#include "images/player1/back/p1_back4.xpm"
#include "images/player1/back/p1_back5.xpm"

#include "images/player1/front/p1_front1.xpm"
#include "images/player1/front/p1_front2.xpm" 
#include "images/player1/front/p1_front3.xpm"
#include "images/player1/front/p1_front4.xpm"
#include "images/player1/front/p1_front5.xpm"

#include "images/player1/left/p1_left1.xpm"
#include "images/player1/left/p1_left2.xpm"
#include "images/player1/left/p1_left3.xpm"
#include "images/player1/left/p1_left4.xpm"
#include "images/player1/left/p1_left5.xpm"

#include "images/player1/right/p1_right1.xpm"
#include "images/player1/right/p1_right2.xpm"
#include "images/player1/right/p1_right3.xpm"
#include "images/player1/right/p1_right4.xpm"
#include "images/player1/right/p1_right5.xpm"

#include "images/bomb/bomb1.xpm"
#include "images/bomb/bomb2.xpm"  
#include "images/bomb/bomb3.xpm"
#include "images/bomb/bomb4.xpm"
#include "images/bomb/bomb5.xpm"
#include "images/bomb/bomb6.xpm"
#include "images/bomb/bomb7.xpm"
#include "images/bomb/bomb8.xpm"
#include "images/bomb/bomb9.xpm"
#include "images/bomb/bomb10.xpm"

#include "images/explosion/explosion1.xpm"
#include "images/explosion/explosion2.xpm"  
#include "images/explosion/explosion3.xpm"
#include "images/explosion/explosion4.xpm"
#include "images/explosion/explosion5.xpm"  
#include "images/explosion/explosion6.xpm"
#include "images/explosion/explosion7.xpm"
#include "images/explosion/explosion8.xpm"
#include "images/explosion/explosion9.xpm"

#include "images/bomb_options/bomb_option1.xpm"
#include "images/bomb_options/bomb_option2.xpm"
#include "images/bomb_options/bomb_option3.xpm"

#include "images/bomb_options/selected_bomb1.xpm"
#include "images/bomb_options/selected_bomb2.xpm"
#include "images/bomb_options/selected_bomb3.xpm"

#include "images/wall/wall.xpm"
#include "images/wall/solid_wall.xpm"

#include "images/background/grid_background.xpm"
#include "images/background/game_background.xpm"

#include "images/cursor.xpm"

#include "images/menu/menu_background.xpm"
#include "images/menu/menu_single.xpm"
#include "images/menu/menu_multi.xpm"
#include "images/menu/menu_exit.xpm"
#include "images/menu/menu_title.xpm"

#include "images/single_player/exit_sp.xpm"

#include "images/died/died_text.xpm"
#include "images/died/died_background.xpm"
#include "images/died/play_again.xpm"
#include "images/died/back_to_menu.xpm"
#include "images/died/your_score.xpm"

#include "images/numbers/number_0.xpm"
#include "images/numbers/number_1.xpm"
#include "images/numbers/number_2.xpm"
#include "images/numbers/number_3.xpm"
#include "images/numbers/number_4.xpm"
#include "images/numbers/number_5.xpm"
#include "images/numbers/number_6.xpm"
#include "images/numbers/number_7.xpm"
#include "images/numbers/number_8.xpm"
#include "images/numbers/number_9.xpm"

#include "images/winner/you_won.xpm"
#include "images/winner/you_lost.xpm"
#include "images/winner/draw.xpm"

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
Sprite* get_solid_wall(SpriteLoader *loader);
Sprite* get_grid_background(SpriteLoader *loader);
Sprite* get_cursor(SpriteLoader *loader);
AnimSprite* get_explosion(SpriteLoader *loader);
Sprite* get_menu_background(SpriteLoader *loader);
Sprite* get_menu_title(SpriteLoader *loader);
Sprite* get_single_mode_button(SpriteLoader *loader);
Sprite* get_multi_mode_button(SpriteLoader *loader);
Sprite* get_exit_button(SpriteLoader *loader);
Sprite* get_exit(SpriteLoader *loader);
Sprite** get_bomb_options(SpriteLoader *loader);
Sprite** get_selected_options(SpriteLoader *loader);
Sprite* get_game_background(SpriteLoader *loader);
Sprite* get_died_title(SpriteLoader *loader);
Sprite* get_died_background(SpriteLoader *loader);
Sprite* get_play_again(SpriteLoader *loader);
Sprite* get_back_to_menu(SpriteLoader *loader);
Sprite* get_number_sprite(SpriteLoader *loader, int number);
Sprite* get_your_score_text(SpriteLoader *loader);

Sprite* get_winners_background(SpriteLoader *loader);
Sprite* get_winners_you_won(SpriteLoader *loader);
Sprite* get_winners_you_lost(SpriteLoader *loader);
Sprite* get_winners_draw(SpriteLoader *loader);

#endif
