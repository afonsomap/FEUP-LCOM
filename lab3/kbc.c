#include <lcom/lcf.h>
#include "kbc.h"

int (kbc_get_status)(uint8_t *st){
  if(util_sys_inb(KBC_ST_REG, st) != 0){
    printf("Failed to read status.\n");
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
  return 1;
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
