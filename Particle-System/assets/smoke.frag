#version 330 core
out vec4 color;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D ourTexture;

void main()
{
  // color = texture(ourTexture, TexCoords);
  color = texture(ourTexture, TexCoords);
}
