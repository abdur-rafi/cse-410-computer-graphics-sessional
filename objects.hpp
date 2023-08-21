#ifndef H_OBJECTS
#define H_OBJECTS

#include "utility.hpp"
#include <fstream>
#include <vector>

class Object{

public:

    virtual void draw(point eyePos) = 0;

    virtual double intersection(const Line &line) = 0;
};

class Sphere : public Object{
    point center, color;
    double radius;
    quartet coeffs;
    double shininess;
public : 

    Sphere(point cent, double r, point col, quartet cfs,double shininess);

    void draw(point eyePos);

    static Sphere* parseSphere(std::ifstream &f);
    double intersection(const Line &line);
};

class Pyramid : public Object{
    point lowestPoint;
    double w, h;
    point color;
    quartet coeffs;
    double shininess;
    std::vector<Surface*> surfaces;

public:
    Pyramid(point lp, double w_, double h_, point col, quartet cf, double sh);

    static Pyramid* parsePyramid(std::ifstream &f);

    void draw(point eyePos);
    double intersection(const Line &line);
};


class Cube : public Object{
    point bottomLeft;
    double side;
    point color;
    quartet coeffs;
    double shininess;
    std::vector<Surface*> surfaces;

public:
    Cube(point lp, double side, point col, quartet cf, double sh);

    static Cube* parseCube(std::ifstream &f);

    void draw(point eyePos);
    double intersection(const Line &line);

};

class CheckerBoard : public Object{
    double w;
    point coeff;

public:
    CheckerBoard(double w_, point cf);

    void draw(point eyePos);
    
    static CheckerBoard* parseCheckerBoard(std::ifstream &f);
    double intersection(const Line &line);
};


#endif 