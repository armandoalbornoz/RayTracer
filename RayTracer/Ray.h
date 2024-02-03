#pragma once
#include <Eigen/Dense>
using Eigen::Vector3d;
/*


 A ray is nothing but a line in 3D. Remember a line in 3D is given by the following vector equation P(t) = p + td
 where "p" is a vector that represents a point in the line, and "d" is a vector giving the direction of the ray.
 */
class Ray
{
	Vector3d rayOrigin; // ray Origin
	Vector3d rayDirection; //

public:


	Ray(Vector3d o, Vector3d d)
	{
		rayOrigin = o;
		rayDirection = d;
	}

	Vector3d getOrigin() { return rayOrigin; }

	Vector3d getDirection() { return rayDirection; }


	/*
	Vector3d evaluate(double t)
	{
		return p + (t * d);
	}
	*/


	/*
	Ray generateOrthographicRay(Vector3d viewpoint, )
	{
	}

	*/



};