#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "defines.h"
#include "ResourceManager.h"
#include "lodepng/lodepng.h"
#include "ModelData.h"

class GenericPainter {
public:
    GenericPainter();
    ~GenericPainter();

    void vInit(unsigned int uWinWidth, unsigned int uWinHeight);
    void vDraw();

private:
    void vSetupView(unsigned int uWinWidth, unsigned int uWinHeight);
    GLuint vLoadTexture(const char * filename);

    void vPaintObject();

    /* Initialize objects */
    ResourceManager oRscMgr;
};

inline GenericPainter::GenericPainter()
{
}

inline GenericPainter::~GenericPainter()
{
}
