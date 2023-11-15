#version 330
uniform mat2 transform;
uniform vec3 cam_pos;
uniform float ts;
in vec2 pos;
in vec2 tex;
out vec2 texcoord;
void main(void)
{

    vec3 d = vec3(pos,0) - cam_pos;
    texcoord = tex;
    vec4 xar = vec4(d, 1);
    gl_Position = xar;

}