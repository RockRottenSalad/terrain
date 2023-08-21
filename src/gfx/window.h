#ifndef WINDOW_H
#define WINDOW_H

//#include "gfx.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cglm/cglm.h>
#include<stdio.h>

typedef void (*winFunc_ptr)(void);

struct Window
{
    GLFWwindow* ptr;
    ivec2 size;
    winFunc_ptr init, loop, destroy, events; 
    float deltaA, deltaB, deltaTime;

    unsigned int strips, vertsPrStrip;
};

extern struct Window window;

void window_init(const char* winTitle, int x, int y,
        winFunc_ptr loop_ptr, winFunc_ptr destroy_ptr, winFunc_ptr events_ptr);
void window_destroy(void);
void window_loop(void);
void window_events(void);

#endif
