#include "objects.hpp"
#include <cmath>
#include <iostream>

Sphere::Sphere(point cent, double r, point col, quartet cfs, double sh){

    center = cent;
    radius = r;
    color = col;
    coeffs = cfs;
    shininess = sh;
}

void Sphere::draw(point eyePos){
    int stacks = 100;
    int slices = 100;


    struct point points[stacks+1][slices+1];
    for (int j = 0; j <= stacks; j++) {
        double phi = -M_PI / 2.0 + j * M_PI / stacks;
        double r = radius * cos(phi);
        double h = radius * sin(phi);
        for (int i = 0; i < slices+1; i++) {
            double theta = i * 2.0 * M_PI / slices;
            points[j][i].x = r * cos(theta);
            points[j][i].y = r * sin(theta);
            points[j][i].z = h;
        }
    }
    glPushMatrix();
        glTranslatef(center.x, center.y, center.z);
        glBegin(GL_QUADS);
            for (int j = 0; j < stacks; j++) {
                for (int i = 0; i < slices; i++) {
                    // GLfloat c = (2+cos((i+j) * 2.0 * M_PI / slices)) / 3;
                    glColor3f(color.x, color.y, color.z);
                    glVertex3f(points[j][i].x, points[j][i].y, points[j][i].z);
                    glVertex3f(points[j][i+1].x, points[j][i+1].y, points[j][i+1].z);

                    glVertex3f(points[j+1][i+1].x, points[j+1][i+1].y, points[j+1][i+1].z);
                    glVertex3f(points[j+1][i].x, points[j+1][i].y, points[j+1][i].z);
                }
            }
        glEnd();
    glPopMatrix();

}

Sphere* Sphere::parseSphere(std::ifstream &f){
    point cen = point::parsePoint(f);
    double r;
    f >> r;
    point col = point::parsePoint(f);
    quartet cfs = quartet::parseQuartet(f);
    double sh;
    f >> sh;

    return new Sphere(cen, r, col, cfs, sh);


}

quartet quartet::parseQuartet(std::ifstream &f){
    quartet x;
    f >> x.x >> x.y >> x.z >> x.w;
    return x;
}

Pyramid* Pyramid::parsePyramid(std::ifstream &f){
    point lp = point::parsePoint(f);
    double w,h;
    f >> w >> h;
    point col = point::parsePoint(f);
    quartet q = quartet::parseQuartet(f);
    double sh;
    f >> sh;
    return new Pyramid(lp, w, h, col, q, sh);
}

Pyramid::Pyramid(point lp, double w_, double h_, point col, quartet cf, double sh){
    lowestPoint = lp;
    w = w_;
    h = h_;
    color = col;
    coeffs = cf;
    shininess = sh;
}

void Pyramid::draw(point eyePos){
    double d2r = (M_PI / 180.);
    double baseCenterToCorner = w / sqrt(2);
    point cornerPoints[4];
    for(int i = 0; i < 4; ++i){
        cornerPoints[i] = lowestPoint;
        cornerPoints[i].x += baseCenterToCorner * cos((135 - i * 90) * d2r);
        cornerPoints[i].z += baseCenterToCorner * sin((135 - i * 90) * d2r);
    }
    point topPoint = lowestPoint;
    topPoint.y += h;

    // std::cout <<  "height: " << h << "\n";
    // std ::cout << topPoint.x << " " << topPoint.y << " " << topPoint.z << "\n";
    glBegin(GL_QUADS);
        glColor3f(color.x, color.y, color.z);
        for(int i = 0; i < 4; ++i){
            glVertex3f(cornerPoints[i].x, cornerPoints[i].y, cornerPoints[i].z);
        }
    glEnd();

    glBegin(GL_TRIANGLES);
        for(int i = 0; i < 3; ++i){
            glVertex3f(cornerPoints[i].x, cornerPoints[i].y, cornerPoints[i].z);
            int j = (i + 1) % 4;
            glVertex3f(cornerPoints[j].x, cornerPoints[j].y, cornerPoints[j].z);
            glVertex3f(topPoint.x, topPoint.y,topPoint.z);

        }
    glEnd();
}

Cube* Cube::parseCube(std::ifstream &f){
    point bc = point::parsePoint(f);
    double side;
    f >> side;
    point col = point::parsePoint(f);
    quartet coeff = quartet::parseQuartet(f);
    double sh;
    f >> sh;
    return new Cube(bc, side, col, coeff, sh);
}

Cube::Cube(point lp, double side, point col, quartet cf, double sh){
    bottomLeft = lp;
    this->side = side;
    color = col;
    coeffs = cf;
    shininess = sh;
}

void Cube::draw(point eyePos){
    glBegin(GL_QUADS);
        for(int i = 0; i < 4; ++i){
            int yOffset = (i > 1) ? side : 0;
            int zOffset = (i == 1 || i == 2) ? side : 0;
            glVertex3f(bottomLeft.x, bottomLeft.y + yOffset, bottomLeft.z + zOffset);
        }
        for(int i = 0; i < 4; ++i){
            int yOffset = (i > 1) ? side : 0;
            int zOffset = (i == 1 || i == 2) ? side : 0;
            glVertex3f(bottomLeft.x + side, bottomLeft.y + yOffset, bottomLeft.z + zOffset);
        }
        for(int i = 0; i < 4; ++i){
            int xOffset = (i > 1) ? side : 0;
            int zOffset = (i == 1 || i == 2) ? side : 0;
            glVertex3f(bottomLeft.x + xOffset, bottomLeft.y, bottomLeft.z + zOffset);
        }
        
        for(int i = 0; i < 4; ++i){
            int xOffset = (i > 1) ? side : 0;
            int zOffset = (i == 1 || i == 2) ? side : 0;
            glVertex3f(bottomLeft.x + xOffset, bottomLeft.y + side, bottomLeft.z + zOffset);
        }

        for(int i = 0; i < 4; ++i){
            int xOffset = (i > 1) ? side : 0;
            int yOffset = (i == 1 || i == 2) ? side : 0;
            glVertex3f(bottomLeft.x + xOffset, bottomLeft.y + yOffset, bottomLeft.z + side);
        }

        for(int i = 0; i < 4; ++i){
            int xOffset = (i > 1) ? side : 0;
            int yOffset = (i == 1 || i == 2) ? side : 0;
            glVertex3f(bottomLeft.x + xOffset, bottomLeft.y + yOffset, bottomLeft.z);
        }
        
        
    glEnd();
}

CheckerBoard::CheckerBoard(double a, point cf){
    w = a;
    coeff = cf;
}

CheckerBoard* CheckerBoard::parseCheckerBoard(std::ifstream &f){
    double a;
    f >> a;
    point coeff = point::parsePoint(f);
    return new CheckerBoard(a, coeff);
}

void CheckerBoard::draw(point eyePos){
    int c = 0;
    glPushMatrix();
        // glTranslatef(eyePos.x, 0, eyePos.z);
        glTranslatef(0, 0, -500);
        glBegin(GL_QUADS);
        for(int i = -10; i < 20; ++i){
            for(int j = 1; j < 50; ++j){
                if(c){
                    glColor3f(0, 0, 0);
                }
                else{
                    glColor3f(1, 1, 1);
                }
                c = 1 - c;
                glVertex3f((i-1) * w, 0 , (j-1) * w);
                glVertex3f((i) * w, 0 , (j-1) * w);
                glVertex3f((i) * w, 0 , (j) * w);
                glVertex3f((i-1) * w, 0 , (j) * w);
            }
        }
        
        glEnd();
    glPopMatrix();
}