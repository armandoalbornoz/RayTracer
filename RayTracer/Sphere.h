#pragma once
#include <vector>
#include <Eigen/Dense>
#include "Ray.h"

using Eigen::Vector3d;

class Sphere
{
	Vector3d center;
	double radius;

public: 

	Sphere(Vector3d center, double radius)
	{
		this->center = center;
		this->radius = radius;
	}

	// Utilize Algebra to find the intersection of a ray and the sphere, we return a vector with the t values that give the intersection points
	// these the first value will always be the smaller t.
	std::vector<double> hitSphere(const Ray& ray)
	{
		std::vector<double> tOfIntersection;

		Vector3d e =  ray.getOrigin();
		Vector3d d = ray.getDirection();

		double A = d.dot(d);
		double B = 2 * (d.dot((e - center)));
		double C = (e - center).dot((e- center)) - (radius * radius);

		double determinant = (B * B) - (4 * A * C);

		if (determinant < 0)
		{
			return tOfIntersection;
		}
		else if (determinant == 0)
		{
			double t = -B / (2 * A);
			tOfIntersection.emplace_back(t);
			return tOfIntersection;
		}
		else
		{

			double t_1 = (-B + sqrt(determinant)) / (2 * A);
			double t_2 = (-B - sqrt(determinant)) / (2 * A);

			tOfIntersection.emplace_back(t_1);
			tOfIntersection.emplace_back(t_2);

			std::sort(tOfIntersection.begin(), tOfIntersection.end());

			return tOfIntersection;
		}

	}


	void test_Sphere()
	{
		std::cout << "center:  (" << center.x() << "," << center.y() << "," << center.z() << ")" << std::endl;
		std::cout << "radius :" << radius << std::endl;
	}


};