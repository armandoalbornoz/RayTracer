#pragma once
#include "ray.h"
/* Surface is an abstract class for Objects that can be hit by rays, and surface_hit_record is a class to store information about
   the hit
*/


struct Record {
    Vector3d point_hit;
    Vector3d normal_to_point;
    double t;
};

class Surface
{
public:

    int color;

    virtual ~Surface() = default;

    virtual bool hit(const Ray& r, double t_min, double t_max, Record& surf_rec) const = 0;
};