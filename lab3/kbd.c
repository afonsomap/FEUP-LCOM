#include <lcom/lcf.h>
#include "kbd.h"

static int hook_id = 1;
static uint8_t scancode = 0;

uint8_t* get_scancode(){
  return &scancode;
}

int (kbd_subscribe_int)(uint8_t *bit_no){
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

void (kbc_ih)(void){
  kbc_read_data(KBC_OUT_BUF, &scancode);
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

int (kbd_enable_interrupts)(){
  uint8_t cmd;

  if(kbc_write_command(KBC_CMD_REG, KBC_READ_CMD) != 0){
    return 1;
  }
  if(kbc_read_data(KBC_OUT_BUF, &cmd) != 0){
    return 1;
  }
  cmd = cmd | BIT(0);
  if(kbc_write_command(KBC_CMD_REG, KBC_WRITE_CMD) != 0){
    return 1;
  }
  if(kbc_write_command(KBC_OUT_BUF, cmd) != 0){
    return 1;
  }
  return 0;
}


