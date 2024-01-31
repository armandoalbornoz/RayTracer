#pragma once
#include "./Ray.h"
#include <iostream>
/*
 All the rays are generated from the camera which is nothing but a orthonormal coordinate frame, also know as the camera frame.
We'll denote by e the viewpoint, u,v, and w, for the three basis vectors, organized with u pointing rightward,
v pointing upward, and w pointing backward, so that {u,v,w} forms a right-handed coordinate system.

The most common way to construct the camera frame is from the viewpoint, which becomes e, the view direction, which is -w, and the 
up vector, which is used to construct a basis that has v and w in the plane defined by the view direction

*/
class OrthographicCamera 
{
	Vector3d e; // viewpoint, where we want our camera to be in space (the center of the camera)
	Vector3d viewDirectionV; // viewdirection, this is a vector aligned in the direction of the camera
	Vector3d rightV; // right vector
	Vector3d upV; // up vector


	// Create camera frame using the view direction vector and the up vector. Notice that this procedure does not work if both vector are colinear. 
	OrthographicCamera(Vector3d viewDirectionV_, Vector3d upV_)
	{
		viewDirectionV = viewDirectionV_;
		upV = upV_;

		if(viewDirectionV.cross(upV) == Vector3d(0,0,0))
		{
			std::cout << "Vectors are collinear." << std::endl;
		}
		else
		{
			viewDirectionV = viewDirectionV / viewDirectionV.norm();

			rightV = upV.cross(viewDirectionV);

			upV = viewDirectionV.cross(rightV);
		}

	
	}


	Vector3d up_vector; // orientation of the camera



};
