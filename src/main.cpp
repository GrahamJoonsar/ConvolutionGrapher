#include "tigr.h"
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

const int screen_width = 640;
const int screen_height = 480;

int points = 1000;

float upper_y = 10;
float lower_y = -10;
float upper_x = 10;
float lower_x = -10;

float current_x = 0;
float current_y = 0;

void graph_func(Tigr * screen, TPixel color, float (*func)(float)){
    // Getting the initial points, as we have to draw lines between 
    // each of these, (x, f(x)) is the point
    float past_x = -(upper_x-lower_x)/2 + current_x;
    float past_y = func(past_x);

    past_x = (past_x - current_x)/(upper_x-lower_x)*screen_width+screen_width/2;
    past_y = (past_y - current_y)/(lower_y-upper_y)*screen_height+screen_height/2;

    for (int i = 1; i <= points; i++){
        // Find the new position on the function
        float new_x = i*(upper_x-lower_x)/points - (upper_x-lower_x)/2 + current_x;
        float new_y = func(new_x);

        // Transform to points on the screen
        new_x = (new_x - current_x)/(upper_x-lower_x)*screen_width+screen_width/2;
        new_y = (new_y - current_y)/(lower_y-upper_y)*screen_height+screen_height/2;

        // Drawing the line on the screen
        tigrLine(screen, past_x, past_y, new_x, new_y, color);
        past_x = new_x;
        past_y = new_y;
    }
}

void process_input(Tigr * screen){
    // Moving the graph around
    if (tigrKeyHeld(screen, TK_LEFT)) current_x -= (upper_x-lower_x)/100;
    if (tigrKeyHeld(screen, TK_RIGHT)){
        current_x += (upper_x-lower_x)/100;
    }
    if (tigrKeyHeld(screen, TK_UP)){
        current_y += (upper_y-lower_y)/100;
    }
    if (tigrKeyHeld(screen, TK_DOWN)){
        current_y -= (upper_y-lower_y)/100;
    }

    // Zooming out
    if (tigrKeyHeld(screen, TK_PADSUB)){
        float dy = log10f(upper_y - lower_y)/10;
        upper_y += dy;
        lower_y -= dy;

        float dx = log10f(upper_x-lower_x)/10;
        upper_x += dx;
        lower_x -= dx;
    }

    // Zooming in
    if (tigrKeyHeld(screen, TK_PADADD)){
        float dy = log10f(upper_y - lower_y)/10;
        upper_y -= dy;
        lower_y += dy;

        float dx = log10f(upper_x-lower_x)/10;
        upper_x -= dx;
        lower_x += dx;
    }
}

void draw_axes(Tigr * screen){
    // Horizontal
    float y_axis = ((current_y)/(upper_y-lower_y) + 0.5) * screen_height;
    tigrLine(screen, 0, y_axis, screen_width, y_axis, tigrRGB(0, 0, 0));
    // Vertical
    float x_axis = ((-current_x)/(upper_x-lower_x) + 0.5) * screen_width;
    tigrLine(screen, x_axis, 0, x_axis, screen_height, tigrRGB(0, 0, 0));
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