#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t rbc = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  int ret = sys_outb(TIMER_CTRL,rbc);
  if(ret!=0)return ret;
  return util_sys_inb(TIMER_0 + timer,st);
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val print_val;
  uint8_t mask;
  uint8_t mode;
  switch (field){
    case tsf_all:
      print_val.byte = st;
      break;
    case tsf_initial:
      switch (st & (BIT(4) | BIT(5))){
      case BIT(4):
        print_val.in_mode = LSB_only;
        break;
      case BIT(5):
        print_val.in_mode = MSB_only;
        break;
      case (BIT(4) | BIT(5)):
        print_val.in_mode = MSB_after_LSB;
        break;
      default:
        print_val.in_mode = INVAL_val;
        break;
      }
      break;
    case tsf_mode:
      mask = BIT(1) | BIT(2) | BIT(3);
      mode = (st & mask)>>1;
      if(mode > 5){
        print_val.count_mode = mode - 4;
      }else{
        print_val.count_mode = mode;
      }
      break;
    case tsf_base:
      print_val.bcd= st & BIT(0); 
      break;
    default:
      return 1;
      break;      
  }
  return timer_print_config(timer,field,print_val);
}
