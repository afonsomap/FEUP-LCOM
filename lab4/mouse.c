#include "mouse.h"

static int hook_id = MOUSE_IRQ;

int (mouse_subscribe_int)(uint8_t *bit_no){
  *bit_no = hook_id;
  hook_id = MOUSE_IRQ;
  if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0) {
    printf("Failed to subscribe keyboard interrupts.\n");
    return 1;
  }
  return 0;
}

int (mouse_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hook_id) != 0) {
    printf("Failed to unsubscribe keyboard interrupts.\n");
    return 1;
  }
  return 0;
}



