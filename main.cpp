#include "openglwindow.h"
#include <iostream>
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>
#include "Triangulation.h"
#include "Point3D.h"
#include "Reader.h"
#include "Writer.h"

//! [1]
class TriangleWindow : public OpenGLWindow
{
public:
    using OpenGLWindow::OpenGLWindow;

    void initialize() override;
    void render() override;

private:
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    QOpenGLShaderProgram* m_program = nullptr;
    int m_frame = 0;
};
//! [1]

//! [2]
int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}
//! [2]


//! [3]
static const char* vertexShaderSource =
"attribute highp vec4 posAttr;\n"
"attribute lowp vec4 colAttr;\n"
"varying lowp vec4 col;\n"
"uniform highp mat4 matrix;\n"
"void main() {\n"
"   col = colAttr;\n"
"   gl_Position = matrix * posAttr;\n"
"}\n";

static const char* fragmentShaderSource =
"varying lowp vec4 col;\n"
"void main() {\n"
"   gl_FragColor = col;\n"
"}\n";

//! [3]

//! [4]
void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = m_program->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
    glEnable(GL_DEPTH_TEST);
}
//! [4]

//! [5]
void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -50);
    matrix.scale(0.2);
   
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 1, 0, 0);

    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 0, 1);



    m_program->setUniformValue(m_matrixUniform, matrix);


    Triangulation triangulation;
    Reader r;
    r.readFile(triangulation);

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
    //    first vertices of Triangle
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
    /*static const GLfloat colors[] = {
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f
    };*/

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_TRIANGLES, 0, totalCoordinates / 3); // Changed to draw a cube

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    ++m_frame;



    //for (const Triangle& triangle : triangles)
    //{
    //    // Iterate over each vertex of the triangle
    //    for (int i = 0; i < verticesPerTriangle; ++i)
    //    {
    //        // Get the index of the current vertex of the triangle
    //        int vertexIndex;
    //        if (i == 0)
    //            vertexIndex = triangle.v1();
    //        else if (i == 1)
    //            vertexIndex = triangle.v2();
    //        else
    //            vertexIndex = triangle.v3();

    //        // Append coordinates of the vertex to vertices array
    //        vertices[currentIndex++] = points[vertexIndex].x();
    //        vertices[currentIndex++] = points[vertexIndex].y();
    //        vertices[currentIndex++] = points[vertexIndex].z();
    //    }
    //}
}
//! [5]
