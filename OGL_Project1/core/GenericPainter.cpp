#include "GenericPainter.h"

void GenericPainter::vInit(unsigned int uWinWidth, unsigned int uWinHeight)
{
    vSetupView(uWinWidth, uWinHeight);
    vLoadTexture("../Resources/Textures/Texture1.png");
}

void GenericPainter::vDraw()
{
    glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex_square_1x1);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texture_square_1x1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GenericPainter::vSetupView(unsigned int uWinWidth, unsigned int uWinHeight)
{
    glViewport(0, 0, uWinWidth, uWinHeight);

    glMatrixMode(GL_PROJECTION);
    glScalef(0.5f, 0.5f, 1.0f);
}

GLuint GenericPainter::vLoadTexture(const char * filename)
{
    std::vector<unsigned char> png;
    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    //load and decode
    lodepng::load_file(png, filename);
    unsigned error = lodepng::decode(image, width, height, png);

    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    unsigned char temp[64 * 64 * 4];
    for (unsigned int j = 0; j < height * width * 4; j++)
    {
        temp[j] = image[j];
    }

    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            for (unsigned int k = 0; k < 4; k++)
            {
                image[(i * 64 * 4) + (j * 4) + k] = temp[((height - i) * 64 * 4) + (j * 4) + k];
            }
        }
    }


    std::cout << "Loading Texture " << filename << std::endl;
    std::cout << "Texture Width  = " << width << std::endl;
    std::cout << "Texture Height = " << height << std::endl;
    std::cout << "data : ";

    for (unsigned int i = 0; i < width * height; i += 4)
    {
        printf("[%02d] 0x %x %x %x %x\n", i, image[i], image[i + 1], image[i + 2], image[i + 3]);
    }

    GLuint texture;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

    return texture;
}

#if 0
GLubyte myTexture[64 * 64 * 4];

for (int i = 0; i < 64; i++)
{
    for (int j = 0; j < 64; j++)
    {
        for (int k = 0; k < 4; k++)
        {
            switch (k)
            {
            case 0: { myTexture[(i * 64 * 4) + (j * 4) + k] = 0xff; }
                    break;
            case 1: { myTexture[(i * 64 * 4) + (j * 4) + k] = 0x0; }
                    break;
            case 2: { myTexture[(i * 64 * 4) + (j * 4) + k] = 0x0; }
                    break;
            case 3: { myTexture[(i * 64 * 4) + (j * 4) + k] = 0xff; }
                    break;
            default: {};
                     break;
            }
        }
    }
}
#endif