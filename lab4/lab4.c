// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "mouse.h"
#include "timer.h"
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
  uint8_t bit_no;
  int ipc_status,r;
  message msg;
 
  if (mouse_subscribe_int(&bit_no)!=0) {
    printf("Failed to subscribe mouse interrupts.\n");
    return 1;
  }
  if (mouse_write_command(KBC_ENABLE_DATA_REPORT)!=0) {
    printf("Failed to enable data report.\n");
    return 1;
  }
  uint32_t irq_set = BIT(bit_no);

  while(cnt > 0) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) {

            mouse_ih();

            if (check_packet_complete()) {
              packet_parse();
              struct packet* packet = get_packet();
              mouse_print_packet(packet);
              cnt--;
            }  
          }
          break;
        default:
          break; 
      }
    }
  }
  if (mouse_write_command(KBC_DISABLE_DATA_REPORT)!=0) {
    printf("Failed to disable data report.\n");
    return 1;
  }
  if (mouse_unsubscribe_int()!=0) {
    printf("Failed to unsubscribe mouse interrupts.\n");
    return 1;
  }
  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  int ipc_status;
  message msg;
  uint8_t bit_no_timer, bit_no_mouse;
  uint16_t timer_frequency = sys_hz();

  if (timer_subscribe_int(&bit_no_timer) != 0) {
    printf("Failed to subscribe timer interrupts.\n");
    return 1;
  }
  if (mouse_subscribe_int(&bit_no_mouse)!=0) {
    printf("Failed to subscribe mouse interrupts.\n");
    return 1;
  }
  if (mouse_write_command(KBC_ENABLE_DATA_REPORT)!=0) {
    printf("Failed to enable data report.\n");
    return 1;
  }

  uint32_t irq_set_timer = BIT(bit_no_timer);
  uint32_t irq_set_mouse = BIT(bit_no_mouse);

  uint8_t time_passed = 0;
  while (time_passed < idle_time) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0){
      printf("Error");
      continue;
    }
    if (is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE: 

          if (msg.m_notify.interrupts & irq_set_timer) { 
            timer_int_handler();
            if (timer_get_count() % timer_frequency == 0){
              time_passed++;              
            }
          }

          if (msg.m_notify.interrupts & irq_set_mouse){ 
            mouse_ih();

            if (check_packet_complete()) {
              packet_parse();
              struct packet* packet = get_packet();
              mouse_print_packet(packet);
            }
            timer_reset_count();
            time_passed = 0;
          }

          break;
        default:
          break;
      }
    }
  }

  if (mouse_write_command(KBC_DISABLE_DATA_REPORT)!=0) {
    printf("Failed to disable data report.\n");
    return 1;
  }
  if (mouse_unsubscribe_int()!=0) {
    printf("Failed to unsubscribe mouse interrupts.\n");
    return 1;
  }
  if (timer_unsubscribe_int()!=0) {
    printf("Failed to unsubscribe timer interrupts.\n");
    return 1;
  }
  return 0;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
