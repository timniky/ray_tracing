#pragma once
 #ifndef Objects_h
  #define Objects_h
   #include "color.h"
    #include "vect.h"
     #include "ray.h"
      #include <cmath>
       #include <vector>
        #include <iostream>

class Sphere{	
public:
	Vec3 Center;
	double Radius;
	Color_t color;
	const double SELF_AVOID_T = 1e-2;
	Sphere(Vec3 center, double radius, Color_t color) : Center(center), Radius(radius),color(color){}

	Vec3 get_center() const {
		return Center;
	}

	Vec3 get_normal(const Vec3& p) const {
		return ((p - Center) * (-1 / Radius)).normalize();// *(-1 / Radius);
	}

	bool intersect(const Ray& ray, double& t) const {
		Vec3 v = ray.origin - Center;

		const double b = 2 * v.dot(ray.direction);
		const double c = v.dot(v) - Radius * Radius;
		double delta = b * b - 4 * c;

		if (delta < 0) {
			t = FLT_MAX;// no intersection, at 'infinity'
			return false;
		}

		const double t1 = (-b - sqrt(delta)) / 2;
		const double t2 = (-b + sqrt(delta)) / 2;

		if (t2 < SELF_AVOID_T) {
			t = FLT_MAX;
			return false;
		}

		t = (t1 >= SELF_AVOID_T) ? t1 : t2;

		return true;
	}
};
#endif
