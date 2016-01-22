#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <png++/png.hpp>

#include "Intro.hpp"
#include "Raytracer.hpp"
#include "core/Point.hpp"
#include "core/Vector.hpp"
#include "scene/Loader.hpp"
#include "scene/Scene.hpp"
#include "shape/Sphere.hpp"


void guiInterface(int argc, char** argv);
void textInterface();

int main(int argc, char** argv)
{
    std::cout << "Params given: " << argc << std::endl <<"To executable: "<< argv[0] << std::endl;
    printIntro();
    if (argc > 1)
    {
        std::cout << "Starting graphical interface..." << std::endl;
        guiInterface(argc, argv);
    }
    else
    {
        std::cout << "Starting text interface..." << std::endl;
        textInterface();
    }
    return 0;
}

void guiInterface(int argc, char** argv)
{
    std::cout << "NOT IMPLEMENTED YET!. USE TEXT INTERFACE." << std::endl;
}

void textInterface()
{
    try
    {
        rt::scene::Loader loader;
        rt::scene::Scene s = loader.load("../scene.json");
        rt::Raytracer raytracer;
        raytracer.load(s);
        raytracer.run();
        rt::Raytracer::ImgType image;
        image = raytracer.getImage();

        png::image<png::rgb_pixel> pngImage(512, 512);
        for (size_t y = 0; y < pngImage.get_height(); ++y)
        {
            for (size_t x = 0; x < pngImage.get_width(); ++x)
            {
                
                if(image[x][y] > 10000)
                {
                    pngImage[y][x] = png::rgb_pixel(100, 100, 100); 
                }

                else if(image[x][y] > 20)
                {
                    pngImage[y][x] = png::rgb_pixel(255, 0, 0); 
                }
                else if (image[x][y] > 15)
                {
                    pngImage[y][x] = png::rgb_pixel(0, 255, 0); 
                }
                else if (image[x][y] > 10)
                {
                    pngImage[y][x] = png::rgb_pixel(0, 0, 255); 
                }
                else if (image[x][y] > 5)
                {
                    pngImage[y][x] = png::rgb_pixel(0, 255, 255); 
                }
                else
                {
                    double d = image[x][y] * 79;
                    char depth = std::min(char(d), char(255));
                    pngImage[y][x] = png::rgb_pixel(depth, depth, depth);
                }
                if (image[x][y] < 0)
                {
                    pngImage[y][x] = png::rgb_pixel(100, 100, 0); 
                }

                if ((x == 256-80) && (y == 256))
                {
                    std::cout << "Probing:" << (unsigned int)(image[x][y]) << std::endl;
                }
            }
        }
        
        pngImage.write("../render.png");

    }
    catch(std::string str)
    {
        std::cout << "Exception was thrown: " << str << std::endl;
    }
}
