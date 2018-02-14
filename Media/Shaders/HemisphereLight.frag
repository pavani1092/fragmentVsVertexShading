#version 330 core
in vec3 fragVert;
in vec3 fragNormal;
in vec3 fragmentColor;
out vec4 color;

void main( )
{

    color = vec4(fragmentColor,1.0);
	 
}  