#pragma once
#include <Eigen/Dense>
using Eigen::Vector3d;
/*


 A ray is nothing but a line in 3D. Remember a line in 3D is given by the following vector equation P(t) = p + td
 where "p" is a vector that represents a point in the line, and "d" is a vector giving the direction of the ray.
 */
class Ray
{
	Vector3d rayOrigin; 
	Vector3d rayDirection; 

public:

	Ray() {}

	Ray(const Vector3d& o, const Vector3d& d)
	{
		rayOrigin = o;
		rayDirection = d;
	}

	 Vector3d getOrigin() const  { return rayOrigin; }
	 Vector3d getDirection() const { return rayDirection; }

	 void setOrigin(Vector3d origin) { rayOrigin = origin; }
	 void setDirection(Vector3d direction) { rayDirection = direction; }

	 Vector3d evaluate(double t) const { return rayOrigin + t * rayDirection;  }


};