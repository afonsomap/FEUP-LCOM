#include <lcom/lcf.h>
#include "utils.h"

static int sys_counter = 0;

int get_sys_counter(){
  return sys_counter;
}

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
