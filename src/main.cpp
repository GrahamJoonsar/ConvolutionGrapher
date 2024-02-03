#include "tigr.h"
#include "graph_util.hpp"
#include <math.h>

float pi = 3.1415926;
float e = 2.71828183;

float f (float x){
    return 5/(pi * (1 + x*x));
}

float g (float x){
    return 5*powf(e, -x*x);
}

float h (float x){
    return x*sinf(x);
}

int main () {
    Tigr *screen = tigrWindow(screen_width, screen_height, "Convolution Grapher", 0);
    while (!tigrClosed(screen)) {
        tigrClear(screen, tigrRGB(255, 255, 255));

        draw_axes(screen);
        graph_func(screen, tigrRGB(255, 0, 0), h);
        //graph_func(screen, tigrRGB(0, 0, 255), f);

        process_input(screen);

        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}