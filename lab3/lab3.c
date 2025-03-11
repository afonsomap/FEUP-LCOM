#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include <i8042.h>
#include "kbd.h"

#include <stdbool.h>
#include <stdint.h>

extern uint32_t sys_counter;
extern uint8_t scancode;


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
  uint8_t code[2];
  uint8_t index = 0;


  if (kbd_subscribe_int(&bit_no)!=0) {
    printf("Failed to subscribe kbd interrupts.\n");
    return 1;
  }

  uint32_t irq_set = BIT(bit_no);


  while(scancode != ESC_BREAKCODE) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) {

            kbc_ih();

            if (check_scancode_complete(code, &index) == 0) {
              kbd_print_scancode(!(scancode & MAKECODE), index+1, code);
              index = 0;
            }
          }  
          break;
        default:
          break; 
      }
    }
  }
  if (kbd_unsubscribe_int()!=0) {return 1;}
  kbd_print_no_sysinb(sys_counter);
  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
