// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "mouse.h"
#include "timer.h"


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

  if (mouse_write_command(KBC_ENABLE_DATA_REPORT)!=0) {
    printf("Failed to enable data report.\n");
    return 1;
  }
  if (mouse_subscribe_int(&bit_no)!=0) {
    printf("Failed to subscribe mouse interrupts.\n");
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
  if (mouse_unsubscribe_int()!=0) {
    printf("Failed to unsubscribe mouse interrupts.\n");
    return 1;
  }
  if (mouse_write_command(KBC_DISABLE_DATA_REPORT)!=0) {
    printf("Failed to disable data report.\n");
    return 1;
  }
  
  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  int ipc_status;
  message msg;
  uint8_t bit_no_timer, bit_no_mouse;
  uint16_t timer_frequency = sys_hz();

  if (mouse_write_command(KBC_ENABLE_DATA_REPORT)!=0) {
    printf("Failed to enable data report.\n");
    return 1;
  }

  if (timer_subscribe_int(&bit_no_timer) != 0) {
    printf("Failed to subscribe timer interrupts.\n");
    return 1;
  }
  if (mouse_subscribe_int(&bit_no_mouse)!=0) {
    printf("Failed to subscribe mouse interrupts.\n");
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
  
  if (mouse_unsubscribe_int()!=0) {
    printf("Failed to unsubscribe mouse interrupts.\n");
    return 1;
  }
  if (timer_unsubscribe_int()!=0) {
    printf("Failed to unsubscribe timer interrupts.\n");
    return 1;
  }

  if (mouse_write_command(KBC_DISABLE_DATA_REPORT)!=0) {
    printf("Failed to disable data report.\n");
    return 1;
  }
  return 0;
}

typedef enum {START, UP_RIGHT, DOWN_RIGHT, VERTEX, END} state;
static state current_state = START;
static int16_t x_displacement = 0;
static int16_t y_displacement = 0;

void update_state(struct packet* packet, uint8_t x_len, uint8_t tolerance) {
  switch (current_state) {
    case START:
      // Check if the left button is pressed
      if (packet->lb == 1 && packet->rb == 0 && packet->mb == 0) {
        x_displacement = 0;
        y_displacement = 0;
        current_state = UP_RIGHT;
      }
      break;

    case UP_RIGHT:
      // Check if only the left button is pressed
      if (packet->lb == 1 && packet->rb == 0 && packet->mb == 0) {
        // Check if the movement is within the tolerance
        if (packet->delta_x >= -tolerance && packet->delta_y <= tolerance) {
          x_displacement += packet->delta_x;
          y_displacement += packet->delta_y;
        }else{
          // Movement outside tolerance
          current_state = START;
        }
      } else if (
        packet->lb == 0 && packet->rb ==0 && packet->mb==0 // No buttons pressed
        && x_displacement>=x_len // Sufficient x displacement
        && abs(packet->delta_y) <= tolerance // Movement within tolerance
        &&  abs(packet->delta_x) <= tolerance // Movement within tolerance
        && (abs(y_displacement)/abs(x_displacement)) > 1) // Check if slope (y/x) is greater than 1
        { 
        // All conditions met, we can move to the vertex state
        current_state = VERTEX;
      } else {
        // Some condition not met, reset state
        current_state = START;
      }
      break;

    case VERTEX:
      // Only the right button should be pressed and movement should be within tolerance
      if (packet->lb == 0 && packet->rb == 1 && packet->mb == 0 && abs(packet->delta_y) <= tolerance &&  abs(packet->delta_x) <= tolerance) {
        x_displacement = 0;
        y_displacement = 0;
        current_state = DOWN_RIGHT;
      } else if (packet->lb == 0 && packet->rb == 0 && packet->mb == 0 && abs(packet->delta_y) <= tolerance &&  abs(packet->delta_x) <= tolerance) { 
        // No buttons pressed and movement within tolerance, stay in vertex state
        current_state = VERTEX; 
      } else {
        // Some condition not met, reset state
        current_state = START; 
      }
      break;

    case DOWN_RIGHT:
      // Check if only the right button is pressed
      if (packet->lb == 0 && packet->rb == 1 && packet->mb == 0) {
        // Check if the movement is within the tolerance
        if (packet->delta_x >= -tolerance && packet->delta_y >= -tolerance) {
          x_displacement += packet->delta_x;
          y_displacement += packet->delta_y;
        }else{
          // Movement outside tolerance
          current_state = START;
        }
      } else if (
        packet->lb == 0 && packet->rb ==0 && packet->mb==0 // No buttons pressed
        && x_displacement>=x_len // Sufficient x displacement
        && abs(packet->delta_y) <= tolerance // Movement within tolerance
        &&  abs(packet->delta_x) <= tolerance // Movement within tolerance
        && (abs(y_displacement)/abs(x_displacement)) > 1) // Check if slope (y/x) is greater than 1
        {
        // All conditions met, we can move to the end state
        current_state = END;
      } else {
        // Some condition not met, reset state
        current_state = START;  
      }
      break;

    case END:
      // Shouldn't be possible to reach this state, if it does, something went wrong :)
      printf("Reached end state, shoud not happen!\n");
      break;
    default:
      current_state = START;
      break;
  }
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
  uint8_t bit_no;
  int ipc_status,r;
  message msg;

  if (mouse_write_command(KBC_ENABLE_DATA_REPORT)!=0) {
    printf("Failed to enable data report.\n");
    return 1;
  }
  if (mouse_subscribe_int(&bit_no)!=0) {
    printf("Failed to subscribe mouse interrupts.\n");
    return 1;
  }
  
  uint32_t irq_set = BIT(bit_no);

  while(current_state != END) {
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
              update_state(packet,x_len, tolerance);
            }  
          }
          break;
        default:
          break; 
      }
    }
  }
  if (mouse_unsubscribe_int()!=0) {
    printf("Failed to unsubscribe mouse interrupts.\n");
    return 1;
  }
  if (mouse_write_command(KBC_DISABLE_DATA_REPORT)!=0) {
    printf("Failed to disable data report.\n");
    return 1;
  }
  
  return 0;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
