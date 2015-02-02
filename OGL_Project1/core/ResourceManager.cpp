#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

unsigned char * ResourceManager::loadBmp(const char * filename)
{
    // TODO
    return NULL;
}

unsigned char * ResourceManager::loadPng(const char * filename)
{
    std::vector<unsigned char> png;
    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    //load and decode
    lodepng::load_file(png, filename);
    unsigned error = lodepng::decode(image, width, height, png);

    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    std::cout << "Loading Texture " << filename << std::endl;
    std::cout << "Texture Width  = " << width << std::endl;
    std::cout << "Texture Height = " << height << std::endl;
    std::cout << "data : ";
    for (unsigned int i = 0; i < width * height; i += 4)
    {
        printf("[%02d] 0x %x %x %x %x\n", i, image[i], image[i+1], image[i+2], image[i+3]);
    }

    return &image[0];
}

unsigned char * ResourceManager::loadObj(const char * filename)
{
    return NULL;
}
