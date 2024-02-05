#pragma once
#include <vector>
#include <Eigen/Dense>
#include "Surface.h"
#include "Ray.h"


using Eigen::Vector3d;

class Sphere : public Surface
{
	Vector3d center;
	double radius;

public: 


	Sphere(const Vector3d& center, double radius) : center(center), radius(radius){}

	// Utilize Algebra to find the intersection of a ray and the sphere, and make sure the intersection is between the min t and max t
	bool hit(const Ray& ray, double t_min, double t_max, Record& rec, const LightSource& light)  const override
	{
		Vector3d e =  ray.getOrigin();
		Vector3d d = ray.getDirection();

		double A = d.dot(d);
		double B = 2 * (d.dot((e - center)));
		double C = (e - center).dot((e- center)) - (radius * radius);

		double discriminant = (B * B) - (4 * A * C);

		if (discriminant < 0)
		{
			return false;
		}
		else if (discriminant == 0)
		{
			double t = -B / (2 * A);

			if (t <= t_min || t_max <= t)
			{
				return false;
			}

			return true;

		}
		else
		{
			double sqrtDis = sqrt(discriminant);
			double t = (-B - sqrtDis) / (2 * A);

			if (t <= t_min || t_max <= t) {
				
				t = (-B + sqrtDis) / (2 * A);

				if (t <= t_min || t_max <= t)
				{
					return false;

				}
			}

			// Store the hit information, notice that t is the smallest t.
			// Also store normal vector in direction of light
			rec.t = t;
			rec.point_hit = ray.evaluate(t);
			rec.normal_to_point = (rec.point_hit - center) / radius;
			rec.light_direction = (light.position - rec.point_hit).normalized();

			return true;
		}

	}


	void test_Sphere()
	{
		std::cout << "center:  (" << center.x() << "," << center.y() << "," << center.z() << ")" << std::endl;
		std::cout << "radius :" << radius << std::endl;
	}


};