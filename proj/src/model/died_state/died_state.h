#ifndef DIED_H
#define DIED_H


#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "sprite.h"
#include "spriteLoader.h"
#include "cursor.h"

struct died_imp;
typedef struct died_imp Died;

Died* create_Died_Page(SpriteLoader *loader);

void destroy_died(Died *d);

void draw_died(Died *d);

int process_died_input(Cursor *c);

#endif
