#version 330 core

in float height;

void main()
{
    float col = (height+16)/32.0;
    FragColor = vec4(col, col, col, 1.0);
}
