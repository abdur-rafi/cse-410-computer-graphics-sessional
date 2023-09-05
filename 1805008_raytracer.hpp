#ifndef H_RAYTRACER
#define H_RAYTRACER

#include <fstream>
#include "1805008_config.hpp"
#include "1805008_utility.hpp"
#include "1805008_objects.hpp"
#include "1805008_lightSource.hpp"
#include <vector>


class RayTracer{
    
    Config config;
    point* eyePos;
    point ***pointBuffer;

public:
    CheckerBoard* board;
    std::vector<Object*> objects;
    std::vector<LightSource*> lights;

    Config getConfig();

    RayTracer(std::ifstream &f);

    void draw(point eyePos);

    ~RayTracer();

    void generatePointBuffer(const CameraConfig &cConfig);

    IntersectionReturnVal intersection(const Line& line);


    void generateImage(const CameraConfig &cConfig);

    point calcColor(const IntersectionReturnVal& val, const Line&, const point&);

    point colorRecursive(const Line& line, int level);
};

#endif