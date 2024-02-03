#pragma once
#include <vector>
#include "Camera.h"
#include <iostream>

/*
A raytracer is a rendering algorithm that works by computing one pixerl at a time, the basic task is to
find theb object that is seen at that pixel's position in the image. Each pixel "looks" in a different direction, 
and any object that is see by the pixel mut insersect the viewing ray, a  line that emanates from the viewpoint in the direction 
that pixel is looking. A ray tracer has 3 three parts

1) Ray Generation: Computes the origin and direction of each pixel's viewing ray based on the camera geometry;
2) ray intersection, which finds the closest object intersecting the viewing ray;
3) shading, which computes the pixel color based on the result of ray intersection.

*/


class Raytracer
{
	int imageWidth;
	int imageHeight;
	std::vector<unsigned char> rasteredImage;

public:

	Raytracer(int width, int height)
	{
		imageWidth = width;
		imageHeight = height;
	}

	std::vector<unsigned char> rayTrace()
	{
		Vector3d cameraCenter(0, 0, 0); 
		Vector3d upVector(0, 1, 0);
		Vector3d viewDirection(0,0, 1);

		OrthographicCamera ortographicCamera(cameraCenter, viewDirection, upVector, imageWidth, imageHeight);
		ortographicCamera.test_show_frame();

		for (int i = 0; i < imageWidth; i++)
		{
			for (int j = 0; j < imageHeight; j++)
			{

				Vector3d rayOrigin = ortographicCamera.getOriginOfRay(i, j);
				std::cout << "(" << rayOrigin.x() << "," << rayOrigin.y() << "," << rayOrigin.z() << ") ";


				// Ray generation: Compute the origin and direction of each pixel's viewing ray based on the camera geometry;

				// Ortographic


			}

			std::cout << std::endl;
		}

		return rasteredImage;


	}





};