// CS 248 Denoiser Project(masoudc, kenhong) : Ray - Tracing Implementation
// Reference: Ray Tracing in One Weekend (Peter Shirley)// Reference: Ray Tracing in One Weekend (Peter Shirley)

#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

class camera {
public:
    camera(
        point3 lookfrom,
        point3 lookat,
        vec3   vup,
        double vfov, 
        double aspect_ratio,
        double aperture,
        double focus_dist
    ) {
        auto t = degrees_to_radians(vfov);
        auto h = tan(t / 2);
        auto vh = 2.0 * h;
        auto vw = aspect_ratio * vh;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * vw * u;
        vertical = focus_dist * vh * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;
    }


    ray get_ray(double s, double t) const {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        return ray(
            origin + offset,
            lower_left_corner + s * horizontal + t * vertical - origin - offset
        );
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
};
#endif