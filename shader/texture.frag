#version 430

in vec2 tc;
in vec4 varyingColor;

out vec4 color;
layout (binding = 0) uniform sampler2D samp;


void main(void) 
{
    color = texture(samp, tc);

    //color = varyingColor; //Gourand Shading
}