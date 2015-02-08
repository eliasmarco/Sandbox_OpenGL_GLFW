#include "GenericPainter.h"

void GenericPainter::vInit(unsigned int uWinWidth, unsigned int uWinHeight)
{
    vSetupView(uWinWidth, uWinHeight);
    //gLoadTexture("../Resources/Textures/Texture1.png");
}

void GenericPainter::vDraw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    float points[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };



    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertex_shader =
        "#version 400\n"
        "in vec3 vp;"
        "void main () {"
        "  gl_Position = vec4 (vp, 1.0);"
        "}";

    const char* fragment_shader =
        "#version 400\n"
        "out vec4 frag_colour;"
        "void main () {"
        "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
        "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);


    glUseProgram(shader_programme);
    glBindVertexArray(vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);







    return;


    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex_square_1x1);

    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //glTexCoordPointer(2, GL_FLOAT, 0, texture_square_1x1);
    GLuint uTex1 = gCreateTexture(64, 64, 4, 0xFF00FFCF);
    GLuint uTex2 = gCreateTexture(64, 64, 4, 0xFFFF00CF);

    vector<glm::vec4> vertices;
    vector<glm::vec3> normals;
    vector<GLushort> elements;
    gLoadObject("../Resources/3DObject/cube.obj", vertices, normals, elements);

    static int flag = false;

    GLuint vbo_mesh_vertices;
    //GLuint vbo_mesh_normals;
    //GLuint ibo_mesh_elements;

    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);

    glGenBuffers(1, &vbo_mesh_vertices);
    //glGenBuffers(1, &vbo_mesh_normals);
    //glGenBuffers(1, &ibo_mesh_elements);
    glEnableVertexAttribArray(0);
    // Describe our vertices array to OpenGL (it can't guess its format automatically)
    glBindBuffer(GL_ARRAY_BUFFER, vbo_mesh_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_square_1x1), &vertex_square_1x1, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0,                  // attribute
        4,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
        );

    //glBindBuffer(GL_ARRAY_BUFFER, vbo_mesh_normals);
    //glVertexAttribPointer(
    //    1, // attribute
    //    3,                  // number of elements per vertex, here (x,y,z)
    //    GL_FLOAT,           // the type of each element
    //    GL_FALSE,           // take our values as-is
    //    0,                  // no extra data between each position
    //    0                   // offset of first element
    //    );

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[0]);
    //int size;  
    //glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    //glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    SHOW_GL_ERROR

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glBindTexture(GL_TEXTURE_2D, uTex1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


    glFlush();
    //glBindTexture(GL_TEXTURE_2D, uTex2);
    //glTranslatef(-0.5f, 0.0f, 0.0f);
    //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GenericPainter::vSetupView(unsigned int uWinWidth, unsigned int uWinHeight)
{
    glViewport(0, 0, uWinWidth, uWinHeight);

    glMatrixMode(GL_PROJECTION);
    //glScalef(0.10f, 0.10f, 1.0f);
    //glTranslatef(0.0f, 0.0f, -2.0f);
}

GLuint GenericPainter::gLoadTexture(const char * filename)
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

GLuint GenericPainter::gLoadObject(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements) 
{
    ifstream in(filename, ios::in);
    if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }

    string line;
    while (getline(in, line)) {
        if (line.substr(0, 2) == "v ") {
            istringstream s(line.substr(2));
            glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
            vertices.push_back(v);
        }
        else if (line.substr(0, 2) == "f ") {
            istringstream s(line.substr(2));
            GLushort a, b, c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;
            elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
        else if (line[0] == '#') { /* ignoring this line */ }
        else { /* ignoring this line */ }
    }

    normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (int i = 0; i < elements.size(); i += 3) {
        GLushort ia = elements[i];
        GLushort ib = elements[i + 1];
        GLushort ic = elements[i + 2];
        //glm::vec3 normal = glm::normalize(glm::cross(
        //    glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
        //    glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
        //normals[ia] = normals[ib] = normals[ic] = normal;
    }
}


GLuint GenericPainter::gCreateTexture(GLuint uWidth, GLuint uHeight, GLuint uBpp, GLuint uColor)
{
    GLubyte * myTexture = new GLubyte[uWidth * uHeight * uBpp];

    for (int i = 0; i < uWidth; i++)
    {
        for (int j = 0; j < uHeight; j++)
        {
            for (int k = 0; k < uBpp; k++)
            {
                switch (k)
                {
                case 0: {
                    myTexture[(i * 64 * 4) + (j * 4) + k] = (uColor & 0xFF000000) >> (3 * 8);
                }
                        break;
                case 1: {
                    myTexture[(i * 64 * 4) + (j * 4) + k] = (uColor & 0x00FF0000) >> (2 * 8);
                }
                        break;
                case 2: {
                    myTexture[(i * 64 * 4) + (j * 4) + k] = (uColor & 0x0000FF00) >> (1 * 8);
                }
                        break;
                case 3: {
                    myTexture[(i * 64 * 4) + (j * 4) + k] = (uColor & 0x000000FF);
                }
                        break;
                default: {};
                         break;
                }
            }
        }
    }

    GLuint texture;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, myTexture);

    return texture;
}