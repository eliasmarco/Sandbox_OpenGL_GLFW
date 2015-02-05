#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glm.hpp>
#include "defines.h"
#include "ResourceManager.h"
#include "lodepng/lodepng.h"
#include "ModelData.h"

using namespace std;

class GenericPainter {
public:
    GenericPainter();
    ~GenericPainter();

    void vInit(unsigned int uWinWidth, unsigned int uWinHeight);
    void vDraw();

private:
    void vSetupView(unsigned int uWinWidth, unsigned int uWinHeight);
    void vPaintObject();

    GLuint gLoadObject(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements);
    GLuint gLoadTexture(const char * filename);
    GLuint gCreateTexture(GLuint uWidth, GLuint uHeight, GLuint uBpp, GLuint uColor);

    /* Initialize objects */
    ResourceManager oRscMgr;
};

inline GenericPainter::GenericPainter()
{
}

inline GenericPainter::~GenericPainter()
{
}
