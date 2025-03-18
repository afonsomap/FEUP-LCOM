#include <lcom/lcf.h>
#include "timer.h"

static int hook_id;
static unsigned int count = 0;

unsigned int timer_get_count() {
  return count;
}

void timer_reset_count() {
  count = 0;
}


int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id = TIMER0_IRQ;
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != 0) {
    printf("Failed to subscribe timer interrupts.\n");
    return 1;
  }
  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hook_id) != 0) {
    printf("Failed to unsubscribe timer interrupts.\n");
    return 1;
  }
  return 0;
}

void (timer_int_handler)() {
  count++;
}

