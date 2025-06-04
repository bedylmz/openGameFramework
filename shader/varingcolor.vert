#version 430
layout (location=0) in vec3 position;

out vec4 varyingColor;

uniform mat4 proj_matrix;
uniform mat4 cam_matrix;
uniform mat4 model_matrix;

void main(void)
{
    vec4 new_position = model_matrix * vec4(position, 1.0);
    gl_Position = proj_matrix * cam_matrix * new_position;

    varyingColor = new_position + vec4(0.5,0.5,0.5,0.5);
}
