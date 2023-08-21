
#ifndef VBO_H
#define VBO_H

#include "ebo.h"
#include <stdio.h>

typedef void(*VBOFunc_ptr)(void);
typedef void(*VBOConfigureFunc_ptr)(float*, int);

struct VBO
{
    unsigned int ptr;
    VBOFunc_ptr bind, delete;
    VBOConfigureFunc_ptr configure;
};

extern struct VBO vbo;

void VBO_init(VBOFunc_ptr bind_ptr, VBOFunc_ptr delete_ptr, VBOConfigureFunc_ptr configure_ptr);
void VBO_bind(void);
void VBO_configure(float* vertices, int n);
void VBO_delete(void);

#endif
