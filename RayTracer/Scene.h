#pragma once
#include<vector>
#include<memory>
#include "./Surface.h"
#include "./Ray.h"

/*  The more intereseting scenes to display are the ones that consists of more than one object. A simple way
	to implement these kind of scenes is to think of the entire scene as a surface itself that can be hit. 
	To intersect a ray with a group, you simply intersect the ray with the objects in the group and return the 
	intersection with the smallest t value.
*/

class Scene 
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

	
	void idealSpecular(Ray& ray, double t_min, Record& rec, Record& current_surface_record, LightSource& light, int& counter, bool hit)
	{
		
		if (counter > 1)
		{
			return;
		}
		else
		{
			if (hit && rec.mirrorCoefficient.norm() > 0)
			{

				Vector3d d = rec.point_hit - ray.getOrigin();
				Vector3d r = d - (2 * (d.dot(rec.normal_to_point)) * rec.normal_to_point);
				Ray newRay(rec.point_hit, r);

				for (auto surface : surfaces) {
					if (surface->hit(newRay, t_min + 0.0000001, 100000, current_surface_record, light))
					{
						rec.diffuseCoefficient =  current_surface_record.diffuseCoefficient;
						rec.specularCoefficient =   current_surface_record.specularCoefficient;
						rec.ambientCoefficient = current_surface_record.ambientCoefficient;
					}
				}
				counter++;
				idealSpecular(newRay, t_min, rec, current_surface_record, light, counter, hit);

			}




		}
		

	
	}

	/*
	This function checks the intersections of the ray and all the surfaces and saves the smallest intersection point
	in our record.
	*/
	bool hit(Ray& ray, double t_min, double t_max,  Record& rec, LightSource& light) 
	{
		Record current_surface_record;
		Record shadow_record;
		bool hit = false;
		auto t = t_max;

		for (auto surface : surfaces) {
			if (surface->hit(ray, t_min, t, current_surface_record, light)) {
				// A ray from the viewpoint has hit the closest object
				hit = true;
				t = current_surface_record.t;
				rec = current_surface_record;
			}
		}
		// check if we hit, if we do, see if the ray from from point of intersection to the light source hits something,
		// If it does we have a shadow
		if (hit)
		{
			for (auto surface : surfaces) {
		
				Ray newRay(rec.point_hit, light.position - rec.point_hit);

				if (surface->hit(newRay, t_min + 0.0000001, 100000, shadow_record, light))
				{
					rec.shadowed = true;
					break;
				}
			}
		}

		// check if we hit and if the image has mirror reflection, if we do, see if the ray from the point of intersection to the mirror direction hits something,
		// If it does check the mirror image

		//int counter = 1;
		//idealSpecular(ray, t_min, rec, current_surface_record, light, counter, hit);

		


		return hit;
	}
};