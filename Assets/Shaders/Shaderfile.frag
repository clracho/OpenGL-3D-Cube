
#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

//layout(location = 0) out vec4 outColor;

void main()
{
    FragColor = texture(ourTexture, TexCoord)* vec4(ourColor, 1.0);
    //outColor.rgb = vertOutColor;
}