#include <draw.h>
#include <syscalls.h>

// temp
static int abs(int n) {
    if (n < 0) {
        return -n;
    }
    return n;
}



void draw_line(color_t color, uint64_t startx, uint64_t starty, uint64_t endx, uint64_t endy)
{
    int dx = endx - startx;
    int dy = endy - starty;
    int sx = (dx >= 0) ? 1 : -1;
    int sy = (dy >= 0) ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (startx != endx || starty != endy) {
        draw(color, startx, starty);
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            startx += sx;
        }
        if (e2 < dy) {
            err += dx;
            starty += sy;
        }
    }
    draw(color, endx, endy);
}


void draw_bitmap(color_t color, char *bitmap[], uint16_t rows, uint16_t cols, uint64_t startx, uint64_t starty) {
    uint64_t x = startx;
    uint64_t y = starty;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (bitmap[i][j] == 'X') {
                draw(color, x, y);
            }
            x += PIXEL;
        }
        x = startx;
        y += PIXEL;
    }
}
