#ifndef __BOMB_OPTION_H
#define __BOMB_OPTION_H

#include <lcom/lcf.h>
#include <stddef.h>
#include <stdlib.h>
#include "sprite.h"
#include "bomb.h"

struct bomb_options_imp;
typedef struct bomb_options_imp BombOptions;

/**
 * @brief Gets the x position of the bomb options
 *
 * @param b Pointer to the bomb options
 * @return The x position of the bomb options
 */
uint16_t get_options_x_initial(BombOptions *b);

/**
 * @brief Gets the y position of the bomb options
 *
 * @param b Pointer to the bomb options
 * @param index The index of the bomb option
 * @return The y position of the bomb option at the given index
 */
uint16_t get_options_y_initial(BombOptions *b, int index);

/**
 * @brief Gets the final x position of the bomb options
 *
 * @param b Pointer to the bomb options
 * @return The final x position of the bomb options
 */
uint16_t get_options_x_final(BombOptions *b);

/**
 * @brief Gets the final y position of the bomb options
 *
 * @param b Pointer to the bomb options
 * @param index The index of the bomb option
 * @return The final y position of the bomb option at the given index
 */
uint16_t get_options_y_final(BombOptions *b, int index);

/**
 * @brief Gets the number of bomb options
 *
 * @param b Pointer to the bomb options
 * @return The number of bomb options
 */
uint8_t get_number_of_options(BombOptions *b);

/**
 * @brief Creates a new bomb options element
 *
 * @param options The array of sprites for the bomb options
 * @param selected_option The array of sprites for the selected bomb options
 * @return Pointer to the created bomb options, or NULL if the pixmap is invalid
 */
BombOptions *create_bomb_options(Sprite** options, Sprite** selected_option);


/**
 * @brief Frees the memory allocated for the bomb options
 *
 * @param b Pointer to the bomb options to be destroyed
 */
void destroy_bomb_options(BombOptions *b); 

/**
 * @brief Draws the bomb options on the screen
 *
 * @param b Pointer to the bomb options to be drawn
 * @param selected_option The index of the selected bomb option
 */
void draw_bomb_options(BombOptions *b, int selected_option);

void set_bomb_unavailable(BombOptions *b, BombType type);

bool isBombAvailable(BombOptions *b, BombType type);

void decrease_time_availability(BombOptions *b);

void decrease_time_spawning(BombOptions *b);

bool is_spawning(BombOptions *b);

void set_spawn_rate(BombOptions *b);

BombType get_random_bomb();

void print_availability_counters(BombOptions *b);


#endif /* __BOMB_OPTIONS_H */

