#include <lcom/lcf.h>
#include "kbd.h"

int hook_id =1;
uint32_t sys_counter = 0;
uint8_t scancode = 0;


int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t val;
  if(sys_inb(port,&val) != 0) {
    printf("Failed in call sys_inb.\n");
    return 1;
  }

  #ifdef LAB3
  sys_counter++;  
  #endif

  *value = (uint8_t)(val & 0xFF);
  return 0;
}

int (kbd_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  hook_id = KBD_IRQ;
  if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0) {
    printf("Failed to subscribe keyboard interrupts.\n");
    return 1;
  }
  return 0;
}

int (kbd_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hook_id) != 0) {
    printf("Failed to unsubscribe keyboard interrupts.\n");
    return 1;
  }
  return 0;
}

int (kbd_get_status)(uint8_t *st) {
  if(util_sys_inb(KBC_ST_REG, st) != 0){
    printf("Failed to read keybord status.\n");
    return 1;
  }
  return 0;
}

void (kbc_ih)(void){
  kbd_get_scancode();
}

int (kbd_get_scancode)() {
  uint8_t status;
  if(kbd_get_status(&status) != 0){
    printf("Failed to get status.\n");
    return 1;
  }
  if((status & KBC_OBF ) != 0){
    if(util_sys_inb(KBC_OUT_BUF, &scancode) != 0){
      printf("Failed to read from OUT_BUF.\n");
      return 1;
    }
    if((status & (KBC_TO_ERR | KBC_PAR_ERR)) != 0){
      scancode = 0;
    }
  }
  return 0;
}

int (check_scancode_complete)(uint8_t* scancode_array, uint8_t *index){
  if (scancode == TWO_BYTE_CODE) {
    scancode_array[*index] = scancode;
    (*index)++;
    return 1;
  }else{
    scancode_array[*index] = scancode;
    return 0;
  }
  
}



