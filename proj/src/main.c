#include <lcom/lcf.h>
#include "graphics.h"
#include "kbd.h"
#include "mouse.h"
#include "timer_count.h"
#include "spriteLoader.h"
#include "singleMode.h"
#include "Died.h"
#include "cursor.h"
#include "menu.h"

typedef enum {
  MENU,
  SINGLE_MODE,
  DIED,
  EXIT
} GameState;

static SpriteLoader *loader = NULL;
static SingleMode *sm = NULL;
static Menu *m = NULL;
static Died *d = NULL;
static Cursor *c = NULL;
static bool key_pressed[5] = {false, false, false, false, false}; // UP, DOWN, LEFT, RIGHT, ESC
GameState current_state = MENU;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

void interrups_loop() {
  if ( mouse_write_command(KBC_ENABLE_DATA_REPORT) != 0 ) {
    printf("Error enabling data reporting\n");
    return;
  }

  uint8_t bit_no_timer, bit_no_kbd, bit_no_mouse;
  int ipc_status;
  message msg;

  if (timer_subscribe_int(&bit_no_timer) != 0) {
    printf("Error subscribing timer interrupts\n");
    return;
  }
  if (kbd_subscribe_int(&bit_no_kbd) != 0) {
    printf("Error subscribing kbd interrupts\n");
    return;
  }
  if (mouse_subscribe_int(&bit_no_mouse) != 0) {
    printf("Error subscribing mouse interrupts\n");
    return;
  }

  uint32_t irq_set_timer = BIT(bit_no_timer);
  uint32_t irq_set_kbd = BIT(bit_no_kbd);
  uint32_t irq_set_mouse = BIT(bit_no_mouse);

  uint8_t *scancode = get_scancode();

  while ( current_state != EXIT ) {
    if( driver_receive(ANY, &msg, &ipc_status) != 0 ){
      printf("Error");
      continue;
    }
    if(is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set_kbd) {
            kbc_ih();

            if (check_scancode_complete() == 0){
              switch (*scancode)
              {
              case ESC_MAKE_CODE:
                key_pressed[4] = true;
                break;
              case ESC_BREAK_CODE:
                key_pressed[4] = false;
                break;
              case W_MAKE_CODE:
                key_pressed[0] = true;
                break;
              case W_BREAK_CODE:
                key_pressed[0] = false;
                break;
              case S_MAKE_CODE:
                key_pressed[1] = true;
                break;
              case S_BREAK_CODE:
                key_pressed[1] = false;
                break;
              case A_MAKE_CODE:
                key_pressed[2] = true;
                break;    
              case A_BREAK_CODE:
                key_pressed[2] = false;
                break;
              case D_MAKE_CODE:
                key_pressed[3] = true;
                break;
              case D_BREAK_CODE:
                key_pressed[3] = false;
                break;
              default:
                break;
              }
            }
          }

          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
            if (timer_get_count() % 2 == 0) { // 30 FPS
              clear_buffer();
          
              int menu_return;
              switch (current_state) {
                case SINGLE_MODE:

                  if (process_single_mode_kbd(sm, key_pressed) == 1) {

                    current_state = MENU; // Go back to menu
                    destroy_singleMode(sm);
                    sm = NULL;
                    m = create_menu(loader);
                    memset(key_pressed, false, sizeof(key_pressed));
                    reset_cursor_button_pressed(c);
                    draw_menu(m);
                    draw_cursor(c);
                    break;

                  }

                  if (process_single_mode_mouse(sm, c) == 1) {

                    current_state = MENU; // Go back to menu
                    destroy_singleMode(sm);
                    sm = NULL;
                    m = create_menu(loader);
                    memset(key_pressed, false, sizeof(key_pressed));
                    reset_cursor_button_pressed(c);
                    draw_menu(m);
                    draw_cursor(c);
                    break;

                  }
                  
                  if (check_bomb_exploded(sm) == 1) {

                    current_state = DIED; // Go back to "You died" page
                    destroy_singleMode(sm);
                    sm = NULL;
                    d = create_Died_Page(loader);
                    memset(key_pressed, false, sizeof(key_pressed));
                    reset_cursor_button_pressed(c);
                    draw_died(d);
                    draw_cursor(c);
                    break;

                  }

                  draw_singleMode(sm);
                  draw_cursor(c);
                  break;
          
                case MENU:
                  menu_return = process_menu_input(c);
                  if (menu_return == 1) {

                    current_state = EXIT; // Exit game
                    destroy_menu(m);
                    m = NULL;
                    break;

                  } else if (menu_return == 2) {

                    current_state = SINGLE_MODE; // Go to single mode
                    destroy_menu(m);
                    m = NULL;
                    sm = create_singleMode(loader);
                    memset(key_pressed, false, sizeof(key_pressed));
                    reset_cursor_button_pressed(c);
                    draw_singleMode(sm);
                    draw_cursor(c);
                    break;
                  }

                  draw_menu(m);
                  draw_cursor(c);
                  break;

                case DIED:
                  if (process_died_input(c) == 1) {

                    current_state = MENU; // Exit to the menu
                    destroy_died(d);
                    d = NULL;
                    m = create_menu(loader);
                    memset(key_pressed, false, sizeof(key_pressed));
                    reset_cursor_button_pressed(c);
                    draw_menu(m);
                    draw_cursor(c);
                    break;

                  }

                  draw_died(d);
                  draw_cursor(c);
                  break;

                default:
                  break;

              }
          
              copy_buffer_vram();
              timer_reset_count();
            }
          }

          if (msg.m_notify.interrupts & irq_set_mouse) {
            mouse_ih();

            if (check_packet_complete() == 1) {
              packet_parse();
              struct packet *pp = get_packet();
              update_cursor_with_mouse(c, pp);
            }
          }

          break;
        default:
          break;
      }
    }
  }

  if (mouse_unsubscribe_int() != 0) {
    printf("Error unsubscribing mouse interrupts\n");
    return;
  }
  if (kbd_unsubscribe_int() != 0) {
    printf("Error unsubscribing kbd interrupts\n");
    return;
  }
  if (timer_unsubscribe_int() != 0) {
    printf("Error unsubscribing timer interrupts\n");
    return;
  }
  if (mouse_write_command(KBC_DISABLE_DATA_REPORT) != 0) {
    printf("Error disabling data reporting\n");
    return;
  }
}


int (proj_main_loop)(int argc, char *argv[]) {

  map_graphics_vram(VBE_1024p_DC);
  allocate_buffer();
  set_video_mode(VBE_1024p_DC);

  loader = load_sprites();
  c = create_cursor(get_cursor(loader), get_mode_info().XResolution, get_mode_info().YResolution);
  m = create_menu(loader);

  interrups_loop();
  
  destroy_cursor(c);
  destroy_sprites(loader);

  free_buffer();
  vg_exit();

  return 0;
}
