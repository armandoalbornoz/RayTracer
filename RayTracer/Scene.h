#pragma once
#include<vector>
#include<memory>
#include "./Surface.h"

/*  The more intereseting scenes to display are the ones that consists of more than one object. A simple way
	to implement these kind of scenes is to think of the entire scene as a surface itself that can be hit. 
	To intersect a ray with a group, you simply intersect the ray with the objects in the group and return the 
	intersection with the smallest t value.
*/

class Scene : Surface
{
public:

	std::vector<std::shared_ptr<Surface>> surfaces;

	Scene(std::shared_ptr<Surface> surface) 
	{ 
		add(surface);
		
	}

	void add(std::shared_ptr<Surface> surface)
	{
		surfaces.push_back(surface);
	}

	/*
	This function checks the intersections of the ray and all the surfaces and saves the smallest intersection point
	in our record.
	*/
	bool hit(const Ray& ray, double t_min, double t_max,  Record& rec, const LightSource& light)  const override
	{
		Record current_surface_record;
		bool hit = false;
		auto t = t_max;

		for (const auto& surface : surfaces) {
			if (surface->hit(ray, t_min, t, current_surface_record, light)) {

				hit = true;
				t = current_surface_record.t;
				rec = current_surface_record;
			}
		}

		return hit;
	}
	
};