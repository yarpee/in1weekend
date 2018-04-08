#pragma once

#include "material.h"

class metal : public material
{
public:
	metal(const vec3& a, float f) : albedo(a)
	{
		if (f < 1)
		{
			fuzz = f;
		}
		else
		{
			fuzz = 1;
		}
	}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + random_in_unit_sphere() * fuzz);	// 镜面反射方向
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

public:
	vec3 albedo;
	float fuzz;
};
