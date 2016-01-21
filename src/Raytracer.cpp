#include "Raytracer.hpp"

#include <cmath>

#include <iostream>

namespace rt
{

Raytracer::ImgType Raytracer::getImage()
{
	return buffer_;
}

void Raytracer::load(scene::Scene& s)
{
	scene_ = s;
}

void Raytracer::run()
{
	for(int height=-IMG_SIDE/2; height < IMG_SIDE/2; height++)
	{
		for(int width =- IMG_SIDE/2; width<IMG_SIDE/2; width++)
		{
	    	core::Point orgin(width, height, -10.0);
	    	core::Vector direction(0.0,0.0,1.0);

	    	core::Ray viewRay(orgin, direction);

	    	double distance = trace(viewRay, 1);
	    	buffer_[width+IMG_SIDE/2][height+IMG_SIDE/2] = distance;
		}
	}
	std::cout << "Hit: " << hitCounter_ << std::endl;
	std::cout << "NoHit: " << noHitCounter_ << std::endl;
}

double Raytracer::trace(core::Ray& ray, int recursiveStep)
{
	double distance = 1000000.0f;

	auto objects = scene_.getObjects();

	for(auto& object : objects)
	{

		if(object->hit(ray, distance))
		{
			hitCounter_++;
		}
		else
		{
			noHitCounter_++;	
		}
		//std::cout << ray.getOrgin() << std::endl;
		//std::cout << distance << std::endl;
	};

	if (distance < 1) 
	{
		distance = 1000000.0f;
	}

	return distance;
}



}  // namespace rt