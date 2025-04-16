#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <lcom/lcf.h>
#include "vbe.h"

vbe_mode_info_t get_mode_info();

void normalize_color(uint32_t color, uint32_t *new_color);

void set_video_mode(uint16_t mode);

void map_graphics_vram(uint16_t mode);

void draw_pixel(uint16_t x, uint16_t y, uint32_t color);

void draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

uint32_t (direct_model)(uint32_t R, uint32_t G, uint32_t B);

uint32_t (indexed_model)(uint16_t col, uint16_t row, uint32_t first, uint8_t step, uint8_t n);

uint32_t (Red)(unsigned col, uint8_t step, uint32_t first);

uint32_t (Green)(unsigned row, uint8_t step, uint32_t first);

uint32_t (Blue)(unsigned col, unsigned row, uint8_t step, uint32_t first);

uint32_t (R)(uint32_t first);

uint32_t (G)(uint32_t first);

uint32_t (B)(uint32_t first);

int draw_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);

#endif

