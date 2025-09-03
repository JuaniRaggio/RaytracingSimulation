#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include "formats.hpp"

// This file has the functions and methods in charge of administrating the tecnical side of the simulation

typedef enum {END_SIMULATION = 0, RUNNING_SIMULATION} simulation_status;

struct Vec3 {
    double x, y, z;
    Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(double t) const { return Vec3(x * t, y * t, z * t); }
    double dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 normalize() const { double len = sqrt(x*x + y*y + z*z); return Vec3(x/len, y/len, z/len); }
    double length() const { return sqrt(x*x + y*y + z*z); }
};

struct Ray {
    Vec3 origin, direction;
    Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d) {}
    Vec3 at(double t) const { return origin + direction * t; }
};

struct Sphere {
    Vec3 center;
    double radius;
    Vec3 color;
    Sphere(const Vec3& c, double r, const Vec3& col) : center(c), radius(r), color(col) {}
    
    bool intersect(const Ray& ray, double& t) const {
        Vec3 oc = ray.origin - center;
        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double c = oc.dot(oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;
        
        if (discriminant < 0) return false;
        
        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        
        if (t1 > 0.001) {
            t = t1;
            return true;
        } else if (t2 > 0.001) {
            t = t2;
            return true;
        }
        return false;
    }
};

class Raytracing {
  private:
    simulation_status current_status {END_SIMULATION};
    Vec3 camera_pos;
    Vec3 camera_target;
    Vec3 camera_up;
    double fov;
    std::vector<Sphere> spheres;
    
  public:
    Raytracing();
    const simulation_status& get_status(void) const;
    void start_simulation(void);
    void manage_event(SDL_Event event);
    void render_frame(SDL_Surface* surface);
    Vec3 ray_color(const Ray& ray);
    void setup_scene();
    void move_camera(double dx, double dy, double dz);
    void rotate_camera(double yaw, double pitch);
};
