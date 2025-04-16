#include <lcom/lcf.h>
#include "graphics.h"

vbe_mode_info_t mode_info;
uint8_t *video_mem;

vbe_mode_info_t get_mode_info() {
  return mode_info;
}

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

uint32_t (direct_model)(uint32_t R, uint32_t G, uint32_t B) {
  return (R << mode_info.RedFieldPosition) | (G << mode_info.GreenFieldPosition) | (B << mode_info.BlueFieldPosition);
}

uint32_t (indexed_model)(uint16_t col, uint16_t row,uint32_t first, uint8_t step, uint8_t n) {
  return (first + (row * n + col) * step) % (1 << mode_info.BitsPerPixel);
}

uint32_t (Red)(unsigned col, uint8_t step, uint32_t first) {
  return (R(first) + col * step) % (1 << mode_info.RedMaskSize);
}

uint32_t (Green)(unsigned row, uint8_t step, uint32_t first) {
  return (G(first) + row * step) % (1 << mode_info.GreenMaskSize);
}

uint32_t (Blue)(unsigned col, unsigned row, uint8_t step, uint32_t first) {
  return (B(first) + (col + row) * step) % (1 << mode_info.BlueMaskSize);
}

uint32_t (R)(uint32_t first){
  return ((1 << mode_info.RedMaskSize) - 1) & (first >> mode_info.RedFieldPosition);
}

uint32_t (G)(uint32_t first){
  return ((1 << mode_info.GreenMaskSize) - 1) & (first >> mode_info.GreenFieldPosition);
}

uint32_t (B)(uint32_t first){
  return ((1 << mode_info.BlueMaskSize) - 1) & (first >> mode_info.BlueFieldPosition);
}

int draw_xpm(xpm_map_t xpm, uint16_t x, uint16_t y) {
  xpm_image_t img;
  uint8_t *map = xpm_load(xpm, XPM_INDEXED, &img);

  if (map == NULL) {
    return -1;
  }

  for (uint16_t i = 0; i < img.height; i++) {
    for (uint16_t j = 0; j < img.width; j++) {
      uint32_t color = map[i * img.width + j];
      draw_pixel(x + j, y + i, color);
    }
  }

  return 0;
}

