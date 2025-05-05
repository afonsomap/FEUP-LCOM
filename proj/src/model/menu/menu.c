#include "menu.h"

struct menu_imp {
  Sprite *background;     // Background image of the menu
  Sprite *resume_button;  // "Resume" button sprite
  Sprite *exit_button;    // "Exit" button sprite
};

Menu* create_menu() {
  Menu *m = (Menu *) malloc(sizeof(Menu));
  if (m == NULL) {
    return NULL;
  }

  m->background = create_sprite((xpm_map_t)/* */);
  m->resume_button = create_sprite((xpm_map_t)/* */); // DEFINIR !!
  m->exit_button = create_sprite((xpm_map_t)/* */);

  if (m->background == NULL || m->resume_button == NULL || m->exit_button == NULL) {
    destroy_menu(m);
    return NULL;
  }

  return m;
}

void destroy_menu(Menu *m) {
  if (m == NULL) {
    return;
  }

  if (m->background != NULL) {
    destroy_sprite(m->background);
  }
  if (m->resume_button != NULL) {
    destroy_sprite(m->resume_button);
  }
  if (m->exit_button != NULL) {
    destroy_sprite(m->exit_button);
  }

  free(m);
}

void draw_menu(Menu *m) {
  if (m == NULL) {
    return;
  }

  draw_sprite(m->background, 0, 0);
  draw_sprite(m->resume_button, 100, 100); 
  draw_sprite(m->exit_button, 100, 200);   
}