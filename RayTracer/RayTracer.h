#pragma once
#include <vector>
#include <iostream>
#include "./OrtographicCamera.h"
#include "Sphere.h"

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
	std::vector<unsigned char> image;

public:

	Raytracer(int imageWidth, int imageHeight) : 
		imageWidth(imageWidth), 
		imageHeight(imageHeight),
		image(3 * imageWidth * imageHeight)
	{
		std::cout << "Image Width: " << imageWidth << " image Height: " << imageHeight << " image size: " << image.size() << std::endl;
	}

	std::vector<unsigned char> rayTrace()
	{

		std::vector<unsigned char> image(3 * imageWidth * imageHeight);
		Vector3d cameraCenter(3, 0, 0); 
		Vector3d upVector(1, 0, 0);
		Vector3d viewDirection(0,0, 1);
		OrthographicCamera ortographicCamera(cameraCenter, viewDirection, upVector, imageWidth, imageHeight);
		ortographicCamera.test_show_frame();

		Vector3d sphereCenter(0, 0, 32);
		Sphere sphere(sphereCenter, 16);

		/*
		Ray ray = Ray(cameraCenter, viewDirection);


		sphere.hitSphere(ray);

		std::cout << sphere.hitSphere(ray)[0] << " " << sphere.hitSphere(ray)[1] <<  std::endl;
		*/


		for (int i = 0; i < imageWidth; i++)
		{
			for (int j = 0; j < imageHeight; j++)
			{

				// Ray generation: Compute the origin and direction of each pixel's viewing ray based on the camera geometry;

				Vector3d rayOrigin = ortographicCamera.getOriginOfRay(i, j);
				//std::cout << "(" << rayOrigin.x() << "," << rayOrigin.y() << "," << rayOrigin.z() << ") ";

				Ray ray(rayOrigin, viewDirection);

				// Ray intersection: Find the closest object intersecting the viewing ray;

				// If the ray hits the sphere shade (i,j)

					if (sphere.hitSphere(ray).size() > 0)
					{
						int idx = (i * imageWidth + j) * 3;
						image[idx] = (unsigned char)(255);
						image[idx + 1] = 0;
						image[idx + 2] = 0;
					}


			}

			//std::cout << std::endl;
		}

		return image;


	}





};