#include <lcom/lcf.h>
#include "vbe.h"

vbe_mode_info_t mode_info;
uint8_t *video_mem;

void set_video_mode(uint16_t mode) {
  struct reg86 args;
  memset(&args, 0, sizeof(args)); 
  args.ah = 0x4F; // VBE function
  args.al = 0x02; // "set mode" function
  args.bx = BIT(14) | mode; 
  args.intno = 0x10; // BIOS video service
  sys_int86(&args);

  if (args.al != 0x4F || args.ah != 0x00) panic("VBE call failed");
}

void map_graphics_vram(uint16_t mode) {
  vbe_get_mode_info(mode, &mode_info); 

  struct minix_mem_range mr;
  memset(&mr, 0, sizeof(mr));
  mr.mr_base = (phys_bytes)mode_info.PhysBasePtr;
  mr.mr_limit = mr.mr_base + mode_info.BytesPerScanLine * mode_info.YResolution;

  // Request permission for our process to map memory
  sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr);

  // Map memory
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, mr.mr_limit - mr.mr_base);
}

void draw_pixel(uint16_t x, uint16_t y, uint32_t color) {
  if (x >= mode_info.XResolution || y >= mode_info.YResolution) {
    panic("invalid coordinate"); 
  }

  unsigned bytesPixel = (mode_info.BitsPerPixel + 7) / 8;
  
  unsigned int index = (mode_info.XResolution * y + x) * bytesPixel;

  if (memcpy(video_mem + index, &color, bytesPixel) == NULL) {
    panic("memcpy failed");
  }
}

void draw_hline(uint16_t x, uint16_t y, uint16_t length, uint32_t color) {
  for (uint16_t i = 0; i < length; i++) {
    draw_pixel(x + i, y, color);
  }
}

void draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (uint16_t i = 0; i < height; i++) {
    draw_hline(x, y + i, width, color);
  }
}
