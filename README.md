# Raytracing

A real-time raytracing simulation implemented in C++ with SDL2.

## Building and Running
```bash
chmod +x build.sh
./build.sh
./raytracing
```

## Controls
- W/S: Move camera forward/backward
- A/D: Move camera left/right  
- Q/E: Move camera up/down
- R: Reset camera position and scene
- ESC or close window: Exit simulation

## Features
- Real-time raytracing with sphere primitives
- Interactive camera movement
- Basic lighting with Lambertian shading
- Scene with colored spheres and ground plane

## File Organization
- main.cpp: Application entry point and SDL setup
- raytracing_simulation.hpp/cpp: Core raytracing implementation  
- error_management.hpp: Error handling utilities
- formats.hpp: Global variable declarations
