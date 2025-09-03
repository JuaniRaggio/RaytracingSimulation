#!/bin/bash

clang++ main.cpp src/raytracing_simulation.cpp -o raytracing `sdl2-config --cflags --libs`
