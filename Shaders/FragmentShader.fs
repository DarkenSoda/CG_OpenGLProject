#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 color;
uniform bool useTexture;
uniform sampler2D texture1;

void main()
{
    if (useTexture)
        FragColor = texture(texture1, TexCoord) * color;
    else
        FragColor = color;
    
    vec4(0.6863, 0.5373, 0.3098, 1.0);
}
