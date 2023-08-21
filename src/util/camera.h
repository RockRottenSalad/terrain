#ifndef CAMERA_H
#define CAMERA_H

#include<cglm/cglm.h>

typedef void (*camFunc_ptr)(void);
typedef mat4* (*camFuncGetMat4_ptr)(void);
typedef void (*camFuncTurn_ptr)(double, double);

struct Camera
{
    mat4 view;
    mat4 perspective;
    vec3 pos;
    vec3 target;
    vec3 center;
    vec3 up;
    vec3 buffer;

    float yaw, pitch;

    float camSpeed, camSens, fov, deltaTime;
    camFuncGetMat4_ptr getView;
    camFuncGetMat4_ptr getPerspective;
    camFunc_ptr updateCamera;
    camFuncTurn_ptr updateDirection;

    camFunc_ptr moveForward, moveBack, moveRight, moveLeft;

    // mouse pos
    double lastX, lastY;

    // Window
    int winWidth, winHeight;
};

extern struct Camera camera;

void camera_init(camFuncGetMat4_ptr getView_ptr, camFuncGetMat4_ptr getPers_ptr,
        camFunc_ptr updateCamera_ptr, camFuncTurn_ptr updateDirection_ptr,
        camFunc_ptr moveForward_ptr, camFunc_ptr moveBack_ptr, camFunc_ptr moveRight_ptr, camFunc_ptr moveLeft_ptr);
mat4* camera_getView(void);
mat4* camera_getPerspective(void);
void camera_updateCamera(void);
void camera_updateDirection(double x, double y);
void camera_moveForward(void);
void camera_moveBack(void);
void camera_moveRight(void);
void camera_moveLeft(void);

#endif
