#version 430
layout (location=0) in vec3 position;
layout (location=1) in vec3 normals;
layout (location=2) in vec2 texCoord;
layout (location=3) in vec3 tangent;
layout (location=4) in vec3 bitangent;
layout (location=5) in vec4 ids;
layout (location=6) in vec4 weigths;

out vec4 varyingColor;
out vec2 tc;

uniform mat4 norm_matrix;
uniform mat4 proj_matrix;
uniform mat4 cam_matrix;
uniform mat4 model_matrix;
layout (binding = 0) uniform sampler2D samp;

void main(void)
{
    //vec4 new_position = model_matrix * vec4(position, 1.0);
    //varyingColor = new_position + vec4(0.5,0.5,0.5,0.5);
    gl_Position = proj_matrix * cam_matrix * model_matrix * vec4(position, 1.0);

    tc = texCoord;
}
