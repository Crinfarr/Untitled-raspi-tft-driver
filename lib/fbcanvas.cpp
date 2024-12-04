#include "fbcanvas.hpp"
using namespace std;
uint16_t FBCanvas::toRgb565(uint32_t color) {
    uint8_t R, G, B;
    uint16_t oColor = 0b0000000000000000;
    R = (color & 0xff0000) >> 16;
    G = (color & 0x00ff00) >> 8;
    B = (color & 0x0000ff);
    uint8_t bR = (uint8_t)round(((float)R / 255.0f) * 0b11111);
    uint8_t bG = (uint8_t)round(((float)G / 255.0f) * 0b111111);
    uint8_t bB = (uint8_t)round(((float)B / 255.0f) * 0b11111);
    oColor |= bR << 11;
    oColor |= bG << 5;
    oColor |= bB;
    return oColor;
}

//framebuffers are usually stored in /dev/fb0, /dev/fb1, [...] /dev/fbn
FBCanvas::FBCanvas(const char* fbpath) {
    framebufferDesc = open(fbpath, O_RDWR);
    if (framebufferDesc < 0)
        throw "Could not open framebuffer";

    if (ioctl(framebufferDesc, FBIOGET_VSCREENINFO, &varInfo) < 0)
        throw "Could not get vscreeninfo";
    
    if (ioctl(framebufferDesc, FBIOGET_FSCREENINFO, &fixInfo) < 0)
        throw "Could not get fscreeninfo";

    width = varInfo.xres;
    height = varInfo.yres;

    colordepth = varInfo.bits_per_pixel;

    screenBytes = (width * height * colordepth) / 8;
    blockCount = screenBytes / 2;

    //.DEBUG
    // printf("Framebuffer stats:\n\tWidth: %i\n\tHeight: %i\n\tColor depth: %i\n\tBytes: %i\n\tBlocks:%i\n", width, height, colordepth, screenBytes, blockCount);
    frameBuffer = (uint16_t*)mmap(NULL, screenBytes, PROT_READ | PROT_WRITE, MAP_SHARED, framebufferDesc, (off_t)0);
}
//TODO: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
//void FBCanvas::drawLine(const POINT ptA, const POINT ptB)

//TODO: https://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
//void FBCanvas::drawTri(const POINT ptA, const POINT ptB, const POINT ptC, uint32_t color)