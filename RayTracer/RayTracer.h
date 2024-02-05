#pragma once
#include <vector>
#include <iostream>
#include "./OrtographicCamera.h"
#include "./Surface.h"
#include "./PerspectiveCamera.h"
#include "Plane.h"
#include "Sphere.h"
#include <memory>
#include "./Scene.h"

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

	Raytracer(int imageWidth, int imageHeight) : imageWidth(imageWidth), imageHeight(imageHeight), image(3 * imageWidth * imageHeight)
	{
		std::cout << "Image Width: " << imageWidth << " image Height: " << imageHeight << " image size: " << image.size() << std::endl;
	}

	std::vector<unsigned char> render(const Scene& scene, const OrthographicCamera& ortographicCamera, const PerspectiveCamera& perspectiveCamera, LightSource light)
	{

		std::vector<unsigned char> image(3 * imageWidth * imageHeight);

		for (int i = 0; i < imageHeight; i++)
		{
			for (int j = 0; j < imageWidth; j++)
			{

				//Vector3d rayOrigin = ortographicCamera.getOriginOfRay(i, j);
				Vector3d rayDirection = perspectiveCamera.getDirectionOfRay(i, j);

				//std::cout << "(" << rayOrigin.x() << "," << rayOrigin.y() << "," << rayOrigin.z() << ") ";

				//Ray ray(rayOrigin, ortographicCamera.getDirection);
				Ray ray(perspectiveCamera.getOrigin(), rayDirection);

				Record rec;

				if (scene.hit(ray, 0, 1000, rec, light))
				{
					double redPixelColorDiffuse = 0.8 * light.intensity.x() * std::max(0.0,rec.normal_to_point.dot(rec.light_direction));
					double greenColorDiffuse = 0.8 * light.intensity.y() * std::max(0.0, rec.normal_to_point.dot(rec.light_direction));
					double bluePixelColorDiffuse = 0.8 * light.intensity.z() * std::max(0.0, rec.normal_to_point.dot(rec.light_direction));

					int idx = (i * imageWidth + j) * 3;
					image[idx] = (unsigned char)(255* ( (redPixelColorDiffuse)));
					image[idx + 1] = (unsigned char)(255 * ( (greenColorDiffuse)));
					image[idx + 2] = (unsigned char)(255 * ( (bluePixelColorDiffuse)));
				}

			}

			//std::cout << std::endl;
		}
		return image;
	}
};