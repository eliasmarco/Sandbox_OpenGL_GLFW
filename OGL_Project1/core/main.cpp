#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>

#include "defines.h"
#include "GenericPainter.h"

int main(int argc, char * argv[])
{
    GLFWwindow* window;
    unsigned int uWinWidth = 640;
    unsigned int uWinHeight = 480;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(uWinWidth, uWinHeight, "OpenGL SandBox", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    /* Initialize Objects */
    GenericPainter oPainter;

    oPainter.vInit(uWinWidth, uWinHeight);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        oPainter.vDraw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}