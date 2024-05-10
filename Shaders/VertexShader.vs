#version 330 core

layout(location = 0) in vec3 aPos; // the position variable has attribute position 0
// layout(location = 1) in vec3 aColor; // the color variable has attribute position 1
layout(location = 1) in vec2 aTexCoord; // the texture variable has attribute position 2

out vec2 TexCoord; // output the texture coordinates to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord; // set the output texture coordinate to the input texture coordinate
}
