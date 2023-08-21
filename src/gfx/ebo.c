
#include "ebo.h"

struct EBO ebo;

void EBO_init(EBOFunc_ptr bind_ptr, EBOFunc_ptr delete_ptr, EBOConfigureFunc_ptr configure_ptr)
{
    ebo.bind = bind_ptr;
    ebo.delete = delete_ptr;
    ebo.configure = configure_ptr;
    glGenBuffers(1, &ebo.ptr);
}

void EBO_bind(void)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.ptr);
}

void EBO_configure(unsigned int* indices, int n)
{
    printf("EBO loading: %d indices\n", n);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * n, indices, GL_STATIC_DRAW);
}

void EBO_delete(void)
{
    glDeleteBuffers(1, &ebo.ptr);
}
