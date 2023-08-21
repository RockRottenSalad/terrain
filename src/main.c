
#include "gfx/window.h"
// also includes vbo and ebo
#include "gfx/vao.h"
#include "gfx/shader.h"
#include "terrain/terrain.h"
#include "util/camera.h"

// MOVE TO UTIL
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.updateDirection(xpos, ypos);
}

void keyboard_callback(void)
{
    if(glfwGetKey(window.ptr, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveForward();
    if(glfwGetKey(window.ptr, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBack();
    if(glfwGetKey(window.ptr, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft();
    if(glfwGetKey(window.ptr, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight();
    if(glfwGetKey(window.ptr, GLFW_KEY_F) == GLFW_PRESS)
        glfwSetInputMode(window.ptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

int main(int argc, char** argv)
{
    
    // # WINDOW
    window_init("Terrain", 1080, 1920,
            window_loop, window_destroy, window_events);
    glfwSetCursorPosCallback(window.ptr, mouse_callback);
    glfwSetInputMode(window.ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // # TERRAIN/VERTICES
    terrain_init(terrain_loadHeightMap, terrain_generateVertices, terrain_getVertices, terrain_getPolygonIndices, terrain_destroy);
    terrain.loadHeightMap("res/england.png");
    terrain.generateVertices();

    int n;
    float* vertex = terrain.getVertices(&n);
    printf("\ntotal vertex count: %d\n", n);

    // # CAMERA
    camera_init(camera_getView, camera_getPerspective, camera_updateCamera, camera_updateDirection,
            camera_moveForward, camera_moveBack, camera_moveRight, camera_moveLeft);


    // # VAO, VBO, EBO
    VAO_init(VAO_bind, VAO_delete, VAO_configure);
    vao.bind();

    VBO_init(VBO_bind, VBO_delete, VBO_configure);
    vbo.bind();
    vbo.configure(vertex, n);

    vao.configure( ((struct Attribute) {
            .attribute = 0,
            .vertices = 3,
            .totalVertices = 3,
            .offset = 0
            }));

    int len;
    unsigned int* indices = terrain.getIndices(&len);
    EBO_init(EBO_bind, EBO_delete, EBO_configure);
    ebo.bind();
    ebo.configure(indices, len);

    // # SHADER
    shader_init(shader_setModelViewProj, shader_useProgram, shader_delete);
    mat4 model;
    glm_mat4_identity(model);
    shader.setTransFunc(&model, camera.getView(), camera.getPerspective());
    //shader.use();

    glEnable(GL_DEPTH_TEST);
    // # START OF MAIN LOOP
    window.deltaB = window.deltaA = (float)glfwGetTime();
    GLenum err;
    while(!glfwWindowShouldClose(window.ptr))
    {
        window.events();
        window.deltaB = (float)glfwGetTime();
        window.deltaTime += window.deltaB - window.deltaA;

        err = glGetError();
        if(err != GL_NO_ERROR)
            printf("ERROR CODE: %d\n", err);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        camera.updateCamera();
        shader.setTransFunc(&model, camera.getView(), camera.getPerspective());
        if(window.deltaTime >= 1.0 / 30.0)
        {
            for(unsigned int i = 0; i < terrain.strips; i++)
                glDrawElements(GL_TRIANGLE_STRIP, terrain.vertsPrStrip, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * terrain.vertsPrStrip*i));

            glfwSwapBuffers(window.ptr);
            window.deltaA = window.deltaB;
        }

        glfwPollEvents();
        keyboard_callback();

    }
    window.destroy();
    //window.loop();

    // # POST WINDOW EXIT CLEANUP
    terrain.destroy();
    shader.delete();
    vao.delete();
    vbo.delete();
    
    return 0;
}
