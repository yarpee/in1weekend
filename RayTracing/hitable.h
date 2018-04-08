#pragma once

#include "ray.h"

float drand48()
{
	int i = rand() % 100;
	return float(i) / 100.0;
}

vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = vec3(drand48(), drand48(), drand48()) * 2.0 - vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);
	return p;
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - n * 2 * dot(v, n);
}

bool refract(const vec3& in, const vec3& normal, float ni_over_nt, vec3& refracted)
{
	vec3 unit_in = unit_vector(in);
	float cos = dot(unit_in, normal);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - cos * cos);	// cos'*cos' = 1-(n/n')*(n/n')*sin*sin
	if (discriminant > 0)
	{
		refracted = (in - normal * cos) * ni_over_nt - normal * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

class material;

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material* mat_ptr;
};

class hitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};
