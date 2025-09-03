#include "../include/raytracing_simulation.hpp"
#include <algorithm>

Raytracing::Raytracing() : camera_pos(0, 0, 0), camera_target(0, 0, -1), camera_up(0, 1, 0), fov(45.0) {
    setup_scene();
}

void Raytracing::start_simulation(void) {
    current_status = RUNNING_SIMULATION;
}

const simulation_status& Raytracing::get_status(void) const {
    return current_status;
}

void Raytracing::setup_scene() {
    spheres.clear();
    spheres.push_back(Sphere(Vec3(0, 0, -5), 1.0, Vec3(1, 0, 0)));
    spheres.push_back(Sphere(Vec3(-2, 0, -5), 0.8, Vec3(0, 1, 0)));
    spheres.push_back(Sphere(Vec3(2, 0, -5), 0.6, Vec3(0, 0, 1)));
    spheres.push_back(Sphere(Vec3(0, -100.5, -5), 100, Vec3(0.5, 0.5, 0.5)));
}

Vec3 Raytracing::ray_color(const Ray& ray) {
    double closest_t = 1e30;
    Sphere* closest_sphere = nullptr;
    
    for (auto& sphere : spheres) {
        double t;
        if (sphere.intersect(ray, t) && t < closest_t) {
            closest_t = t;
            closest_sphere = &sphere;
        }
    }
    
    if (closest_sphere) {
        Vec3 hit_point = ray.at(closest_t);
        Vec3 normal = (hit_point - closest_sphere->center).normalize();
        Vec3 light_dir = Vec3(0.5, 1, 0.5).normalize();
        double light_intensity = std::max(0.1, normal.dot(light_dir));
        return closest_sphere->color * light_intensity;
    }
    
    Vec3 unit_direction = ray.direction.normalize();
    double t = 0.5 * (unit_direction.y + 1.0);
    return Vec3(1.0, 1.0, 1.0) * (1.0 - t) + Vec3(0.5, 0.7, 1.0) * t;
}

void Raytracing::render_frame(SDL_Surface* surface) {
    if (SDL_MUSTLOCK(surface)) {
        SDL_LockSurface(surface);
    }
    
    Uint32* pixels = (Uint32*)surface->pixels;
    int width = surface->w;
    int height = surface->h;
    
    double aspect_ratio = double(width) / height;
    double viewport_height = 2.0 * tan((fov * M_PI / 180.0) / 2);
    double viewport_width = aspect_ratio * viewport_height;
    
    Vec3 w = (camera_pos - camera_target).normalize();
    Vec3 u = camera_up.dot(Vec3(w.y * camera_up.z - w.z * camera_up.y, 
                                 w.z * camera_up.x - w.x * camera_up.z,
                                 w.x * camera_up.y - w.y * camera_up.x)) > 0 ?
             Vec3(w.y * camera_up.z - w.z * camera_up.y,
                  w.z * camera_up.x - w.x * camera_up.z,
                  w.x * camera_up.y - w.y * camera_up.x).normalize() :
             Vec3(camera_up.y * w.z - camera_up.z * w.y,
                  camera_up.z * w.x - camera_up.x * w.z,
                  camera_up.x * w.y - camera_up.y * w.x).normalize();
    Vec3 v = Vec3(w.y * u.z - w.z * u.y,
                  w.z * u.x - w.x * u.z,
                  w.x * u.y - w.y * u.x);
    
    Vec3 horizontal = u * viewport_width;
    Vec3 vertical = v * viewport_height;
    Vec3 lower_left_corner = camera_pos - horizontal * 0.5 - vertical * 0.5 - w;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double u_coord = double(x) / (width - 1);
            double v_coord = double(height - 1 - y) / (height - 1);
            
            Vec3 direction = lower_left_corner + horizontal * u_coord + vertical * v_coord - camera_pos;
            Ray ray(camera_pos, direction.normalize());
            
            Vec3 color = ray_color(ray);
            
            Uint8 r = (Uint8)(std::min(255.0, color.x * 255.0));
            Uint8 g = (Uint8)(std::min(255.0, color.y * 255.0));
            Uint8 b = (Uint8)(std::min(255.0, color.z * 255.0));
            
            pixels[y * width + x] = SDL_MapRGB(surface->format, r, g, b);
        }
    }
    
    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
}

void Raytracing::move_camera(double dx, double dy, double dz) {
    camera_pos = camera_pos + Vec3(dx, dy, dz);
}

void Raytracing::rotate_camera(double yaw, double pitch) {
    double cos_yaw = cos(yaw);
    double sin_yaw = sin(yaw);
    double cos_pitch = cos(pitch);
    double sin_pitch = sin(pitch);
    
    camera_target = Vec3(cos_yaw * cos_pitch, sin_pitch, sin_yaw * cos_pitch);
}

void Raytracing::manage_event(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_w: move_camera(0, 0, -0.1); break;
                case SDLK_s: move_camera(0, 0, 0.1); break;
                case SDLK_a: move_camera(-0.1, 0, 0); break;
                case SDLK_d: move_camera(0.1, 0, 0); break;
                case SDLK_q: move_camera(0, 0.1, 0); break;
                case SDLK_e: move_camera(0, -0.1, 0); break;
                case SDLK_r: setup_scene(); camera_pos = Vec3(0, 0, 0); break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            break;
        case SDL_QUIT:
            current_status = END_SIMULATION;
            break;
    }
}
