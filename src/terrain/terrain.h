#ifndef TERRAIN_H
#define TERRAIN_H

#include<cglm/cglm.h>

struct Vertex
{
    vec3 position;
    vec3 normal;
};

struct HeightMap
{
    unsigned char* data;
    int width, height, nrChannels;
};

typedef void (*TerrainFunc_ptr)(void);
typedef void (*TerrainCharArgFunc_ptr)(char*);
typedef float* (*TerrainFloatReturnFunc_ptr)(int*);
typedef unsigned int* (*TerrainIntReturnFunc_ptr)(int*);

struct Terrain
{
    TerrainFunc_ptr generateVertices, destroy;
    TerrainCharArgFunc_ptr loadHeightMap;
    TerrainFloatReturnFunc_ptr getVertices;
    TerrainIntReturnFunc_ptr getIndices;

    struct HeightMap heightmap;
    float* vertices;
    unsigned int verticesLen;
    unsigned int* polygonIndices;
    unsigned int indicesLen;

    unsigned int strips;
    unsigned int vertsPrStrip;
};

extern struct Terrain terrain;

void terrain_init(TerrainCharArgFunc_ptr loadHeightMap_ptr, TerrainFunc_ptr generateVertices_ptr,
        TerrainFloatReturnFunc_ptr getVertices_ptr, TerrainIntReturnFunc_ptr, TerrainFunc_ptr destroy_ptr);
void terrain_loadHeightMap(char* filePath);
void terrain_generateVertices(void);
float* terrain_getVertices(int* len);
unsigned int* terrain_getPolygonIndices(int* len);
void terrain_destroy(void);

#endif
