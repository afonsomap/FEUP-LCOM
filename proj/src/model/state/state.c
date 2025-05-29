#include <lcom/lcf.h>
#include "state.h"

struct state_imp {
  SingleMode *sm; // Pointer to the single mode game
  Menu *m; // Pointer to the menu
  Died *d; // Pointer to the died state
  Cursor *c; // Pointer to the cursor
  SpriteLoader *loader; // Pointer to the sprite loader
  GameState current_state; // Current state of the game
};

State *create_state(SpriteLoader *loader, Cursor *c) {
  State *state = (State *) malloc(sizeof(State));
  if (state == NULL) {
    return NULL;
  }

  state->loader = loader;
  state->sm = NULL;
  state->m = create_menu(loader);
  state->d = NULL;
  state->c = c;
  state->current_state = MENU;
  return state;
}

void destroy_state(State *state) {
  if (state == NULL) {
    return;
  }

  if (state->sm != NULL) {
    destroy_singleMode(state->sm);
  }
  if (state->m != NULL) {
    destroy_menu(state->m);
  }
  if (state->d != NULL) {
    destroy_died(state->d);
  }

  free(state);
}

void update_state(State *state, KeyPressed *key, Cursor *c) {
  if (state == NULL) {
    panic("State is NULL");
  }

  update_state_kbd(state, key);
  update_state_mouse(state, c);
  update_state_without_event(state);
}

void update_state_kbd(State *state, KeyPressed *key) {
  if (state == NULL) {
    panic("State is NULL");
  }

  switch (state->current_state) {
    case SINGLE_MODE:
      if (process_single_mode_kbd(state->sm, key) == 1) {
        state->current_state = MENU; // Go back to menu
        destroy_singleMode(state->sm);
        state->sm = NULL;
        state->m = create_menu(state->loader);
        reset_cursor_button_pressed(state->c);
      }
      break;
    default:
      break;
  }
}

void update_state_mouse(State *state, Cursor *c) {
  if (state == NULL || c == NULL) {
    panic("State or Cursor is NULL");
  }

  switch (state->current_state) {
    case SINGLE_MODE:
      if (process_single_mode_mouse(state->sm, c) == 1) {
        state->current_state = MENU; // Go back to menu
        destroy_singleMode(state->sm);
        state->sm = NULL;
        state->m = create_menu(state->loader);
        reset_cursor_button_pressed(c);
      }
      break;

    case MENU:
      if (process_menu_input(c) == 1) {
        state->current_state = EXIT; // Exit game
        destroy_menu(state->m);
        state->m = NULL;
      } else if (process_menu_input(c) == 2) {
        state->current_state = SINGLE_MODE; // Go to single mode
        destroy_menu(state->m);
        state->m = NULL;
        state->sm = create_singleMode(state->loader);
        reset_cursor_button_pressed(c);
      }
      break;

    case DIED:
      if (process_died_input(state->d, c) == 1) {
        state->current_state = MENU; // Exit to the menu
        destroy_died(state->d);
        state->d = NULL;
        state->m = create_menu(state->loader);
        reset_cursor_button_pressed(c);
      } else if (process_died_input(state->d, c) == 2) {
        state->current_state = SINGLE_MODE; // Exit to the menu
        destroy_died(state->d);
        state->d = NULL;
        state->sm = create_singleMode(state->loader);
        reset_cursor_button_pressed(c);
      }
      break;

    default:
      break;
  }
}

void update_state_without_event(State *state) {
  if (state == NULL) {
    panic("State is NULL");
  }

  if (state->current_state == SINGLE_MODE) {
    process_bomb_spawning(state->sm); // Process bomb spawning
    if (check_bomb_exploded(state->sm)) {
      state->current_state = DIED; // Go to died state
      destroy_singleMode(state->sm);
      state->sm = NULL;
      state->d = create_died_page(state->loader);
      reset_cursor_button_pressed(state->c);
    }
  }else{
    return; // No need to check for other states
  }
}

void draw_state(State *state) {
  if (state == NULL) {
    panic("State is NULL");
  }

  switch (state->current_state) {
    case SINGLE_MODE:
      draw_singleMode(state->sm);
      break;

    case MENU:
      draw_menu(state->m);
      break;

    case DIED:
      draw_died(state->d);
      break;

    default:
      break;
  }

  draw_cursor(state->c);
}

int is_game_over(State *state) {
  if (state == NULL) {
    panic("State is NULL");
  }

  return (state->current_state == EXIT) ? 1 : 0;
}
