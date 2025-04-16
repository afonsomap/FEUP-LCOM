// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "kbc.h"
#include "kbd.h"
#include "i8042.h"
#include "utils.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

    set_video_mode(mode); 

    sleep(delay);

    vg_exit();
    
    return 0;
}

int wait_for_ESC_press(){
  uint8_t bit_no = 0;
  int ipc_status,r;
  message msg;

  if (kbd_subscribe_int(&bit_no)!=0) {
    printf("Failed to subscribe kbd interrupts.\n");
    return 1;
  }

  uint32_t irq_set = BIT(bit_no);

  uint8_t* scancode = get_scancode();

  while(*scancode != ESC_BREAKCODE) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
          }
          break;
        default:
          break; 
      }
    }
  }
  if (kbd_unsubscribe_int()!=0) {return 1;}
  return 0;
}


int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

  map_graphics_vram(mode);
  set_video_mode(mode);

  draw_rectangle(x, y, width, height, color);

  if (wait_for_ESC_press() != 0) {
    printf("Failed to wait for ESC press.\n");
    return 1;
  }

  vg_exit();

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  map_graphics_vram(mode);
  set_video_mode(mode);
  
  vbe_mode_info_t mode_info = get_mode_info();

  int rectangle_vertical_size = mode_info.YResolution / no_rectangles;
  int rectangle_horizontal_size = mode_info.XResolution / no_rectangles;

  for (int row = 0; row < no_rectangles; row++) {
    for (int col = 0; col < no_rectangles; col++) {

      uint32_t final_color;

      if (mode_info.MemoryModel == DIRECT_MODEL){

        uint32_t R = Red(col, step, first);
        uint32_t G = Green(row, step, first);
        uint32_t B = Blue(col, row, step, first);

        final_color = direct_model(R, G, B);

      }else if( mode_info.MemoryModel == INDEXED_MODEL){

        final_color = indexed_model(col, row, first, step, no_rectangles);

      }else{
        panic("Invalid Memory Model");
      }

      draw_rectangle(col * rectangle_horizontal_size, row * rectangle_vertical_size, rectangle_horizontal_size, rectangle_vertical_size, final_color);
    }
  }

  if (wait_for_ESC_press() != 0) {
    printf("Failed to wait for ESC press.\n");
    return 1;
  }

  vg_exit();

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  map_graphics_vram(VBE_768p_INDEXED);
  set_video_mode(VBE_768p_INDEXED);

  if ( draw_xpm(xpm, x, y) == 1 ) {
    printf("Failed to draw xpm.\n");
    return 1;
  }

  if (wait_for_ESC_press() != 0) {
    printf("Failed to wait for ESC press.\n");
    return 1;
  }

  vg_exit();
  
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
