#ifndef __FB_CANVAS
#define __FB_CANVAS

//sys utils
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
//c utils
#include <unistd.h>
#include <stdint.h>
#include <cmath>
#include <iostream>
#include <string.h>
#include <array>
#include <algorithm>

#define POINT array<int, 2>
class FBCanvas {
protected:
    //converts from hex colors to RGB565 16-bit colors
    static uint16_t toRgb565(uint32_t color);
    static uint16_t toRgb565LE(uint32_t color) {
        return swapEnd(toRgb565(color));
    }
    //swaps the endianness of a uint16_t
    static inline uint16_t swapEnd(uint16_t num) {
        return (num & 0xff00) >> 8 | (num & 0x00ff) << 8;
    }

    uint16_t* frameBuffer;
    int colordepth;
    int screenBytes;
    int blockCount;
private:
    int framebufferDesc;
    struct fb_var_screeninfo varInfo;
    struct fb_fix_screeninfo fixInfo;


public:
    int width;
    int height;
    inline void fill(uint32_t color) {
        uint16_t col = toRgb565(color);
        for (int i = 0; i < blockCount; i++) {
            //.DEBUG
            //printf("%i\n", i);
            frameBuffer[i] = col;
        }
    };
    inline void setPt(int x, int y, uint32_t color) {
        frameBuffer[(y * width) + x] = toRgb565(color);
    }
    void drawTri(const POINT ptA, const POINT ptB, const POINT ptC, uint32_t color);//TODO
    void drawLine(const POINT ptA, const POINT ptB, uint32_t color);//TODO
    FBCanvas(const char* fbPath);
    ~FBCanvas() {
        if (munmap(frameBuffer, screenBytes) < 0) {
            std::cerr << "Could not deallocate frame buffer" << std::endl;
        }
        close(framebufferDesc);
    };
};
#endif