
#include "vbo.h"

struct VBO vbo;

void VBO_init(VBOFunc_ptr bind_ptr, VBOFunc_ptr delete_ptr, VBOConfigureFunc_ptr configure_ptr)
{
    vbo.bind = bind_ptr;
    vbo.delete = delete_ptr;
    vbo.configure = configure_ptr;
    glGenBuffers(1, &vbo.ptr);
}

void VBO_bind(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo.ptr);
}

void VBO_configure(float* vertices, int n)
{
    printf("\nVBO loading %d vertices\n", n);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, vertices, GL_STATIC_DRAW);
}

void VBO_delete(void)
{
    glDeleteBuffers(1, &vbo.ptr);
}
