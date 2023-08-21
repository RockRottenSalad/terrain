
#include "vao.h"

struct VAO vao;

void VAO_init(VAOFunc_ptr bind_ptr, VAOFunc_ptr delete_ptr, VAOConfigureFunc_ptr configure_ptr)
{
    vao.bind = bind_ptr;
    vao.delete = delete_ptr;
    vao.configure = configure_ptr;
    glGenVertexArrays(1, &vao.ptr);
}

void VAO_bind(void)
{
    glBindVertexArray(vao.ptr);
}

void VAO_configure(struct Attribute attrib)
{
    glVertexAttribPointer(attrib.attribute, attrib.vertices, GL_FLOAT, GL_FALSE,
            attrib.totalVertices * sizeof(float), (void*)0);
    glEnableVertexAttribArray(attrib.attribute);
}

void VAO_delete(void)
{
    glDeleteVertexArrays(1, &vao.ptr);
}
