#pragma once
#include "tigr.h"

void graph_func(Tigr * screen, TPixel color, float (*func)(float));
void process_input(Tigr * screen);
void draw_axes(Tigr * screen);

const int screen_width = 640;
const int screen_height = 480;