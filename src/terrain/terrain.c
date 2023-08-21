
#include "terrain.h"

#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

struct Terrain terrain;

void terrain_init(TerrainCharArgFunc_ptr loadHeightMap_ptr, TerrainFunc_ptr generateVertices_ptr,
        TerrainFloatReturnFunc_ptr getVertices_ptr, TerrainIntReturnFunc_ptr getIndices_ptr, TerrainFunc_ptr destroy_ptr)
{
    terrain.loadHeightMap = loadHeightMap_ptr;
    terrain.generateVertices = generateVertices_ptr;
    terrain.getVertices = getVertices_ptr;
    terrain.getIndices = getIndices_ptr;
    terrain.destroy = destroy_ptr;

    stbi_set_flip_vertically_on_load(true);
}

void terrain_loadHeightMap(char* filePath)
{
    terrain.heightmap.data = stbi_load(filePath, &terrain.heightmap.width, &terrain.heightmap.height, &terrain.heightmap.nrChannels, 0);
    if(!terrain.heightmap.data)
        printf("failed to load texture\n");
}

void terrain_generateVertices(void)
{
    int vertexCount = terrain.heightmap.width * terrain.heightmap.height;
    terrain.vertices = malloc(sizeof(float) * (vertexCount*3));
    terrain.polygonIndices = malloc(sizeof(int) * (vertexCount*3));
    terrain.verticesLen = vertexCount*3;

    terrain.strips = terrain.heightmap.height - 1;
    terrain.vertsPrStrip = terrain.heightmap.width * 2;

    int index = 0;
    for(unsigned int i = 0; i < terrain.heightmap.height; i++)
    {
        for(unsigned int n = 0; n < terrain.heightmap.width; n++)
        {
            unsigned char* pixel = terrain.heightmap.data + (n + terrain.heightmap.width * i) * terrain.heightmap.nrChannels;

            unsigned char y = pixel[0];
            terrain.vertices[index] = (-terrain.heightmap.height / 2.0f + terrain.heightmap.height*i/(float)terrain.heightmap.height);
            terrain.vertices[index+1] = (int)y * (32.0f / 256.0f) - 16.0f;
            terrain.vertices[index+2] = (-terrain.heightmap.width / 2.0f + terrain.heightmap.width*n/(float)terrain.heightmap.width);
            index += 3;
        }
    }

    index = 0;
    for(unsigned int i = 0; i < terrain.heightmap.height - 1; i++)
    {
        for(unsigned int j = 0; j < terrain.heightmap.width; j++)
        {
            for(unsigned int k = 0; k < 2; k++)
            {
                terrain.polygonIndices[index] = j + terrain.heightmap.width * (i + k);
                index++;
            }
        }
    }

    terrain.indicesLen = index;
    printf("total indices: %d\n", index-1);
    printf("vert: %f %f %f\n", terrain.vertices[3], terrain.vertices[4], terrain.vertices[5]);
    printf("strips: %d\nvertsPrStrip: %d\n", terrain.strips, terrain.vertsPrStrip);

}

float* terrain_getVertices(int* len)
{
    *len = terrain.verticesLen;
    return terrain.vertices;
}

unsigned int* terrain_getPolygonIndices(int* len)
{
    *len = terrain.indicesLen;
    return terrain.polygonIndices;
}

void terrain_destroy(void)
{
    free(terrain.vertices);
    free(terrain.polygonIndices);
    stbi_image_free(terrain.heightmap.data);
}
