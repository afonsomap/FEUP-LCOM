#include <lcom/lcf.h>
#include "graphics.h"
#include "kbd.h"
#include "mouse.h"
#include "timer_count.h"
#include "spriteLoader.h"
#include "singleMode.h"
#include "cursor.h"

static SpriteLoader *loader;
static SingleMode *sm;
static Cursor *c;
static bool key_pressed[4] = {false, false, false, false}; // UP, DOWN, LEFT, RIGHT
static bool running = true;

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

  while ( running ) {
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
              case ESC_BREAK_CODE:
                running = false;
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
            if (timer_get_count() % 2 == 0) { //Timer works at 60 Hz, this will the game will be 30 fps
              clear_buffer();
              draw_cursor(c)
              process_input(sm, key_pressed);
              draw_singleMode(sm);
              copy_buffer_vram();
              timer_reset_count();
            }
          }

          if (msg.m_notify.interrupts & irq_set_mouse) {
            mouse_ih();
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
  sm = create_singleMode(loader);

  interrups_loop();
  
  destroy_singleMode(sm);
  free_buffer();
  destroy_sprites(loader);

  vg_exit();

  return 0;
}
