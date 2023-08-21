#ifndef VAO_H
#define VAO_H

#include "vbo.h"

struct Attribute
{
    int attribute;
    int vertices;
    int totalVertices;
    int offset;
};

typedef void(*VAOFunc_ptr)(void);
typedef void(*VAOConfigureFunc_ptr)(struct Attribute);

struct VAO
{
    unsigned int ptr;
    VAOFunc_ptr bind, delete;
    VAOConfigureFunc_ptr configure;
};

extern struct VAO vao;

void VAO_init(VAOFunc_ptr bind_ptr, VAOFunc_ptr delete_ptr, VAOConfigureFunc_ptr configure_ptr);
void VAO_bind(void);
void VAO_configure(struct Attribute attrib);
void VAO_delete(void);

#endif
