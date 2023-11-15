#version 330
uniform sampler2D TexMap;
in vec2 texcoord;

out vec4 color;
void main(void)
{
      vec4 var = texture(TexMap, texcoord);
      var = var + vec4(0.0, 0.0, 0.0, 1.0);
      color = texture(TexMap, texcoord);
      color = vec4(texcoord, 0.0, 1.0);
      //color = vec4(1, 0,  0.0, 1.0);
      //color = var;
}