#include <lcom/lcf.h>
#include "kbd.h"

int hook_id =1;
uint32_t sys_counter = 0;
uint8_t scancode = 0;

int (util_sys_inb)(int port, uint8_t *value){
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

int (kbc_get_status)(uint8_t *st) {
  if(util_sys_inb(KBC_ST_REG, st) != 0){
    printf("Failed to read keybord status.\n");
    return 1;
  }
  return 0;
}

int (kbc_read_data)(uint8_t port, uint8_t *data){
  uint8_t status;
  uint8_t tries = MAX_TRIES;
  while (tries > 0){
    if(kbc_get_status(&status) != 0){
      printf("Failed to get status.\n");
      return 1;
    }
    if((status & KBC_OBF ) != 0){
      if(util_sys_inb(port, data) != 0){
        printf("Failed to read from OUT_BUF.\n");
        return 1;
      }
      if((status & (KBC_TO_ERR | KBC_PAR_ERR)) != 0){
        *data = 0;
        return 1;
      }
      return 0;
      
    }
    tries--;
    tickdelay(micros_to_ticks(WAIT_KBC));
  }
  return 0;
}

int (kbc_write_command)(uint8_t port, uint8_t cmd){
  uint8_t status;
  uint8_t tries = MAX_TRIES;
  while( tries>0 ) {
    if( kbc_get_status(&status) != 0 ) {return 1;}
    if( (status & KBC_IBF) == 0 ) {
      if(sys_outb(port, cmd) != 0) {
        printf("Failed to write command.\n");
        return 1;
      }
      return 0;
    }
    tries--;
    tickdelay(micros_to_ticks(WAIT_KBC));
  }
  return 1;
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


