#pragma once
#include <vector>
#include <Eigen/Dense>
#include "Surface.h"
#include "Ray.h"
#include <iostream>
#include "./Plane.h"



class Triangle : public Surface
{
	Vector3d vertexa; 
	Vector3d vertexb; 
	Vector3d vertexc; 
	Plane containerPlane; // plane containing triangle

public:


	Triangle(const Vector3d& vertexa, const Vector3d& vertexb, const Vector3d& vertexc, Vector3d diffuseCoefficient, Vector3d specularCoefficient, Vector3d ambientCoefficient, Vector3d mirrorCoefficient) :
		vertexa(vertexa), vertexb(vertexb), vertexc(vertexc), Surface(diffuseCoefficient, specularCoefficient, ambientCoefficient, mirrorCoefficient)
	{
		containerPlane.p = vertexa;
		containerPlane.n = ((vertexb - vertexa).cross(vertexc - vertexa)).normalized();
	}

	bool hit(const Ray& ray, double t_min, double t_max, Record& rec, const LightSource& light)  const override
	{

		// Check if ray hits plane

		if (containerPlane.hit(ray,t_min, t_max, rec, light))
		{
			// Ray hits point, now check if it's inside the three edges of the triangle

			double num1 = ((vertexb - vertexa).cross(rec.point_hit - vertexa)).dot(rec.normal_to_point);
			double num2 = ((vertexc - vertexb).cross(rec.point_hit - vertexb)).dot(rec.normal_to_point);
			double num3 = ((vertexa - vertexc).cross(rec.point_hit - vertexc)).dot(rec.normal_to_point);
			if (num1 > 0 && num2 > 0 && num3 > 0)
			{
				rec.diffuseCoefficient = diffuseCoefficient;
				rec.ambientCoefficient = ambientCoefficient;
				rec.specularCoefficient = specularCoefficient;
				rec.mirrorCoefficient = mirrorCoefficient;
				return true;
			}
		}

		return false;


	}
};
