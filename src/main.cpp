#include "main.hpp"

using namespace std;
int main() {
    for (unsigned char i = 0; i < 255; i++) {
        printf("%i [8b]  \t%i [5b]\t%i [6b]\n", i, (unsigned char)round(((float)i / (float)255) * 0b11111), (unsigned char)round(((float)i / (float)255) * 0b111111));
    }
}