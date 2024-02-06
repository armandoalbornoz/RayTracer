#pragma once
#include "ray.h"
#include "./Material.h"
#include "./LightSource.h"
/* Surface is an abstract class for Objects that can be hit by rays, and surface_hit_record is a class to store information about
   the hit
*/


struct Record {
     Vector3d point_hit; 
     Vector3d normal_to_point; 
     double t; 
     Vector3d light_direction; 
     Vector3d diffuseCoefficient;
     Vector3d specularCoefficient;
     Vector3d ambientCoefficient;
     Vector3d angleBisector;
};


class Surface
{
protected:
    Vector3d diffuseCoefficient;
    Vector3d specularCoefficient;
    Vector3d ambientCoefficient;

    Surface(Vector3d diffuseCoefficient, Vector3d specularCoefficient, Vector3d ambientCoefficient) :
        diffuseCoefficient(diffuseCoefficient), specularCoefficient(specularCoefficient), ambientCoefficient(ambientCoefficient)  {}
public:

    virtual ~Surface() = default;

    virtual bool hit(const Ray& r, double t_min, double t_max, Record& surf_rec, const LightSource& light) const = 0;

  //  virtual Vector3d diffuseShade(const LightSource& light, Record rec) const = 0;

};