#ifndef _VBE_H
#define _VBE_H
#include <lcom/lcf.h>

void normalize_color(uint32_t color, uint32_t *new_color);

void set_video_mode(uint16_t mode);

void map_graphics_vram(uint16_t mode);

void draw_pixel(uint16_t x, uint16_t y, uint32_t color);

void draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

#endif
