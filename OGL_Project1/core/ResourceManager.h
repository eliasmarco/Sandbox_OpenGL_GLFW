#include <vector>
#include <iostream>
#include "lodepng\lodepng.h"

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    void createResource();
    unsigned char * loadBmp(const char * filename);
    unsigned char * loadPng(const char * filename);
    unsigned char * loadObj(const char * filename);
};