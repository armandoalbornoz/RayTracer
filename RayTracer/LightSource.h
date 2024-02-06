#pragma once
#include <Eigen/Dense>

using Eigen::Vector3d;


class LightSource
{
public:

	Vector3d intensity; // Intensity value of the light RGB
	Vector3d position; // direction of light pointing towards the light source
	Vector3d ambientLightIntensity;


	LightSource(Vector3d intensity, Vector3d position, Vector3d ambientLightIntensity) : 
		intensity(intensity), position(position), ambientLightIntensity(ambientLightIntensity)  {}
};