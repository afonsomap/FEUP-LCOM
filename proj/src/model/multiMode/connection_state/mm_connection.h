#ifndef MM_CONNECTION_H
#define MM_CONNECTION_H

#include <lcom/lcf.h>
#include "spriteLoader.h"
#include "cursor.h"
#include "serial_port.h"
#include "sprite.h"
#include "button.h"

struct mm_connection_imp;
typedef struct mm_connection_imp MmConnection;

#define HANDSHAKE_HELLO  0xC1
#define HANDSHAKE_REPLY  0xC2

MmConnection *create_mm_connection(SpriteLoader *loader);
void destroy_mm_connection(MmConnection *mm_connection);
void draw_mm_connection(MmConnection *mm_connection);
int process_mm_connection_mouse(MmConnection *mm_connection, Cursor *c);
int process_mm_connection_timer(MmConnection *mm_connection);
int process_mm_connection_sp(MmConnection *mm_connection, uint8_t byte);

#endif // MM_CONNECTION_H
