#ifndef SHADER_H
#define SHADER_H

#include<stdio.h>
#include<cglm/cglm.h>
#include<glad/glad.h>
#include<string.h>

extern char srcBuffer[1024];
extern char lineBuffer[128];

void readFile(const char* filePath);

typedef void (*shaderSetTransFunc_ptr)(mat4* modelArg, mat4* viewArg, mat4* projArg);
typedef void(*shaderFunc_ptr)(void);

struct Shader
{
    unsigned int ptr;
    unsigned int vertexShader, fragmentShader;

    unsigned int modelLoc, viewLoc, projLoc;
    
    shaderSetTransFunc_ptr setTransFunc;
    shaderFunc_ptr use, delete;
};

extern struct Shader shader;

void shader_init(shaderSetTransFunc_ptr setModelViewProj_ptr, shaderFunc_ptr use_ptr, shaderFunc_ptr delete_ptr);
void shader_setModelViewProj(mat4* modelArg, mat4* viewArg, mat4* projArg);
void shader_useProgram(void);
void shader_delete(void);

#endif
