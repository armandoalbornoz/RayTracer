#pragma once
#include <vector>
#include <Eigen/Dense>
#include "Surface.h"
#include "Ray.h"
#include <iostream>



class Plane : public Surface
{
	Vector3d p; // A point on the plane
	Vector3d n; // A normal to the plane

public:


	Plane(const Vector3d& p, const Vector3d& n, Vector3d diffuseCoefficient, Vector3d specularCoefficient, Vector3d ambientCoefficient,Vector3d mirrorCoefficient) :
		p(p), n(n), Surface(diffuseCoefficient, specularCoefficient, ambientCoefficient, mirrorCoefficient) {}

	bool hit(const Ray& ray, double t_min, double t_max,  Record& rec, const LightSource& light)  const override
	{
		double denominator = ray.getDirection().dot(n);

		if (denominator == 0) 
		{ 
			//std::cout << "Ray is parallel to plane." << std::endl;
			return false;
		}

		double t = (p.dot(n) - ray.getOrigin().dot(n)) / (ray.getDirection().dot(n));

		if (t <= t_min || t_max <=t)
		{
			return false;
		}

		rec.t = t;
		rec.point_hit = ray.evaluate(t);
		rec.normal_to_point = n;
		rec.light_direction = (light.position - rec.point_hit).normalized();
		rec.diffuseCoefficient = diffuseCoefficient;
		rec.specularCoefficient = specularCoefficient;
		rec.ambientCoefficient = ambientCoefficient;
		rec.mirrorCoefficient = mirrorCoefficient;

		return true;

	}

	/*
	Vector3d diffuseShade(const LightSource& light, Record rec) const override
	{
		double redPixelColorDiffuse = +diffuseCoefficient * (light.intensity.x())* std::max(0.0, rec.normal_to_point.dot(rec.light_direction));
		double greenColorDiffuse = diffuseCoefficient * light.intensity.y() * std::max(0.0, rec.normal_to_point.dot(rec.light_direction));
		double bluePixelColorDiffuse = diffuseCoefficient * light.intensity.z() * std::max(0.0, rec.normal_to_point.dot(rec.light_direction));

		return Vector3d(redPixelColorDiffuse, greenColorDiffuse, bluePixelColorDiffuse);
	}
	*/


	void test_Plane()
	{
		std::cout << "point:  (" << p.x() << "," << p.y() << "," << p.z() << ")" << std::endl;
		std::cout << "normal:  (" << n.x() << "," << n.y() << "," << n.z() << ")" << std::endl;
	}


};
