
typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr vbe_mode_info = (VBEInfoPtr) 0x0000000000005C00

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y){
    uint8_t * frameBuffer = vbe_mode_info -> frameBuffer;
    uint64_t offset = (x * ((vbe_mode_info->bpp)/8)) + (y * (vbe_mode_info->pitch));
    frameBuffer[offset] = (hexColor) & 0xFF 
    frameBuffer[offset+1] = (hexColor >> 8) & 0xFF
    frameBuffer[offset+2] = (hexColor >> 16) & 0xFF
}