#include "syscalls.h"
#include "io.h"
#include "keyboard.h"
#include "sound.h"
#include "time.h"
#include "video.h"
#include <exceptions.h>
#include <lib.h>
#include <naiveConsole.h>

#define REGS_SIZE 19

static uint8_t regs_flag = 0;
static uint64_t regs[REGS_SIZE];

// Cast to a function pointer
typedef uint64_t (*syscall_t)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

// Array of function pointers
static syscall_t syscalls[] = {
    (syscall_t)&sys_read, // sys_id 0
    (syscall_t)&sys_write, // sys_id 1
    (syscall_t)&pid, // sys_id 2
    (syscall_t)&sys_exec, // sys_id 3
    (syscall_t)&sys_ticks, // sys_id 4
    (syscall_t)&sys_seconds, // sys_id 5
    (syscall_t)&sys_random_number, // sys_id 6
    (syscall_t)&sys_read_char, // sys_id 7
    (syscall_t)&draw, // sys_id 8
    (syscall_t)&sys_sleep, // sys_id 9
    (syscall_t)&sys_time, // sys_id 10
    (syscall_t)&sys_sound, // sys_id 11
    (syscall_t)&sys_hlt, // sys_id 12
    (syscall_t)&sys_clear, // sys_id 13
    (syscall_t)&sys_writing_position, // sys_id 14
    (syscall_t)&screen_info, // sys_id 15
    (syscall_t)&font_size, // sys_id 16
    (syscall_t)&sys_registers // sys_id 17
};

uint64_t syscall_dispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {

    syscall_t syscall = syscalls[r9];
    if (syscall != 0) {
        return syscall(rdi, rsi, rdx, rcx, r8);
    }
    return 0;
}

uint64_t sys_write(uint8_t fd, const char *buffer, uint64_t count, uint64_t fgcolor, uint64_t bgcolor) {
    if (buffer == 0) {
        return 0;
    }

    // stdout
    if (fd == 1) {
        return printf_color(buffer, fgcolor, bgcolor);
    }

    // stderr
    else if (fd == 2)
        return printf_color(buffer, 0xFF, 0x40);

    return 0;
}

char *sys_read(uint8_t fd, char *buffer, uint64_t count) {
    get_buffer(buffer, count);

    return 0;
}

char sys_read_char() {
    hlt();
    return get_last_input();
}

uint64_t pid() {
    return 0;
}
void sys_exec() {
}

uint64_t sys_ticks() {
    return ticks_elapsed();
}

uint64_t sys_seconds() {
    return seconds_elapsed();
}

uint64_t sys_random_number(int seed) {
    return get_random_number(seed);
}

void draw(uint32_t color, uint64_t posx, uint64_t posy) {
    // pixel is 8x8
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            put_pixel(color, posx + j, posy + i);
        }
    }
}

char *sys_time() {
    // in format: hh:mm:ss
    static char time[9];
    uint32_t hours = getHours();
    uint32_t minutes = getMinutes();
    uint32_t seconds = getSeconds();

    char hh[3], mm[3], ss[3];
    itoa(hh, hours, 2);
    itoa(mm, minutes, 2);
    itoa(ss, seconds, 2);

    // Format the time string as "hh:mm:ss"
    time[0] = hh[0];
    time[1] = hh[1];
    time[2] = ':';
    time[3] = mm[0];
    time[4] = mm[1];
    time[5] = ':';
    time[6] = ss[0];
    time[7] = ss[1];
    time[8] = '\0';

    return time;
}

void sys_sleep(uint64_t millis) {
    sleep(millis);
}

void sys_sound(uint8_t freq, uint64_t duration) {
    start_sound(freq, duration);
}

void sys_hlt() {
    hlt();
}

void sys_clear(uint32_t color) {
    clear(color);
}

void sys_writing_position(uint64_t x, uint64_t y) {
    set_position(x, y);
}

void screen_info(uint64_t *width, uint64_t *height) {
    *width = get_width();
    *height = get_height();
}

void font_size(int size) {
    video_fontsize(size);
}

void sys_registers() {
    print_regs(regs_flag ? regs : (uint64_t *)0);
    regs_flag = 0;
}

void save_registers(uint64_t *stack) {
    regs_flag = 1;
    for (int i = 0; i < REGS_SIZE; i++){
        regs[i] = stack[i];
    }
}