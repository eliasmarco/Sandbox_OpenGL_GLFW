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

    for (int i = 0; i < width * height; i++)
    {
        std::cout << "data " << image[i] << std::endl;
    }

    return &image[0];
}

unsigned char * ResourceManager::loadObj(const char * filename)
{
    return NULL;
}
