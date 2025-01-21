#!/bin/bash

clang++ main.cpp -o raytracing `sdl2-config --cflags --libs`
