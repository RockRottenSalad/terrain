
#include "camera.h"

struct Camera camera;

void camera_init(camFuncGetMat4_ptr getView_ptr, camFuncGetMat4_ptr getPers_ptr, camFunc_ptr updateCamera_ptr, camFuncTurn_ptr updateDirection_ptr,
        camFunc_ptr moveForward_ptr, camFunc_ptr moveBack_ptr, camFunc_ptr moveRight_ptr, camFunc_ptr moveLeft_ptr)
{
    camera.getView = getView_ptr;
    camera.getPerspective = getPers_ptr;
    camera.updateCamera = updateCamera_ptr;
    camera.updateDirection = updateDirection_ptr;
    camera.moveForward = moveForward_ptr;
    camera.moveBack = moveBack_ptr;
    camera.moveRight = moveRight_ptr;
    camera.moveLeft = moveLeft_ptr;

    camera.pos[0] = 0.0f;
    camera.pos[1] = 0.0f;
    camera.pos[2] = 0.0f;

    camera.target[0] = 0.0f;
    camera.target[1] = 0.0f;
    camera.target[2] = -1.0f;

    camera.up[0] = 0.0f;
    camera.up[1] = 1.0f;
    camera.up[2] = 0.0f;

    camera.camSpeed = 0.75f;
    camera.camSens = 0.1f;
    camera.fov = 110.0f;

    camera.yaw = -90.0f;
    camera.pitch = 0.0f;

    camera.lastX = 450.0;
    camera.lastY = 450.0;

}

mat4* camera_getView(void)
{
    return &camera.view;
}

mat4* camera_getPerspective(void)
{
    return &camera.perspective;
}

void camera_updateCamera(void)
{
    glm_mat4_identity(camera.view);
    glm_mat4_identity(camera.perspective);
    glm_vec3_add(camera.pos, camera.target, camera.center);
    glm_lookat(camera.pos, camera.center, camera.up, camera.view);
    glm_perspective(camera.fov * (M_PI/180.0f), 1920.0f/1080.0f, 0.1f, 10000.0f, camera.perspective);
    //printf("target: %f %f %f\n", camera.target[0], camera.target[1], camera.target[2]);
}

void camera_updateDirection(double x, double y)
{
    camera.yaw += (x - camera.lastX) * camera.camSens;
    camera.pitch += (camera.lastY - y) * camera.camSens;
    camera.lastX = x;
    camera.lastY = y;

    if(camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    if(camera.pitch < -89.0f)
        camera.pitch = -89.0f;
    camera.target[0] = cos(camera.yaw * (M_PI/180.0f)) * cos(camera.pitch * (M_PI/180.0f));
    camera.target[1] = sin(camera.pitch * (M_PI/180.0f));
    camera.target[2] = sin(camera.yaw * (M_PI/180.0f)) * cos(camera.pitch * (M_PI/180.0f));

    glm_vec3_normalize(camera.target);
    camera.updateCamera();

}

void camera_moveForward(void)
{
    glm_vec3_zero(camera.buffer);
    glm_vec3_scale(camera.target, camera.camSpeed, camera.buffer);
    glm_vec3_add(camera.pos, camera.buffer, camera.pos);
}

void camera_moveBack(void)
{
    glm_vec3_zero(camera.buffer);
    glm_vec3_scale(camera.target, camera.camSpeed, camera.buffer);
    glm_vec3_sub(camera.pos, camera.buffer, camera.pos);
}

void camera_moveRight(void)
{
    glm_vec3_zero(camera.buffer);
    glm_vec3_crossn(camera.target, camera.up, camera.buffer);
    glm_vec3_scale(camera.buffer, camera.camSpeed, camera.buffer);
    glm_vec3_add(camera.pos, camera.buffer, camera.pos);
}

void camera_moveLeft(void)
{
    glm_vec3_zero(camera.buffer);
    glm_vec3_crossn(camera.target, camera.up, camera.buffer);
    glm_vec3_scale(camera.buffer, camera.camSpeed, camera.buffer);
    glm_vec3_sub(camera.pos, camera.buffer, camera.pos);
}
