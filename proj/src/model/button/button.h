#ifndef BUTTON_H
#define BUTTON_H

#include <lcom/lcf.h>

#include "sprite.h"
#include "cursor.h"

struct button_imp;
typedef struct button_imp Button;

Button *create_button(uint16_t x, uint16_t y, Sprite *sprite);
void destroy_button(Button *button);
void draw_button(Button *button);
bool is_button_clicked(Button *button, Cursor *cursor);

#endif // BUTTON_H
