
#include <fstream>
#include <iostream>
#include <QOpenGLShaderProgram>
#include <sstream>
#include <vector>
#include "Point3D.h"
#include "Writer.h"

using namespace std;
Writer::Writer()
{
}
Writer ::~Writer()
{
}
void Writer::writerStl(Triangulation& triangulation)
{
    vector<Point3D>& points = triangulation.uniquePoints();
    vector<Triangle>& triangles = triangulation.triangles();

    static const int verticesPerTriangle = 3;
    static const int coordinatesPerVertex = 3;
    static const int totalVertices = verticesPerTriangle * triangles.size();
    static const int totalCoordinates = totalVertices * coordinatesPerVertex;

    GLfloat* vertices = new GLfloat[totalCoordinates];
    int currentIndex = 0;


    for (const Triangle& triangle : triangles)
    {
        //first vertices of Triangle
        vertices[currentIndex++] = points[triangle.v1()].x();
        vertices[currentIndex++] = points[triangle.v1()].y();
        vertices[currentIndex++] = points[triangle.v1()].z();

        //second Vertices of Triangle
        vertices[currentIndex++] = points[triangle.v2()].x();
        vertices[currentIndex++] = points[triangle.v2()].y();
        vertices[currentIndex++] = points[triangle.v2()].z();

        //Third vertices of Triangle
        vertices[currentIndex++] = points[triangle.v3()].x();
        vertices[currentIndex++] = points[triangle.v3()].y();
        vertices[currentIndex++] = points[triangle.v3()].z();


    }
    GLfloat* colors = new GLfloat[totalCoordinates];

    for (int i = 0; i < totalCoordinates; i += 3) {
        colors[i] = 1.0f;
        colors[i + 1] = 1.0f;
        colors[i + 2] = 1.0f;
    }
    
}