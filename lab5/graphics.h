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
 * @brief Creates the uint32_t with the color of the pixel in direct mode, given the RGB values
 * 
 * @param R Red component
 * @param G Green component
 * @param B Blue component
 * @return uint32_t with the color of the pixel
 */
uint32_t (direct_mode)(uint32_t R, uint32_t G, uint32_t B);

/**
 * @brief Returns the index of the color in the color palette based on the collum and row position
 * 
 * @param col Column index
 * @param row Row index
 * @param first First color
 * @param step Step size
 * @param n Number of colors
 * @return uint32_t with the index of the color
 */
uint32_t (indexed_mode)(uint16_t col, uint16_t row, uint32_t first, uint8_t step, uint8_t n);

/**
 * @brief Calculates the red component of a pixel in direct mode
 * 
 * @param col Column index
 * @param step Step size
 * @param first First color
 * @return uint32_t with the red component of the pixel
 */
uint32_t (Red)(unsigned col, uint8_t step, uint32_t first);

/**
 * @brief Calculates the green component of a pixel in direct mode
 * 
 * @param row Row index
 * @param step Step size
 * @param first First color
 * @return uint32_t with the green component of the pixel
 */
uint32_t (Green)(unsigned row, uint8_t step, uint32_t first);

/**
 * @brief Calculates the blue component of a pixel in direct mode
 * 
 * @param col Column index
 * @param row Row index
 * @param step Step size
 * @param first First color
 * @return uint32_t with the blue component of the pixel
 */
uint32_t (Blue)(unsigned col, unsigned row, uint8_t step, uint32_t first);

/**
 * @brief Returns the red component of the first pixel
 * 
 * @param first First color
 * @return uint32_t with the red component of the first pixel
 */
uint32_t (R)(uint32_t first);

/**
 * @brief Returns the green component of the first pixel
 * 
 * @param first First color
 * @return uint32_t with the green component of the first pixel
 */
uint32_t (G)(uint32_t first);

/**
 * @brief Returns the blue component of the first pixel
 * 
 * @param first First color
 * @return uint32_t with the blue component of the first pixel
 */
uint32_t (B)(uint32_t first);

/**
 * @brief Draws an xpm image on the screen
 * 
 * @param xpm XPM image to draw
 * @param x X coordinate of the top left corner
 * @param y Y coordinate of the top left corner
 * @return 0 on success, 1 on failure
 */
int draw_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);

/**
 * @brief Erases an xpm image from the screen
 * 
 * @param xpm XPM image to erase
 * @param x X coordinate of the top left corner
 * @param y Y coordinate of the top left corner
 * @return 0 on success, 1 on failure
 */
int clean_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);

#endif

