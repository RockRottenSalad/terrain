
#include "eventhandler.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.updateDirection(xpos, ypos);
}

void keyboard_callback(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveForward();
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBack();
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft();
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight();
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
