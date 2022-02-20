#version 450

layout (binding = 1) uniform sampler2D samplerImage;

layout (location = 0) in vec2 inTexCoord;

layout (location = 0) out vec4 FragColor;

void main()
{
    vec4 image = texture(samplerImage, inTexCoord);
    FragColor = image;
}