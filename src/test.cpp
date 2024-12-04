#include "../lib/fbcanvas.hpp"
#include <iostream>

int main() {
    printf("Creating canvas\n");
    FBCanvas canvas = FBCanvas("/dev/fb1");
    printf("Filling canvas\n");
    canvas.fill(0xFF0000);
    for (int row = 0; row < canvas.height; row++) {
        for (int col = 0; col < canvas.width; col++) {

        }
    }
}