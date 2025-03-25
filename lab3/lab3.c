#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include "kbd.h"
#include "timer.h"
#include "utils.h"

#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {

  uint8_t bit_no = 0;
  int ipc_status,r;
  message msg;

  if (kbd_subscribe_int(&bit_no)!=0) {
    printf("Failed to subscribe kbd interrupts.\n");
    return 1;
  }

  uint32_t irq_set = BIT(bit_no);

  uint8_t* scancode = get_scancode();

  while(*scancode != ESC_BREAKCODE) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) {

            kbc_ih();

            if (check_scancode_complete() == 0) {
              uint8_t* code = get_scancode_array();
              uint8_t index = get_scancode_index();
              kbd_print_scancode(!(*scancode & MAKECODE), (index == 0) ? 1 : 2, code);
            }  
          }
          break;
        default:
          break; 
      }
    }
  }
  if (kbd_unsubscribe_int()!=0) {return 1;}
  kbd_print_no_sysinb(get_sys_counter());
  return 0;
}

int(kbd_test_poll)() {
  uint8_t* scancode = get_scancode();
  while(*scancode != ESC_BREAKCODE) {
    if(kbc_read_data(KBC_OUT_BUF, scancode) != 0) {
      return 1;
    }
    if (check_scancode_complete() == 0) {
      uint8_t* code = get_scancode_array();
      uint8_t index = get_scancode_index();
      kbd_print_scancode(!(*scancode & MAKECODE), (index == 0) ? 1 : 2, code);
    }
  }
  kbd_print_no_sysinb(get_sys_counter());
  if(kbd_enable_interrupts() != 0) {
    return 1;
  }
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t bit_no_kbd, bit_no_timer;
  int ipc_status,r;
  message msg; 

  if (kbd_subscribe_int(&bit_no_kbd)!=0) {
    printf("Failed to subscribe kbd interrupts.\n");
    return 1;
  }
  if (timer_subscribe_int(&bit_no_timer)!=0) {
    printf("Failed to subscribe timer interrupts.\n");
    return 1;
  }

  uint32_t irq_set_kbd = BIT(bit_no_kbd);
  uint32_t irq_set_timer = BIT(bit_no_timer);

  uint8_t* scancode = get_scancode();

  uint8_t time_left = n;

  while (*scancode!=ESC_BREAKCODE && time_left>0) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set_kbd) {
            kbc_ih();
            if (check_scancode_complete() == 0) {
              uint8_t* code = get_scancode_array();
              uint8_t index = get_scancode_index();
              kbd_print_scancode(!(*scancode & MAKECODE), (index == 0) ? 1 : 2, code);
            }
            time_left = n;
            timer_reset_count();
          }
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
            if (timer_get_count() % 60 == 0) {
              time_left--;
              timer_reset_count();
            }
          }
          break;
        default:
          break; 
      }
    }
  }

  if (kbd_unsubscribe_int()!=0) {return 1;}
  if (timer_unsubscribe_int()!=0) {return 1;}

  return 0;
}
