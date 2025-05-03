#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <lcom/lcf.h>
#include "vbe.h"

/**
 * @defgroup graphics graphics 
 * @{
 * 
 * Functions to interact with the graphics card.
 */


/**
 * @brief Returns the structure that holds the VBE mode information
 * 
 * @return VBE mode information structure
 */
vbe_mode_info_t get_mode_info();

/**
 * @brief Sets the video mode
 * 
 * Panic if the mode is not supported.
 * 
 * @param mode Video mode to set
 */
void set_video_mode(uint16_t mode);

/**
 * @brief Allocates physical memory and maps it to the virtual address space
 * 
 * Panic if the allocation fails.
 * 
 * @param mode Video mode to know the needed memory
 */
void map_graphics_vram(uint16_t mode);

/**
 * @brief Allocates a buffer to store the graphics data
 * 
 * Panic if the allocation fails.
 */
void allocate_buffer();

/**
 * @brief Copies the buffer to the video memory
 */
void copy_buffer_vram();

/**
 * @brief Frees the buffer
 */
void free_buffer();

/**
 * @brief Clears the buffer

 */
void clear_buffer();

/**
 * @brief Draws a pixel on the screen
 * 
 * Panic if something goes wrong.
 * 
 * @param x X coordinate of the pixel
 * @param y Y coordinate of the pixel
 * @param color Color of the pixel
 */
void draw_pixel(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a horizontal line on the screen
 * 
 * Panic if something goes wrong.
 * 
 * @param x X coordinate of the starting point
 * @param y Y coordinate of the starting point
 * @param length Length of the line
 * @param color Color of the line
 * @return 0 on success, 1 on failure
 */
void draw_hline(uint16_t x, uint16_t y, uint16_t length, uint32_t color);

/**
 * @brief Draws a rectangle on the screen
 * 
 * Panic if something goes wrong.
 * 
 * @param x X coordinate of the top left corner
 * @param y Y coordinate of the top left corner
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param color Color of the rectangle
 * @return 0 on success, 1 on failure
 */
void draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief Draws an xpm image on the screen
 * 
 * @param xpm XPM image to draw
 * @param x X coordinate of the top left corner
 * @param y Y coordinate of the top left corner
 * @return 0 on success, 1 on failure
 */
int vg_draw_xpm(uint8_t* xpm_map, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

#endif

