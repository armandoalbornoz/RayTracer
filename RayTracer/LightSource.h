#pragma once
#include <Eigen/Dense>
using Eigen::Vector3d;


class LightSource
{
public:

	Vector3d intensity; // Intensity value of the light RGB
	Vector3d position; // direction of light pointing towards the light source

	LightSource(Vector3d intensity, Vector3d lightDirection) : intensity(intensity), position(position) {}
};