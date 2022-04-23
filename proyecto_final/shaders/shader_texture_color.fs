#version 330 core

in vec2 TexCoord;
in vec3 ourColor;

uniform sampler2D texture1;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
	// vec4 texColor = vec4(ourColor, 1.0);
    if(texColor.a < 0.1) discard;
    FragColor = texColor;
}