#include <lcom/lcf.h>

#include "i8042.h"

static int hook_id = 0;

int (kdb_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id = KBD_IRQ;
  if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0) {
    printf("Failed to subscribe keyboard interrupts.\n");
    return 1;
  }
  return 0;
}

int (kdb_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hook_id) != 0) {
    printf("Failed to unsubscribe keyboard interrupts.\n");
    return 1;
  }
  return 0;
}

int (kdb_get_status)(uint8_t *st) {
  if(util_sys_inb(KBC_ST_REG, st) != 0){
    printf("Failed to read keybord status.\n");
    return 1;
  }
  return 0;
}

int (kdb_get_scancode)(uint8_t *scancode) {
  u_int8_t status;
  if(kdb_get_status(&status) != 0){
    printf("Failed to get status.\n");
    return 1;
  }
  if(status & (KBC_TO_ERR | KBC_PAR_ERR) != 0){
    uint8_t trash;
    if(util_sys_inb(KBC_OUT_BUF, trash) != 0){
      printf("Failed to read from OUT_BUF.\n");
      return 1;
    }
  }

  if(status & KBC_OBF == 1){
    if(util_sys_inb(KBC_OUT_BUF, scancode) != 0){
      printf("Failed to read from OUT_BUF.\n");
      return 1;
    }
  }
  return 0;
}



