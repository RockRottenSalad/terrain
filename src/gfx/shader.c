
#include "shader.h"

struct Shader shader;

char srcBuffer[1024];
char lineBuffer[128];

const char* vertexSrc = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 proj;\n"
"out float height;\n"
"void main()\n"
"{\n"
"   height = aPos.y;\n"
"   gl_Position = proj * view * model * vec4(aPos.xyz, 1.0);\n"
"}\0";

const char* fragmentSrc = "#version 330 core\n"
"out vec4 FragColor;\n"
"in float height;\n"
"void main()\n"
"{\n"
"   float col = (height+16)/32.0;\n"
"   FragColor = vec4(col, col, col, 1.0);\n"
"}\0";

void readFile(const char* filePath)
{
    FILE* file = fopen(filePath, "r");
    if(file == NULL)
        printf("shader not found\n");

    while(!feof(file))
    {
        fread(lineBuffer, sizeof(lineBuffer), 1, file);
        strcat(srcBuffer, lineBuffer);
    }
    fclose(file);
}

void shader_init(shaderSetTransFunc_ptr setModelViewProj_ptr, shaderFunc_ptr use_ptr, shaderFunc_ptr delete_ptr)
{
    shader.setTransFunc = setModelViewProj_ptr;
    shader.delete = delete_ptr;
    shader.use = use_ptr;

    shader.vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader.vertexShader, 1, &vertexSrc, NULL);
    glCompileShader(shader.vertexShader);
    //memset(&srcBuffer[0], 0, sizeof(srcBuffer));

    shader.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //readFile("./src/gfx/glsl/fragment.glsl");
    glShaderSource(shader.fragmentShader, 1, &fragmentSrc, NULL);
    glCompileShader(shader.fragmentShader);

    shader.ptr = glCreateProgram();
    glAttachShader(shader.ptr, shader.vertexShader);
    glAttachShader(shader.ptr, shader.fragmentShader);
    glLinkProgram(shader.ptr);

    int check;
    glGetShaderiv(shader.vertexShader, GL_COMPILE_STATUS, &check);
    if(!check)
    {
        glGetShaderInfoLog(shader.vertexShader, 1024, NULL, srcBuffer);
        printf("%s\n", srcBuffer);

    }
    glGetShaderiv(shader.fragmentShader, GL_COMPILE_STATUS, &check);
    if(!check)
    {
        glGetShaderInfoLog(shader.fragmentShader, 1024, NULL, srcBuffer);
        printf("%s\n", srcBuffer);

    }
    glGetProgramiv(shader.ptr, GL_LINK_STATUS, &check);
    if(!check)
    {
        glGetProgramInfoLog(shader.ptr, 1024, NULL, srcBuffer);
        printf("%s\n", srcBuffer);
    }

    glUseProgram(shader.ptr);
    shader.modelLoc = glGetUniformLocation(shader.ptr, "model");
    shader.viewLoc = glGetUniformLocation(shader.ptr, "view");
    shader.projLoc = glGetUniformLocation(shader.ptr, "proj");

  //  shader.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
}

void shader_setModelViewProj(mat4* modelArg, mat4* viewArg, mat4* projArg)
{
    //printf("test: %f\n", *modelArg[0][0]);
    
    glUniformMatrix4fv(shader.modelLoc, 1, GL_FALSE, (const GLfloat *)modelArg);
    glUniformMatrix4fv(shader.viewLoc, 1, GL_FALSE, (const GLfloat *)viewArg);
    glUniformMatrix4fv(shader.projLoc, 1, GL_FALSE, (const GLfloat *)projArg);
}

void shader_useProgram(void)
{
    glUseProgram(shader.ptr);
}

void shader_delete(void)
{
    glDeleteProgram(shader.ptr);
    glDeleteShader(shader.vertexShader);
    glDeleteShader(shader.fragmentShader);
}
