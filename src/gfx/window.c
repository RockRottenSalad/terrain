
#include "window.h"

struct Window window;

void window_init(const char* winTitle, int x, int y,
        winFunc_ptr loop_ptr, winFunc_ptr destroy_ptr, winFunc_ptr events_ptr)
{
    window.loop = loop_ptr;
    window.destroy = destroy_ptr;
    window.events = events_ptr;
    window.size[0] = x;
    window.size[1] = y;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window.ptr = glfwCreateWindow(y, x, winTitle, NULL, NULL);

    glfwMakeContextCurrent(window.ptr);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        printf("GLAD failed to load\n");

    glViewport(0, 0, y, x);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void window_loop(void)
{
    window.deltaB = window.deltaA = (float)glfwGetTime();
    while(!glfwWindowShouldClose(window.ptr))
    {
        window.events();
        window.deltaB = (float)glfwGetTime();
        window.deltaTime = window.deltaB - window.deltaA;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(unsigned int i = 0; i < window.strips; i++)
            glDrawElements(GL_TRIANGLE_STRIP, window.vertsPrStrip, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * window.vertsPrStrip * window.strips));

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();

        window.deltaA = window.deltaB;
    }
    window.destroy();
}

void window_events(void)
{
    if(glfwGetKey(window.ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.ptr, true);
}

void window_destroy(void)
{
    glfwTerminate();
    //free(window);
}
