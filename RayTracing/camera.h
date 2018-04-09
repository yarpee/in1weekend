#pragma once

#include "ray.h"

#define _USE_MATH_DEFINES
#include <math.h>

vec3 random_in_unit_disk()
{
	vec3 p;
	do
	{
		p = vec3(drand48(), drand48(), 0) * 2.0 - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}

class camera
{
public:
	//camera()
	//{
	//	origin = vec3(0, 0, 0);
	//	lower_left_corner = vec3(-2, -1, -1);
	//	horizontal = vec3(4, 0, 0);
	//	vertical = vec3(0, 2, 0);
	//}

	camera(float vfov, float aspect)
	{
		float theta = vfov * M_PI / 180;	// camera position is (0, 0, 0), plane z = -1, distance = 1
		float half_height = tan(theta / 2);
		float half_width = half_height * aspect;
		origin = vec3(0, 0, 0);
		lower_left_corner = vec3(-half_width, -half_height, -1);
		horizontal = vec3(2 * half_width, 0, 0);
		vertical = vec3(0, 2 * half_height, 0);
	}

	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
	{
		lens_radius = aperture / 2;
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = half_height * aspect;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = unit_vector(cross(w, u));
		lower_left_corner = origin - u * half_width * focus_dist - v * half_height * focus_dist - w * focus_dist;
		horizontal = u * half_width * 2 * focus_dist;
		vertical = v * half_height * 2 * focus_dist;
	}

	//ray get_ray(float u, float v)
	//{
	//	return ray(origin, lower_left_corner + horizontal * u + vertical * v - origin);
	//}

	ray get_ray(float s, float t)
	{
		vec3 rd = random_in_unit_disk() * lens_radius;
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin + offset, lower_left_corner + horizontal * s + vertical * t - origin - offset);
	}

public:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lens_radius;
};
