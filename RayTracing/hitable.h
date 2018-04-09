#pragma once

#include "ray.h"

#define M 0x100000000LL
#define C 0xB16
#define A 0x5DEECE66DLL

static unsigned long long seed = 1;

double drand48()
{
	seed = (A * seed + C) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return  ((double)x / (double)M);
}

//float drand48()
//{
//	int i = rand() % 100;
//	return float(i) / 100.0;
//}

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
		refracted = (unit_in - normal * cos) * ni_over_nt - normal * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
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
