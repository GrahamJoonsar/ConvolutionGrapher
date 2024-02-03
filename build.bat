@echo off

echo Starting Build
g++ src/tigr.c src/main.cpp src/graph_util.cpp -lopengl32 -lgdi32 -o build/ConvolutionGrapher
echo Build Complete