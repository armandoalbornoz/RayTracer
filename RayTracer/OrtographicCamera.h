#pragma once
#include "./Ray.h"
#include <iostream>
#include <vector>

/*
 All the rays are generated from the camera which is nothing but a orthonormal coordinate frame, also know as the camera frame.
We'll denote by e the viewpoint, u,v, and w, for the three basis vectors, organized with u pointing rightward,
v pointing upward, and w pointing backward, so that {u,v,w} forms a right-handed coordinate system.

The most common way to construct the camera frame is from the viewpoint, which becomes e, the view direction, which is -w, and the 
up vector, which is used to construct a basis that has v and w in the plane defined by the view direction

*/

/*
For an Ortographic camera, all the rays will have direction viewDirectionV. Even though a parallel view does not have a viewpoint per se,
we can still use the origin of the camera frame to define the plane where the rays start, so it is possible for objects to be behind the camera.

The viewing rays should start on the plane defined by the point e and the vectors rightV and upV; the only remaining information required is where on 
the plane the image is supposed to be. We'll define the image dimensions with four numbers, for the four sides of the image: l and r are the positions of the left 
and right edge of the image measureed from e along the upV direction, and b and t are the positions of the bottom  and top edges of the image. Usually, l < 0 < r and b < 0 < t.
*/
class OrthographicCamera 
{
	int imageWidth;
	int imageHeight;

	Vector3d e; // viewpoint, where we want our camera to be in space (the center of the camera)
	Vector3d viewDirection; // viewdirection, this is a vector aligned in the direction of the camera
	Vector3d u; // right vector
	Vector3d v; // up vector


	double r;
	double l;
	double t;
	double b;


public:


	// Create camera frame using the view direction vector and the up vector. Notice that this procedure does not work if both vector are colinear. 
	OrthographicCamera(const Vector3d& e_, const Vector3d& viewDirection_,  const Vector3d& upV_, int imageWidth_, int imageHeight_)
	{
		imageWidth = imageWidth_;
		imageHeight = imageHeight_;
		e = e_;
		viewDirection = viewDirection_;
		v = upV_;
		r = (imageWidth_ / 2);
		l = -(imageWidth_ / 2);
		t = (imageHeight_ / 2);
		b = -(imageHeight_ / 2);
	
		if(viewDirection.cross(v) == Vector3d(0,0,0)) // If v and -w are collinear
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

	// Receive the position (i,j) of a pixel and returns the the coordinates of the pixel's position on the image plane measured with respect to the
	// origin e and the basis {v,u}
	Vector3d getOriginOfRay(int i, int j) const
	{
		// calculate coordinates of pixel at position (i,j)  measured with respect to the origin e and the basis {v,u}

		double ucoord = l + ((r - l) * (i + 0.5) / imageWidth);
		double vcoord =  b + ((t - b) * (j + 0.5) / imageHeight);

		/*
		In an orthographic view, we can simply use the pixel’s image-plane position
		as the ray’s starting point, thus
		*/

		return (e + (ucoord * u) + (vcoord * v));
	}

	Vector3d getDirection() const { return viewDirection;}


	void test_show_frame()
	{
		std::cout << "viewdirection:  ("  << viewDirection.x() << "," << viewDirection.y() << "," << viewDirection.z() << ")" << std::endl;
		std::cout << "right: (" << u.x() << "," << u.y() << "," << u.z() << ")" << std::endl;
		std::cout << "up: ("  << v.x() << "," << v.y() << "," << v.z() << ")" << std::endl;

	}
};
