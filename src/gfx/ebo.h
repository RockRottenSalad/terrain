#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>
#include<stdlib.h>
#include<string.h>
#include <stdio.h>

typedef void(*EBOFunc_ptr)(void);
typedef void(*EBOConfigureFunc_ptr)(unsigned int*, int);

struct EBO
{
    unsigned int ptr;
    EBOFunc_ptr bind, delete;
    EBOConfigureFunc_ptr configure;
};

extern struct EBO ebo;

void EBO_init(EBOFunc_ptr bind_ptr, EBOFunc_ptr delete_ptr, EBOConfigureFunc_ptr configure_ptr);
void EBO_bind(void);
void EBO_configure(unsigned int* indices, int n);
void EBO_delete(void);

#endif
