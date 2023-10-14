#include "video.h"
#include "font.h"

struct vbe_mode_info_structure
{
  uint16_t
      attributes;       // deprecated, only bit 7 should be of interest to you, and it
                        // indicates the mode supports a linear frame buffer.
  uint8_t window_a;     // deprecated
  uint8_t window_b;     // deprecated
  uint16_t granularity; // deprecated; used while calculating bank numbers
  uint16_t window_size;
  uint16_t segment_a;
  uint16_t segment_b;
  uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode
                         // without returning to real mode
  uint16_t pitch;        // number of bytes per horizontal line
  uint16_t width;        // width in pixels
  uint16_t height;       // height in pixels
  uint8_t w_char;        // unused...
  uint8_t y_char;        // ...
  uint8_t planes;
  uint8_t bpp;   // bits per pixel in this mode
  uint8_t banks; // deprecated; total number of banks in this mode
  uint8_t memory_model;
  uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may
                     // be 16 KB...
  uint8_t image_pages;
  uint8_t reserved0;

  uint8_t red_mask;
  uint8_t red_position;
  uint8_t green_mask;
  uint8_t green_position;
  uint8_t blue_mask;
  uint8_t blue_position;
  uint8_t reserved_mask;
  uint8_t reserved_position;
  uint8_t direct_color_attributes;

  uint32_t framebuffer; // physical address of the linear frame buffer; write
                        // here to draw to the screen
  uint32_t off_screen_mem_off;
  uint16_t off_screen_mem_size; // size of memory in the framebuffer but not
                                // being displayed on the screen
  uint8_t reserved1[206];
} __attribute__((packed));


typedef struct vbe_mode_info_structure *VBEInfoPtr;

VBEInfoPtr vbe_mode_info = (VBEInfoPtr)0x0000000000005C00;


// Check if the posx of the pixel is out of the screens width
static char posx_out_screen(uint64_t x)
{
  return x + FONT_WIDTH - 1 >= vbe_mode_info->width;
}

// Check if the posx of the pixel is out of the screens height
static char posy_out_screen(uint64_t y)
{
  return y + FONT_HEIGHT - 1 >= vbe_mode_info->height;
}


// 8 x 16 pixels
void put_char_at(unsigned char c, uint64_t *x, uint64_t *y, uint64_t fgcolor, uint64_t bgcolor)
{
  // rx and ry are the "real values"
  // *y += FONT_HEIGHT; // 12 is baseline, 4 is padding
  if (posx_out_screen(*x)) {
      *x = 0;
      *y += FONT_HEIGHT;
  }

  if (posy_out_screen(*y)) {
      // scroll the screen up
      *y--;
  }

  uint64_t cx, cy;
  unsigned char *bm_char = get_char_bitmap(c);

  for (cy = 0; cy < FONT_HEIGHT; cy++)
  {
    for (cx = 0; cx < FONT_WIDTH; cx++)
    {
      put_pixel((bm_char[cy] & 1 << (FONT_WIDTH - cx - 1)) ? fgcolor : bgcolor, *x + cx, *y + cy + 12); // 12 is baseline
    }
  }
  *x += FONT_WIDTH;
}


void draw_cursor(uint64_t x, uint64_t y, uint64_t fgcolor, uint64_t bgcolor)
{
  // put_char_at('_', x, y, fgcolor, bgcolor);
}

void delete_char(uint64_t *x, uint64_t *y, uint64_t fgcolor, uint64_t bgcolor)
{
  
  *x -= FONT_WIDTH;
  put_char_at(' ', x, y, fgcolor, bgcolor);
  *x -= FONT_WIDTH;
}

void put_pixel(uint32_t hexColor, uint64_t x, uint64_t y)
{
  uint8_t *frameBuffer = (uint8_t *)vbe_mode_info->framebuffer;
  uint64_t offset =
      (x * ((vbe_mode_info->bpp) / 8)) + (y * (vbe_mode_info->pitch));
  frameBuffer[offset] = (hexColor)&0xFF;
  frameBuffer[offset + 1] = (hexColor >> 8) & 0xFF;
  frameBuffer[offset + 2] = (hexColor >> 16) & 0xFF;
}
