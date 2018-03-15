#version 330 core
out vec4 color;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D ourTexture;

void main()
{
  // color = texture(ourTexture, TexCoords);
  vec4 colorTexture = texture(ourTexture, TexCoords);
  color =vec4(0.7569f, 0.2471f, 0.1176f, colorTexture.a);
}
