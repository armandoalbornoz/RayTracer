#pragma once
#include "./Ray.h"
#include <iostream>
#include <vector>

/*
For a perspective view, all the rays have the same origin, at the viewpoint; it
is the directions that are different for each pixel. The image plane is no longer
positioned at e, but rather some distance d in front of e; this distance is the image
plane distance, often loosely called the focal length, because choosing d plays the
same role as choosing focal length in a real camera. The direction of each ray is
defined by the viewpoint and the position of the pixel on the image plane.
*/
class PerspectiveCamera
{

	int imageWidth;
	int imageHeight;
	double d; // d is the distance between e and the image plane

	Vector3d e; // viewpoint, where we want our camera to be in space (the center of the camera)
	Vector3d viewDirection; // viewdirection, this is a vector aligned in the direction of the camera
	Vector3d u; // right vector
	Vector3d v; // up vector
	

	double r;
	double l;
	double t;
	double b;

public: 

	PerspectiveCamera(const Vector3d& e_, const Vector3d& viewDirection_, const Vector3d& upV_, int imageWidth_, int imageHeight_, double d_)
	{
		imageWidth = imageWidth_;
		imageHeight = imageHeight_;
		e = e_;
		viewDirection = viewDirection_;
		v = upV_;
		d = d_;
		r = (imageWidth_ / 2);
		l = -(imageWidth_ / 2);
		t = (imageHeight_ / 2);
		b = -(imageHeight_ / 2);

		if (viewDirection.cross(v) == Vector3d(0, 0, 0)) // If v and -w are collinear
		{
			std::cout << "Vectors are collinear." << std::endl;
		}
		else // Compute camera frame

		{

			viewDirection = viewDirection / viewDirection.norm();

			u = viewDirection.cross(v);

			u = u / u.norm();

			v = u.cross(viewDirection);

			v = v / v.norm();
		}
	}

	Vector3d getDirectionOfRay(int i, int j) const
	{
		// calculate coordinates of pixel at position (i,j)  measured with respect to the origin e and the basis {v,u}
		double ucoord = l + ((r - l) * (i + 0.5) / imageWidth);
		double vcoord = b + ((t - b) * (j + 0.5) / imageHeight);
		// return the direction
		return ((d * viewDirection) + (ucoord * u) + (vcoord * v));
	}


	Vector3d getOrigin() const {return e;}

};