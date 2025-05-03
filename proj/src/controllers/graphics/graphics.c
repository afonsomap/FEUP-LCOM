#include <lcom/lcf.h>
#include "graphics.h"

static vbe_mode_info_t mode_info;
static uint8_t *video_mem;
static uint8_t *buffer;

vbe_mode_info_t get_mode_info() {
  return mode_info;
}

void set_video_mode(uint16_t mode) {
  struct reg86 args;
  memset(&args, 0, sizeof(args)); 
  args.ah = 0x4F; // VBE function
  args.al = 0x02; // "set mode" function
  args.bx = VBE_LINEAR_FB | mode; 
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

void allocate_buffer(){
  buffer = (uint8_t *)malloc(mode_info.BytesPerScanLine * mode_info.YResolution); 
  if (buffer == NULL) {
    panic("Failed to allocate buffer");
  }
}

void copy_buffer_vram(){
  memcpy(video_mem, buffer, mode_info.BytesPerScanLine * mode_info.YResolution); 
}

void free_buffer(){
  if (buffer != NULL) {
    free(buffer);
    buffer = NULL;
  }  
}

void clear_buffer(){
  memset(buffer, 0, mode_info.BytesPerScanLine * mode_info.YResolution); 
}

void draw_pixel(uint16_t x, uint16_t y, uint32_t color) {
  if (x >= mode_info.XResolution || y >= mode_info.YResolution) {
    panic("Coordinates out of bounds");
  }

  unsigned bytesPixel = (mode_info.BitsPerPixel + 7) / 8;
  
  unsigned int index = (mode_info.XResolution * y + x) * bytesPixel;

  if (color == CHROMA_KEY_GREEN_888) { // Preciso definir uma cor para o transparente
    return; // Skip drawing transparent color
  }

  if (memcpy(buffer + index, &color, bytesPixel) == NULL) {
    panic("Failed to copy color to video memory");
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

int vg_draw_xpm(uint8_t* xpm_map, uint16_t x, uint16_t y, uint16_t width, uint16_t height){
  if (xpm_map == NULL) {
    return 1;
  }

  unsigned bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;

  for (uint16_t i = 0; i < height; i++) {
    for (uint16_t j = 0; j < width; j++) {

      unsigned int index = (i * width + j) * bytes_per_pixel;

      uint32_t color = 0;
      memcpy(&color, &xpm_map[index], bytes_per_pixel);

      draw_pixel(x + j, y + i, color);
    }
  }

  return 0;
}

