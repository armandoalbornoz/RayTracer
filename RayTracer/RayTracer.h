#pragma once
#include <vector>

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
	int width;
	int height;
	//std::vector<int> image;

	Raytracer(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	std::vector<unsigned char> RayTrace()
	{
		for (int i = 0; i < width; i++) 
		{
			for (int j = 0; j < height; j++)
			{
				// Ray generation
			}
		}

	}





};